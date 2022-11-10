from onem2m import *
uri_cse = "http://127.0.0.1:8080/~/in-cse/in-name"

ae1 = "Lane-1"
ae2 = "Lane-2"
ae3 = "Test"
cnt_LDR = "LDR"
cnt_PIR = "PIR"
cnt_Speed = "Speed"
cnt_Humid = "Humidity"
# cnt_Humid = "Humidity"

uri_ae1 = uri_cse +"/"+ ae1
uri_cnt1_LDR = uri_ae1 + "/" + cnt_LDR
uri_cnt1_PIR = uri_ae1 + "/" + cnt_PIR
uri_cnt1_Speed = uri_ae1 + "/" + cnt_Speed

delete(uri_cnt1_LDR)
delete(uri_cnt1_PIR)
delete(uri_cnt1_Speed)

create_cnt(uri_ae1, cnt_LDR)
uri_cnt1_LDR = uri_ae1 + "/" + cnt_LDR

create_cnt(uri_ae1, cnt_PIR)
uri_cnt1_PIR = uri_ae1 + "/" + cnt_PIR

create_cnt(uri_ae1, cnt_Speed)
uri_cnt1_Speed = uri_ae1 + "/" + cnt_Speed

uri_ae2 = uri_cse +"/"+ ae2
uri_cnt2_LDR = uri_ae2 + "/" + cnt_LDR
uri_cnt2_PIR = uri_ae2 + "/" + cnt_PIR
uri_cnt2_Speed = uri_ae2 + "/" + cnt_Speed

delete(uri_cnt2_LDR)
delete(uri_cnt2_PIR)
delete(uri_cnt2_Speed)

create_cnt(uri_ae2, cnt_LDR)
uri_cnt2_LDR = uri_ae2 + "/" + cnt_LDR

create_cnt(uri_ae2, cnt_PIR)
uri_cnt2_PIR = uri_ae2 + "/" + cnt_PIR

create_cnt(uri_ae2, cnt_Speed)
uri_cnt2_Speed = uri_ae2 + "/" + cnt_Speed

uri_ae3 = uri_cse +"/"+ ae3
uri_cnt3_Humid = uri_ae3 + "/" + cnt_Humid

# delete(uri_cnt3_Humid)
