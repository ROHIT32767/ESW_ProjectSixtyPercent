from onem2m import *
uri_cse = "https://esw-onem2m.iiit.ac.in:443/~/in-cse/in-name"

ae = "Team-18"
cnt = ["Prana_PM2.5", "Prana_PM10", "CO2_Levels", "VOC_Levels", "Temperature", "Humidity"]

uri_ae = uri_cse + "/" + ae

for i in range(0, 6):
    uri_cnt = uri_ae + "/" + cnt[i]
    delete(uri_cnt)
    create_cnt(uri_ae, cnt[i])
    create_data_cin(uri_cnt, 0)