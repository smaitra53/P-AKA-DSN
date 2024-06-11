
/*! udmhandlers.cpp
 \brief
 \author Sudip Maitra and Tolga Omer Atalay
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

void udmhandlers::internalf2345(const std::string& req, std::string& response_send) {
        std::map<std::string, std::string> request;
        std::vector<std::string> kvpairs; 
        boost::split(kvpairs, req, boost::is_any_of("&"), boost::token_compress_on);

        for (auto i : kvpairs){
                spdlog::debug("Value: {}", i);
        }

        unsigned char opcbuf[100];
        unsigned char keybuf[100];
        unsigned char randbuf[100];
        unsigned char xresbuf[100];
        unsigned char ckbuf[100];
        unsigned char ikbuf[100];
        unsigned char akbuf[100];
        int buflen;
        decode_base64(kvpairs[0], opcbuf, buflen);
        decode_base64(kvpairs[1], keybuf, buflen);
        decode_base64(kvpairs[2], randbuf, buflen);

        Authentication_5gaka::f2345(
                opcbuf, keybuf, randbuf, xresbuf, ckbuf, ikbuf,
                akbuf);  // to compute XRES, CK, IK, AK

        std::string xres_send;
        std::string ck_send;
        std::string ik_send;
        std::string ak_send;

        encode_base64(xres_send, xresbuf, 16);        
        encode_base64(ck_send, ckbuf, 16);        
        encode_base64(ik_send, ikbuf, 16);        
        encode_base64(ak_send, akbuf, 6);

        response_send = xres_send + "&" + ck_send + "&" + ik_send + "&" + ak_send;
}
