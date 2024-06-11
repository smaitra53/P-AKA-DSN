/*
 * Licensed to the OpenAirInterface (OAI) Software Alliance under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The OpenAirInterface Software Alliance licenses this file to You under
 * the OAI Public License, Version 1.1  (the "License"); you may not use this
 * file except in compliance with the License. You may obtain a copy of the
 * License at
 *
 *      http://www.openairinterface.org/?page_id=698
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *-------------------------------------------------------------------------------
 * For more information about the OpenAirInterface (OAI) Software Alliance:
 *      contact@openairinterface.org
 */

#include "authfunctions.hpp"
#include <gmp.h>
#include <nettle/hmac.h>

random_state_t random_state;

void Authentication_5gaka::generate_random(uint8_t* random_p, ssize_t length) {
  gmp_randinit_default(random_state.state);
  gmp_randseed_ui(random_state.state, time(NULL));
  random_t random_nb;
  mpz_init(random_nb);
  mpz_init_set_ui(random_nb, 0);
  pthread_mutex_lock(&random_state.lock);
  mpz_urandomb(random_nb, random_state.state, 8 * length);
  pthread_mutex_unlock(&random_state.lock);
  mpz_export(random_p, NULL, 1, length, 0, 0, random_nb);

  return;
}

void Authentication_5gaka::f1(
    const uint8_t opc[16], const uint8_t k[16], const uint8_t _rand[16],
    const uint8_t sqn[6], const uint8_t amf[2], uint8_t mac_a[8]) {
  uint8_t temp[16];
  uint8_t in1[16];
  uint8_t out1[16];
  uint8_t rijndaelInput[16];
  uint8_t i;

  RijndaelKeySchedule(k);

  for (i = 0; i < 16; i++) rijndaelInput[i] = _rand[i] ^ opc[i];

  RijndaelEncrypt(rijndaelInput, temp);

  for (i = 0; i < 6; i++) {
    in1[i]     = sqn[i];
    in1[i + 8] = sqn[i];
  }

  for (i = 0; i < 2; i++) {
    in1[i + 6]  = amf[i];
    in1[i + 14] = amf[i];
  }

  /*
   * XOR op_c and in1, rotate by r1=64, and XOR
   * * * * on the constant c1 (which is all zeroes)
   */
  for (i = 0; i < 16; i++) rijndaelInput[(i + 8) % 16] = in1[i] ^ opc[i];

  /*
   * XOR on the value temp computed before
   */
  for (i = 0; i < 16; i++) rijndaelInput[i] ^= temp[i];

  RijndaelEncrypt(rijndaelInput, out1);
  for (i = 0; i < 16; i++) out1[i] ^= opc[i];

  for (i = 0; i < 8; i++) mac_a[i] = out1[i];

  return;
}

void Authentication_5gaka::f2345(
    const uint8_t opc[16], const uint8_t k[16], const uint8_t _rand[16],
    uint8_t res[8], uint8_t ck[16], uint8_t ik[16], uint8_t ak[6]) {
  uint8_t temp[16];
  uint8_t out[16];
  uint8_t rijndaelInput[16];
  uint8_t i;

  RijndaelKeySchedule(k);

  for (i = 0; i < 16; i++) rijndaelInput[i] = _rand[i] ^ opc[i];

  RijndaelEncrypt(rijndaelInput, temp);

  /*
   * To obtain output block OUT2: XOR OPc and TEMP,
   * * * * rotate by r2=0, and XOR on the constant c2 (which *
   * * * * is all zeroes except that the last bit is 1).
   */
  for (i = 0; i < 16; i++) rijndaelInput[i] = temp[i] ^ opc[i];

  rijndaelInput[15] ^= 1;
  RijndaelEncrypt(rijndaelInput, out);

  for (i = 0; i < 16; i++) out[i] ^= opc[i];

  for (i = 0; i < 8; i++) res[i] = out[i + 8];

  for (i = 0; i < 6; i++) ak[i] = out[i];
  /*
   * To obtain output block OUT3: XOR OPc and TEMP,
   * * * * rotate by r3=32, and XOR on the constant c3 (which *
   * * * * is all zeroes except that the next to last bit is 1).
   */

  for (i = 0; i < 16; i++) rijndaelInput[(i + 12) % 16] = temp[i] ^ opc[i];

  rijndaelInput[15] ^= 2;
  RijndaelEncrypt(rijndaelInput, out);

  for (i = 0; i < 16; i++) out[i] ^= opc[i];

  for (i = 0; i < 16; i++) ck[i] = out[i];

  /*
   * To obtain output block OUT4: XOR OPc and TEMP,
   * * * * rotate by r4=64, and XOR on the constant c4 (which *
   * * * * is all zeroes except that the 2nd from last bit is 1).
   */
  for (i = 0; i < 16; i++) rijndaelInput[(i + 8) % 16] = temp[i] ^ opc[i];

  rijndaelInput[15] ^= 4;
  RijndaelEncrypt(rijndaelInput, out);

  for (i = 0; i < 16; i++) out[i] ^= opc[i];

  for (i = 0; i < 16; i++) ik[i] = out[i];

  return;
} /* end of function f2345 */

void Authentication_5gaka::generate_autn(
    const uint8_t sqn[6], const uint8_t ak[6], const uint8_t amf[2],
    const uint8_t mac_a[8], uint8_t autn[16]) {
  for (int i = 0; i < 6; i++) {
    autn[i] = sqn[i] ^ ak[i];
  }
  memcpy(&autn[6], amf, 2);
  memcpy(&autn[8], mac_a, 8);

  return;
}

void Authentication_5gaka::annex_a_4_33501(
    uint8_t ck[16], uint8_t ik[16], uint8_t* input, uint8_t rand[16],
    std::string serving_network, uint8_t* output) {
  OCTET_STRING_t netName;
  OCTET_STRING_fromBuf(
      &netName, serving_network.c_str(), serving_network.length());
  uint8_t S[100];
  S[0] = 0x6B;
  memcpy(&S[1], netName.buf, netName.size);
  S[1 + netName.size] = (netName.size & 0xff00) >> 8;
  S[2 + netName.size] = (netName.size & 0x00ff);
  for (int i = 0; i < 16; i++) S[3 + netName.size + i] = rand[i];
  S[19 + netName.size] = 0x00;
  S[20 + netName.size] = 0x10;
  for (int i = 0; i < 8; i++) S[21 + netName.size + i] = input[i];
  S[29 + netName.size] = 0x00;
  S[30 + netName.size] = 0x08;
  /*
    uint8_t plmn[3] = {0x46, 0x0f, 0x11};
    uint8_t oldS[100];
    oldS[0] = 0x6B;
    memcpy(&oldS[1], plmn, 3);
    oldS[4] = 0x00;
    oldS[5] = 0x03;
    for (int i = 0; i < 16; i++)
      oldS[6 + i] = rand[i];
    oldS[22] = 0x00;
    oldS[23] = 0x10;
    for (int i = 0; i < 8; i++)
      oldS[24 + i] = input[i];
    oldS[32] = 0x00;
    oldS[33] = 0x08;
  */
  // comUt::print_buffer("udm_ueau", "Input string: ", S, 31 + netName.size);
  uint8_t key[32];
  memcpy(&key[0], ck, 16);
  memcpy(&key[16], ik, 16);  // KEY
  // Authentication_5gaka::kdf(key, 32, oldS, 33, output, 16);
  uint8_t out[32];
  Authentication_5gaka::kdf(key, 32, S, 31 + netName.size, out, 32);
  for (int i = 0; i < 16; i++) output[i] = out[16 + i];
  //comUt::print_buffer("udm_ueau", "XRES*(new)", out, 32);

  return;
}

void Authentication_5gaka::kdf(
    uint8_t* key, uint16_t key_len, uint8_t* s, uint16_t s_len, uint8_t* out,
    uint16_t out_len) {
  struct hmac_sha256_ctx ctx;
  memset(&ctx, 0, sizeof(ctx));
  hmac_sha256_set_key(&ctx, key_len, key);
  hmac_sha256_update(&ctx, s_len, s);
  hmac_sha256_digest(&ctx, out_len, out);

  return;
}

void Authentication_5gaka::derive_kausf(
    uint8_t ck[16], uint8_t ik[16], std::string serving_network, uint8_t sqn[6],
    uint8_t ak[6], uint8_t kausf[32]) {
  //Logger::udm_ueau().debug("derive_kausf ...");

  OCTET_STRING_t netName;
  OCTET_STRING_fromBuf(
      &netName, serving_network.c_str(), serving_network.length());

  uint8_t S[100];
  uint8_t key[32];
  memcpy(&key[0], ck, 16);
  memcpy(&key[16], ik, 16);  // KEY
  S[0] = 0x6A;
  memcpy(&S[1], netName.buf, netName.size);
  // memcpy (&S[1+netName.size], &netName.size, 2);
  S[1 + netName.size] = (uint8_t)((netName.size & 0xff00) >> 8);
  S[2 + netName.size] = (uint8_t)(netName.size & 0x00ff);
  for (int i = 0; i < 6; i++) {
    S[3 + netName.size + i] = sqn[i] ^ ak[i];
  }
  S[9 + netName.size]  = 0x00;
  S[10 + netName.size] = 0x06;

  //comUt::print_buffer("udm_ueau", "derive_kausf key", key, 32);
  kdf(key, 32, S, 11 + netName.size, kausf, 32);
  //comUt::print_buffer("udm_ueau", "derive_kausf kausf", kausf, 32);

  return;
}
