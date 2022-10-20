from onem2m import *
uri_cse = "http://127.0.0.1:8080/~/in-cse/in-name"

ae1 = "Lane-1"
ae2 = "Lane-2"

cnt1 = "LDR"
cnt2 = "PIR"
cnt3 = "Speed"

create_ae(uri_cse,ae1)
uri_ae1 = uri_cse +"/"+ ae1

create_cnt(uri_ae1, cnt1)
uri_cnt1 = uri_ae1 + "/" + cnt1
create_data_cin(uri_cnt1,190)

create_cnt(uri_ae1, cnt2)
uri_cnt2 = uri_ae1 + "/" + cnt2
create_data_cin(uri_cnt2,190)

create_cnt(uri_ae1, cnt3)
uri_cnt3 = uri_ae1 + "/" + cnt3
create_data_cin(uri_cnt3,190)

#################################################

create_ae(uri_cse,ae2)
uri_ae2 = uri_cse +"/"+ ae2

create_cnt(uri_ae2, cnt1)
uri_cnt1 = uri_ae2 + "/" + cnt1
create_data_cin(uri_cnt1,190)

create_cnt(uri_ae2, cnt2)
uri_cnt2 = uri_ae2 + "/" + cnt2
create_data_cin(uri_cnt2,190)

create_cnt(uri_ae2, cnt3)
uri_cnt3 = uri_ae2 + "/" + cnt3
create_data_cin(uri_cnt3,190)


