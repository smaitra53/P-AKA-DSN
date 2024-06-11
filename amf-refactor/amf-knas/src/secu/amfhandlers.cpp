
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

	uint8_t amf_nea = EA0_5G;
	uint8_t amf_nia = IA0_5G;

        unsigned char kamfbuf[100];
        unsigned char knasintbuf[100];
        unsigned char knasencbuf[100];
        
	int buflen;
        decode_base64(kvpairs[0], kamfbuf, buflen);


	Authentication_5gaka::derive_knas(
		NAS_INT_ALG, amf_nia,
		kamfbuf, knasintbuf);

	Authentication_5gaka::derive_knas(
		NAS_ENC_ALG, amf_nea,
		kamfbuf, knasencbuf);

        std::string knasint_send;
        std::string knasenc_send;
        encode_base64(knasint_send, knasintbuf, 32);
        encode_base64(knasenc_send, knasencbuf, 32);
        std::cout << &knasintbuf << std::endl;
        std::cout << &knasencbuf << std::endl;

        response_send = knasint_send + "&" + knasenc_send;
}
