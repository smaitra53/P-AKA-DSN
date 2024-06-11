#!/bin/bash

i=4
j="384M"
docker rmi udm-fall-gautn:t$i-$j gsc-udm-fall-gautn:t$i-$j-unsigned gsc-udm-fall-gautn:t$i-$j


#i=4
#j="384M"
#sed -i "s/max_threads = [0-9]*/max_threads = $i/" /home/smaitra/gsc/udm-fall-gautn.manifest.bak
#sed -i "s/sgx.enclave_size = \".*\"/sgx.enclave_size = \"$j\"/" /home/smaitra/gsc/udm-fall-gautn.manifest.bak
#cd /home/smaitra/gsc/ 
#docker tag 62b51916a3c9 udm-fall-gautn:t$i-$j
#./gsc build --rm -d udm-fall-gautn:t$i-$j udm-fall-gautn.manifest.bak
#./gsc sign-image udm-fall-gautn:t$i-$j ~/.config/gramine/enclave-key.pem

# i=10
# docker tag 62b51916a3c9 udm-fall-gautn:thread_$i
# sed -i "s/max_threads = [0-9]*/max_threads = $i/" /home/smaitra/gsc/udm-fall-gautn.manifest.bak
# cd /home/smaitra/gsc/
# ./gsc build --rm -d udm-fall-gautn:thread_$i udm-fall-gautn.manifest.bak
# ./gsc sign-image udm-fall-gautn:thread_$i ~/.config/gramine/enclave-key.pem


# for i in {10..100..10}
# do
#     # retag udm image
#     docker tag 62b51916a3c9 udm-fall-gautn:thread_$i
#     # build gsc image
#     sed -i "s/max_threads = [0-9]*/max_threads = $i/" /home/smaitra/gsc/udm-fall-gautn.manifest.bak
#     cd /home/smaitra/gsc/ 
#     ./gsc build --rm -d udm-fall-gautn:thread_$i udm-fall-gautn.manifest.bak &> /dev/null
#     ./gsc sign-image udm-fall-gautn:thread_$i ~/.config/gramine/enclave-key.pem &> /dev/null
#     sleep 1m
# done







# sed -i 's/sgx.enclave_size = "[^"]*"/sgx.enclave_size = "512M"/' /home/smaitra/gsc/udm-fall-gautn.manifest.bak
