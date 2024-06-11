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

void Authentication_5gaka::derive_knas(
    algorithm_type_dist_t nas_alg_type, uint8_t nas_alg_id, uint8_t kamf[32],
    uint8_t* knas) {
  //Logger::amf_n1().debug("derive_knas ...");
  uint8_t S[20];
  uint8_t out[32] = {0};
  S[0]            = 0x69;  // FC
  S[1]            = (uint8_t)(nas_alg_type & 0xFF);
  S[2]            = 0x00;
  S[3]            = 0x01;
  S[4]            = nas_alg_id;
  S[5]            = 0x00;
  S[6]            = 0x01;
  // comUt::print_buffer("amf_n1", "inputstring S", S, 7);
  // comUt::print_buffer("amf_n1", "key KEY", kamf, 32);
  kdf(kamf, 32, S, 7, out, 32);
  // memcpy (knas, &out[31 - 16 + 1], 16);
  for (int i = 0; i < 16; i++) knas[i] = out[16 + i];
  // comUt::print_buffer("amf_n1", "knas", knas, 16);
  // Logger::amf_n1().debug("derive knas finished!");
}

