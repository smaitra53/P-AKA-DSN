
/*! udmhandlers.cpp
 \brief
 \author  Tolga Atalay / Sudip Maitra
 \affiliation VirginiaTech
 \date 2022
 \email: tolgaoa@vt.edu
 */

#include "ausfhandlers.hpp"

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

void ausfhandlers::internalhandler(const std::string& req, std::string& response_send) {
        std::map<std::string, std::string> request;
        std::vector<std::string> kvpairs;
        boost::split(kvpairs, req, boost::is_any_of("&"), boost::token_compress_on);

        for (auto i : kvpairs){
                spdlog::debug("Value: {}", i);
        }

        unsigned char randausfbuf[100];
        unsigned char kausfbuf[100];
        unsigned char xressausfbuf[100];
        unsigned char hxresStarbuf[100];
        unsigned char kseafbuf[100];
        
	int buflen;
        decode_base64(kvpairs[0], randausfbuf, buflen);
        decode_base64(kvpairs[1], xressausfbuf, buflen);
	std::string snn = kvpairs[2];	
        decode_base64(kvpairs[3], kausfbuf, buflen);

        Authentication_5gaka::generate_Hxres(randausfbuf, xressausfbuf, hxresStarbuf);
	Authentication_5gaka::derive_kseaf(snn, kausfbuf, kseafbuf);
	
        std::string kseaf_send;
        std::string hxress_send;

        encode_base64(kseaf_send, kseafbuf, 32);
        encode_base64(hxress_send, hxresStarbuf, 8);

        response_send = kseaf_send + "&" + hxress_send;
}
