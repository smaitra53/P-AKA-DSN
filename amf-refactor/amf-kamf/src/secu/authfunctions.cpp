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

void Authentication_5gaka::derive_kamf(
    std::string imsi, uint8_t* kseaf, uint8_t* kamf, uint16_t abba) {
  std::string ueSupi = imsi;  // OK
  // Logger::amf_n1().debug("inputstring: supi(%s)", ueSupi.c_str());
  // int supiLen = (imsi.length()*sizeof(unsigned char))/2;
  // unsigned char * supi = (unsigned char*)calloc(1, supiLen);
  // hexStr2Byte(imsi.c_str(), supi, imsi.length());
  OCTET_STRING_t supi;
  OCTET_STRING_fromBuf(&supi, ueSupi.c_str(), ueSupi.length());
  // uint8_t supi[8] = {0x64, 0xf0, 0x11, 0x10, 0x32, 0x54, 0x76, 0x98};
  int supiLen = supi.size;
  // comUt::print_buffer("amf_n1", "inputstring: supi(hex)", supi.buf, supiLen);
  uint8_t S[100];
  S[0] = 0x6D;  // FC = 0x6D
  memcpy(&S[1], supi.buf, supiLen);
  // memcpy (&S[1+supiLen], &supiLen, 2);
  S[1 + supiLen] = (uint8_t)((supiLen & 0xff00) >> 8);
  S[2 + supiLen] = (uint8_t)(supiLen & 0x00ff);
  S[3 + supiLen] = abba & 0x00ff;
  S[4 + supiLen] = (abba & 0xff00) >> 8;
  S[5 + supiLen] = 0x00;
  S[6 + supiLen] = 0x02;
  // comUt::print_buffer("amf_n1", "inputstring S", S, 7+supiLen);
  // comUt::print_buffer("amf_n1", "key KEY", kseaf, 32);
  kdf(kseaf, 32, S, 7 + supiLen, kamf, 32);
  // comUt::print_buffer("amf_n1", "KDF out: Kamf", kamf, 32);
  // Logger::amf_n1().debug("derive kamf finished!");
}
