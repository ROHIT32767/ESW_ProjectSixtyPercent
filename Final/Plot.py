from ctypes import sizeof
from onem2m import *
import json
import matplotlib.pyplot as plt

content_LDR = []
content_PIR = []
content_Speed = []
creation_time = []

uri_cse = "http://127.0.0.1:8080/~/in-cse/in-name"
ae = "Lane-1"
cnt_LDR = "LDR"
cnt_PIR = "PIR"
cnt_Speed = "Speed"

uri_ae = uri_cse + "/" + ae
uri_cnt_LDR = uri_ae + "/" + cnt_LDR
uri_cnt_PIR = uri_ae + "/" + cnt_PIR
uri_cnt_Speed = uri_ae + "/" + cnt_Speed
'''
headers = {
    'X-M2M-Origin': 'admin:admin',
    'Content-type': 'application/json'
}'''

response = get_data(uri_ae + "/LDR?rcn=4")
print()


for data in response["m2m:cnt"]["m2m:cin"][::]:
    if (float(data["con"]) > 500):
        content_LDR.append(float(data["con"]))
        creation_time.append(data["ct"][-4:-2] + ":" + data["ct"][-2:])

ax = plt.gca()
ax.axes.xaxis.set_ticks([])
plt.xlabel("Time")
plt.ylabel("Value of LDR")
plt.plot(creation_time, content_LDR)
plt.show()

###################################################################################

# response = get_data(uri_ae + "/PIR?rcn=4")
# print()


# for data in response["m2m:cnt"]["m2m:cin"][-400::]:
#     content_PIR.append(float(data["con"]))
#     creation_time.append(data["ct"][-4:-2] + ":" + data["ct"][-2:])

# ax = plt.gca()
# ax.axes.xaxis.set_ticks([])
# plt.xlabel("Time")
# plt.ylabel("Value of PIR")
# plt.plot(creation_time, content_PIR)
# plt.show()


# ########################################################################################

# response = get_data(uri_ae + "/Speed?rcn=4")
# print()


# for data in response["m2m:cnt"]["m2m:cin"][::]:
#     if (float(data["con"]) < 20):
#         content_Speed.append(float(data["con"]))
#         creation_time.append(data["ct"][-4:-2] + ":" + data["ct"][-2:])

# ax = plt.gca()
# ax.axes.xaxis.set_ticks([])
# plt.xlabel("Time")
# plt.ylabel("Value of Speeds")
# plt.plot(creation_time, content_Speed)
# plt.show()


'''
while (len(content) < 10):
    response = requests.get(uri_cnt + "/la", headers=headers)
    y = json.loads(response.content)
    content.append(float(y['m2m:cin']['con']))
    creation_time.append(y['m2m:cin']['ct'])

print(content)
print(creation_time)'''