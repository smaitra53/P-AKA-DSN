/*
 * Re-factoring of the OAI-UDM code by seperating the f2345 3GPP 5GAKA function from the 
 * monolithic VNF
 *
 *
 * ! file basutil.hpp
 *  \brief
 * \author: Sudip Maitra and Tolga Omer Atalay
 * \Affiliation: VirginiaTech
 * \date: 2022
 * \email: tolgaoa@vt.edu
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


class basUtil {
	public: 
		/*
		* decode_base64: Decodes base64 encoded data
		* @param [const std::string] rec_str
		* @param [usigned char] buf[]
		* @param [int] _rand
		* @return void
		*/
		static void decode_base64( const std::string& rec_str, unsigned char buf[], int buf_len); 
				

};


#endif


