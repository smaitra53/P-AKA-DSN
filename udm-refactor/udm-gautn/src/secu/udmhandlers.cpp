
/*! udmhandlers.cpp
 \brief
 \author Tolga Atalay / Sudip Maitra
 \affiliation VirginiaTech
 \date 2022
 \email: tolgaoa@vt.edu
 */

#include "udmhandlers.hpp"

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

void udmhandlers::internal_gautn(const std::string& req, std::string& response_send) {
        std::map<std::string, std::string> request;
        std::vector<std::string> kvpairs; 
        boost::split(kvpairs, req, boost::is_any_of("&"), boost::token_compress_on);

        for (auto i : kvpairs){
                spdlog::debug("Value: {}", i);
        }

        unsigned char sqnbuf[100];
        unsigned char akbuf[100];
        unsigned char amfbuf[100];
        unsigned char macabuf[100];
        unsigned char autnbuf[100];
        int buflen;
        decode_base64(kvpairs[0], sqnbuf, buflen);
        decode_base64(kvpairs[1], akbuf, buflen);
        decode_base64(kvpairs[2], amfbuf, buflen);
        decode_base64(kvpairs[3], macabuf, buflen);

	Authentication_5gaka::generate_autnrem(
		sqnbuf, akbuf, amfbuf, macabuf, autnbuf);  // generate AUTN

  	std::string autn_send;	
        encode_base64(autn_send, autnbuf, 16);
	spdlog::debug("Computed AUTN: {}", autn_send);	
	std::cout <<  &autnbuf << std::endl;	


        response_send = autn_send;
}
