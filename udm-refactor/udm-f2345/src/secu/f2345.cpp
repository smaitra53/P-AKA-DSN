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

#include "f2345.hpp"

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
