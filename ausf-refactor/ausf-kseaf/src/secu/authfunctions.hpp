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

#ifndef _5GAKA_H_
#define _5GAKA_H_

// extern "C"{
#include <gmp.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#include <string>


#include "sha256.hpp"

#include "OCTET_STRING.h"
//}

#define SQN_LENGTH_BITS (48)
#define SQN_LENGTH_OCTEST (SQN_LENGTH_BITS / 8)
#define IK_LENGTH_BITS (128)
#define IK_LENGTH_OCTETS (IK_LENGTH_BITS / 8)
#define RAND_LENGTH_OCTETS (16)
#define RAND_LENGTH_BITS (RAND_LENGTH_OCTETS * 8)
#define XRES_LENGTH_OCTETS (8)
#define AUTN_LENGTH_OCTETS (16)
#define KASME_LENGTH_OCTETS (32)
#define MAC_S_LENGTH (8)

typedef mpz_t random_t;

typedef struct random_state_s {
  pthread_mutex_t lock;
  gmp_randstate_t state;
} random_state_t;

class Authentication_5gaka {
	public:

		static void kdf(
			uint8_t* key, uint16_t key_len, uint8_t* s, uint16_t s_len, uint8_t* out,
			uint16_t out_len);
		static void derive_kseaf(
		      std::string serving_network, uint8_t kausf[32], uint8_t kseaf[32]);
		
};


#endif


