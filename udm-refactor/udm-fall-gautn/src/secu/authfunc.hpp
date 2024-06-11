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


class Authentication_5gaka {
	public: 
		/*
		* f1: Computes network authentication code MAC-A from key K, random,
		challenge RAND, sequence number SQN and authentication management field AMF.
		* @param [const uint8_t[16]] opc
		* @param [const uint8_t[16]] k
		* @param [const uint8_t[16]] _rand
		* @param [const uint8_t[6]] sqn
		* @param [const uint8_t[2]] amf
		* @param [uint8_t[8]] mac_a
		* @return
		*/
		static void f1(
			const uint8_t opc[16], const uint8_t k[16], const uint8_t _rand[16],
			const uint8_t sqn[6], const uint8_t amf[2], uint8_t mac_a[8]);

                static void f2345( const uint8_t opc[16], const uint8_t k[16], const uint8_t _rand[16],
                                   uint8_t res[8], uint8_t ck[16], uint8_t ik[16], uint8_t ak[6]);	

		static void generate_autnrem(
			const uint8_t sqn[6], const uint8_t ak[6], const uint8_t amf[2],
			const uint8_t mac_a[8], uint8_t autnrem[16]);
		
		static void RijndaelKeySchedule(const uint8_t key[16]);
		static void RijndaelEncrypt(const uint8_t in[16], uint8_t out[16]);
};


#endif


