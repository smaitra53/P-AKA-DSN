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

#include "authfunc.hpp"
#include <string.h>

void Authentication_5gaka::generate_autnrem(
    const uint8_t sqn[6], const uint8_t ak[6], const uint8_t amf[2],
    const uint8_t mac_a[8], uint8_t autnrem[16]) {
  for (int i = 0; i < 6; i++) {
    autnrem[i] = sqn[i] ^ ak[i];
  }
  memcpy(&autnrem[6], amf, 2);
  memcpy(&autnrem[8], mac_a, 8);

  return;
}

