/*
 * Re-factoring of the OAI-UDM code by seperating the f1 3GPP 5GAKA function from the 
 * monolithic VNF
 *
 *
 * ! file main.cpp
 *  \brief
 * \author: Tolga Atalay / Sudip Maitra
 * \Affiliation: VirginiaTech
 * \date: 2022
 * \email: tolgaoa@vt.edu
*/

#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/router.h>

#include "rapidjson/document.h"

#include <iostream>
#include "spdlog/spdlog.h"

#include "udmhandlers.hpp"

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

#include <openssl/evp.h>

using namespace Pistache;

void handle(const Rest::Request& req, Http::ResponseWriter resp){


        spdlog::debug("Receiving Authentication credentials: {}", req.body());
	std::string response_send;
	udmhandlers handler1;
	
	handler1.internal_handler(req.body(), response_send);
        resp.send(Pistache::Http::Code::Ok, response_send);

}

int main(int argc, char* argv[])
{
	spdlog::set_level(spdlog::level::debug);
	using namespace Rest;

	Router router;
	Port port(9090);
	Address addr(Ipv4::any(), port);
	std::shared_ptr<Http::Endpoint> endpoint = std::make_shared<Http::Endpoint>(addr);
	auto opts = Http::Endpoint::options().threads(2);
	opts.flags(Pistache::Tcp::Options::ReuseAddr);
	endpoint->init(opts);

	Routes::Post(router, "/fall_gautn", Routes::bind(handle));

	spdlog::info("Starting HTTP Server for UDM-5GAKA Function: fall-generate_autn");
	endpoint->setHandler(router.handler());
	endpoint->serve();
}
