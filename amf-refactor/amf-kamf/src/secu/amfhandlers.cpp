
/*! udmhandlers.cpp
 \brief
 \author  Tolga Atalay / Sudip Maitra
 \affiliation VirginiaTech
 \date 2022
 \email: tolgaoa@vt.edu
 */

#include "amfhandlers.hpp"

void encode_base64(std::string& send_str, unsigned char buf[], int buf_len){
        char encodedData[100];
        int encoded_data_len = EVP_EncodeBlock((unsigned char*)encodedData, buf, buf_len);
        for(int i=0; i < encoded_data_len; i++){
                send_str.push_back(encodedData[i]);
        }
}

void decode_base64(const std::string& rec_str, unsigned char buf[], int buf_len){
    int rec_str_len = rec_str.length();
    char rec_char_array[rec_str_len+1];
    strcpy(rec_char_array, rec_str.c_str());
    //unsigned char buf[100];
    buf_len = EVP_DecodeBlock(buf, (unsigned char*)rec_char_array, rec_str_len);
}

void amfhandlers::internalhandler(const std::string& req, std::string& response_send) {
        std::map<std::string, std::string> request;
        std::vector<std::string> kvpairs;
        boost::split(kvpairs, req, boost::is_any_of("&"), boost::token_compress_on);

        for (auto i : kvpairs){
                spdlog::debug("Value: {}", i);
        }

        unsigned char kseafbuf[100]; 
        unsigned char kamfbuf[100]; 
	int buflen;
	std::string imsi = kvpairs[0];
        decode_base64(kvpairs[1], kseafbuf, buflen);

	Authentication_5gaka::derive_kamf(
		imsi, kseafbuf, kamfbuf, 0x0000);

        std::string kamf_send;
        encode_base64(kamf_send, kamfbuf, 32);
	std::cout << &kamfbuf << std::endl;	

        response_send = kamf_send;
}
