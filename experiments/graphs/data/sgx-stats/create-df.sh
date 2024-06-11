#!/bin/bash

iter=2

cat logs.$iter | grep EENTER 	| awk '{if ($4<2000) print $4 }' >> EENTERs.$iter
cat logs.$iter | grep EEXIT	| awk '{if ($4<2000) print $4 }' >> EEXITs.$iter
cat logs.$iter | grep AEX 	| awk '{ print $4 }' >> AEXs.$iter
cat logs.$iter | grep -w sync 	| awk '{ print $5 }' >> SYNC.$iter
cat logs.$iter | grep -w async 	| awk '{ print $5 }' >> ASYNC.$iter

echo '"EENTERs","EEXITs","AEXs","SYNC","ASYNC"' >> sgx-stats.$iter

paste -d ',' EENTERs.$iter EEXITs.$iter AEXs.$iter SYNC.$iter ASYNC.$iter >> sgx-stats.$iter
