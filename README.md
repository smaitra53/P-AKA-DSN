# P-AKA DSN Source -- OpenAirInterface Refactored Modules

The 5G core VNFs included as tar.gz files are modified versions of the [OpenAirInterface 5G core VNFs](https://gitlab.eurecom.fr/oai/cn5g)

OAI 5G core VNFs require an extended TIMEOUT period so as not to crash while working with P-AKA. Thus, the OAI 5G core VNF images with increased API TIMEOUT are marked with a (+++) below.

Isolating the critical micro-services of 5G core components to protect them against co-residency attacks. 

## UDM Status 
### <strong>Isolated Microservices</strong>
 - :heavy_check_mark: - f1
 - :heavy_check_mark: - f2345
 - :heavy_check_mark: - generate_autn
 - >> For using the f1-f2345-gautn modules seperately -- tolgaomeratalay/udm:modfall_autn_v2
 - :heavy_check_mark: - derive_kausf
 - >> For using the f1-f2345-gautn-kausf modules seperately -- tolgaomeratalay/udm:f1_f2345_gautn_kausfv3 </strong>(+++)</strong>
 - :heavy_check_mark: - All-in-one -- {f1 + f23345 + generate_autn}  
 - >> For using the all-in-one {f1+f2345+gautn} module tolgaomeratalay/udm:fall_gautn_v1 

## AUSF Status
### <strong>Isolated Microservices</strong>
 - :heavy_check_mark: - generate_Hxres
 - :heavy_check_mark: - derive_kseaf
 - >> For using only the derive_kseaf -- tolgaomeratalay/ausf:kseafv1
 - >> For using derive_kseaf and genHxres seperately -- tolgaomeratalay/ausf:kseaf_ghxresv1
 - :heavy_check_mark: - All-in-one -- {generateHxres + derive_kseaf}
 - >> For using derive_kseaf and genHxres all-in-one -- tolgaomeratalay/ausf:mod_allv3 </strong>(+++)</strong>

## AMF Status
### <strong>Isolated Microservices</strong>
 - :heavy_check_mark: - derive_kamf
 - >> For using only the derive_kamf -- tolgaomeratalay/amf:kamfv3 </strong>(+++)</strong> - v1.2.1
 - >> For using only the derive_kamf -- tolgaomeratalay/amf:kamfv4 </strong>(+++)</strong> - v1.5.0

