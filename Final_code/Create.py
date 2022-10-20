from onem2m import *
uri_cse = "http://127.0.0.1:8080/~/in-cse/in-name"

ae1 = "Test"

cnt1 = "Temperature"

create_ae(uri_cse,ae1)
uri_ae1 = uri_cse +"/"+ ae1

create_cnt(uri_ae1, cnt1)
uri_cnt1 = uri_ae1 + "/" + cnt1
create_data_cin(uri_cnt1,28.0)