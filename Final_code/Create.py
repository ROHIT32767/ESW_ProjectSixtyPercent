from onem2m import *
uri_cse = "http://127.0.0.1:8080/~/in-cse/in-name"

ae = "Sensor_Readings"
cnt = ["Prana_PM2.5", "Prana_PM10", "CO2_Levels", "VOC_Levels", "Temperature", "Humidity"]

create_ae(uri_cse, ae)
uri_ae = uri_cse +"/"+ ae

for i in range(0, 6):
    create_cnt(uri_ae, cnt[i])
    uri_cnt = uri_ae + "/" + cnt[i]
    create_data_cin(uri_cnt, 0)
