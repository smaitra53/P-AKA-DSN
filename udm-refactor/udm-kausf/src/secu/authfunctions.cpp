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
