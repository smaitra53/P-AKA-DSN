#!/bin/bash

# Check if an argument is provided
if [ -z "$1" ]; then
  echo "Error: ./test iter thrd mem"
  exit 1
fi

iter=$1
thrd=$2
mem=$3

echo "Staring test."

for i in {1..10}
do
  # deploy 5G core
  docker-compose -f /home/smaitra/oai-cn5g-fed-sgx/docker-compose/docker-compose-basic-nrf.yaml up -d &> /dev/null
  sleep 2m
  # deploy fall-gautn module and sleep for 5 minutes until it comes online
  docker-compose -f /home/smaitra/external-module-docker-compose/docker-compose-fall-gautn.yaml up -d &> /dev/null
  sleep 30

  # deploy and undeploy gnbsim n times
  for j in {1..10}
  do
    date +"%r"
    # deploy gnbsim
    docker-compose -f /home/smaitra/oai-cn5g-fed-sgx/docker-compose/docker-compose-gnbsim.yaml up -d &> /dev/null
    # wait for it to come online
    sleep 40
    # retrieve the last line from the log and append in gnbsim.log
    docker logs -n 1 gnbsim &>> "gnbsim.log.$iter"
    # wait 2 seconds and undeploy gnbsim
    sleep 2
    docker-compose -f /home/smaitra/oai-cn5g-fed-sgx/docker-compose/docker-compose-gnbsim.yaml down &> /dev/null
    sleep 30
  done

  # write fall-gautn module logs to file
  docker logs -t fall-gautn-module 2> /dev/null 1> "temp.$i"
  cat temp.$i >> gsc-fall-gautn.log.$thrd.$mem
  sleep 2
  # undeploy fall-gautn module
  docker-compose -f /home/smaitra/external-module-docker-compose/docker-compose-fall-gautn.yaml down &> /dev/null
  sleep 2m
  docker-compose -f /home/smaitra/oai-cn5g-fed-sgx/docker-compose/docker-compose-basic-nrf.yaml down &> /dev/null
  sleep 2m
done

awk -i inplace '{sub(/^[[:space:]]+/,""); $1=""; print}' gsc-fall-gautn.log.$thrd.$mem
rm temp*
echo "Testing done."
