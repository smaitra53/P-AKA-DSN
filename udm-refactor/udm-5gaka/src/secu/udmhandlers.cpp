
/*! udmhandlers.cpp
 \brief
 \author  Tolga Omer Atalay
 \affiliation VirginiaTech
 \date 2022
 \email: tolgaoa@vt.edu
 */

#include "udmhandlers.hpp"

void decode_base64(const std::string& rec_str, unsigned char buf[], int buf_len){
    int rec_str_len = rec_str.length();
    char rec_char_array[rec_str_len+1];
    strcpy(rec_char_array, rec_str.c_str());
    //unsigned char buf[100];
    buf_len = EVP_DecodeBlock(buf, (unsigned char*)rec_char_array, rec_str_len);
}

void udmhandlers::internalaka(const std::string& req, std::string& response_send) {
	uint8_t rand[16] = {0};
	uint8_t mac_a[8]     = {0};
	uint8_t ck[16]       = {0};
	uint8_t ik[16]       = {0};
	uint8_t ak[6]        = {0};
	uint8_t xres[8]      = {0};
	uint8_t xresStar[16] = {0};
	uint8_t autn[16]     = {0};
	uint8_t kausf[32]    = {0};

        std::map<std::string, std::string> request;
        std::vector<std::string> kvpairs; 
        boost::split(kvpairs, req, boost::is_any_of("&"), boost::token_compress_on);

        for (auto i : kvpairs){
                spdlog::debug("Value: {}", i);
        }

        unsigned char opcbuf[100];
        unsigned char keybuf[100];
        unsigned char sqnbuf[100];
        unsigned char amfbuf[100];
        int buflen;
        decode_base64(kvpairs[0], opcbuf, buflen);
        decode_base64(kvpairs[1], keybuf, buflen);
        decode_base64(kvpairs[2], sqnbuf, buflen);
        decode_base64(kvpairs[3], amfbuf, buflen);
	std::string snn = kvpairs[4];	

	Authentication_5gaka::generate_random(rand, 16);  // generate rand
	Authentication_5gaka::f1(
		opcbuf, keybuf, rand, sqnbuf, amfbuf,
		mac_a);  // to compute mac_a
	Authentication_5gaka::f2345(
		opcbuf, keybuf, rand, xres, ck, ik,
		ak);  // to compute XRES, CK, IK, AK
	Authentication_5gaka::generate_autn(
		sqnbuf, ak, amfbuf, mac_a,
		autn);  // generate AUTN
	Authentication_5gaka::annex_a_4_33501(
		ck, ik, xres, rand, snn,
		xresStar);  // generate xres*
	Authentication_5gaka::derive_kausf(
		ck, ik, snn, sqnbuf, ak,
		kausf);  // derive Kausf

        std::string kausf_send;
        char encodedData[100]; 
        int encoded_data_len = EVP_EncodeBlock((unsigned char*)encodedData, kausf, 32);
        for(int i=0; i < encoded_data_len; i++){
                kausf_send.push_back(encodedData[i]);
        }

        std::string rand_send;
        encoded_data_len = EVP_EncodeBlock((unsigned char*)encodedData, rand, 16);
        for(int i=0; i < encoded_data_len; i++){
                rand_send.push_back(encodedData[i]);
        }

        std::string xress_send;
        encoded_data_len = EVP_EncodeBlock((unsigned char*)encodedData, xresStar, 16);
        for(int i=0; i < encoded_data_len; i++){
                xress_send.push_back(encodedData[i]);
        }

        std::string autn_send;
        encoded_data_len = EVP_EncodeBlock((unsigned char*)encodedData, autn, 16);
        for(int i=0; i < encoded_data_len; i++){
                autn_send.push_back(encodedData[i]);
        }

        response_send = rand_send + "&" + autn_send + "&" + kausf_send + "&" + xress_send;
                        

}
