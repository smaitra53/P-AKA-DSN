#!/bin/sh
# script to replace host interface names in multus files 
# might have to fiddle with field and line number to capture the correct name in hostInterface variable
hostInterface=$(nmcli connection show | awk 'FNR == 2 {print $6}')
sed -i "s|\"master\":.*|\"master\": \"$hostInterface\",|" udm-f2345/deployment/01_multus.yaml
sed -i "s|\"master\":.*|\"master\": \"$hostInterface\",|" udm-f1/deployment/01_multus.yaml
sed -i "s|\"master\":.*|\"master\": \"$hostInterface\",|" udm-gautn/deployment/01_multus.yaml
sed -i "s|\"master\":.*|\"master\": \"$hostInterface\",|" udm-fall-gautn/deployment/01_multus.yaml
