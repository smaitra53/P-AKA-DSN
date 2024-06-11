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

void Authentication_5gaka::generate_Hxres(
    uint8_t rand[16], uint8_t xresStar[16], uint8_t* hxresStar) {
  uint8_t inputString[40];

  memcpy(&inputString[0], rand, 16);
  memcpy(&inputString[16], xresStar, 16);

  unsigned char sha256Out[Sha256::DIGEST_SIZE];
  Authentication_5gaka::sha256((unsigned char*) inputString, 32, sha256Out);
  for (int j = 0; j < 16; j++) hxresStar[j] = (uint8_t) sha256Out[j];
}

Sha256 ctx;
void Authentication_5gaka::sha256(
    unsigned char* message, int msg_len, unsigned char* output) {
  memset(output, 0, Sha256::DIGEST_SIZE);
  ctx.init();
  ctx.update(message, msg_len);
  ctx.finalResult(output);
}

