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

#include "f1.hpp"

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
