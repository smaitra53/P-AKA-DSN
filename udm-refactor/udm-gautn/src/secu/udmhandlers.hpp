/*
 * Re-factoring of the OAI-UDM code by seperating the f1 3GPP 5GAKA function from the 
 * monolithic VNF
 *
 *
 * ! file udmhandlers.hpp
 *  \brief
 * \author: Tolga Atalay / Sudip Maitra
 * \Affiliation: VirginiaTech
 * \date: 2022
 * \email: tolgaoa@vt.edu
*/

#ifndef _UDM_HANDLERS_H_
#define _UDM_HANDLERS_H_

#include <gmp.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <string>

#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/router.h>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

#include "spdlog/spdlog.h"

#include "rapidjson/document.h"

#include "authfunc.hpp"

#include <openssl/evp.h>

class udmhandlers {
	public: 
		/*
		* handlef2345: handler for the f2345 function
		* @param [std::string& req] body of incoming Pistache HTTP request
		* @param [std::string& response_send] the response to be sent over HTTP
		* @return void
		*/
		void internal_gautn ( const std::string& req, std::string& response_send); 
				

};


#endif


