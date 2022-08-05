
import serial
import time
import matplotlib.pyplot as plt
import sys

ser = serial.Serial('COM3',9600) # This is mac port for windows it will be like COM1
data = {}
time = [60,120,180,240,300,360,420,480,540,600];
count = 1
for t in time:
   data[t] = 0.0
while count <= 30:
    line = ser.readline()  # read a byte
    string = line.decode()
    if 'BME' not in string: 
        print(len(string),string,string[0],string[1])
        string_list = string
        print(string_list) 
        index = (count -1) % 10
        print(index, time[index])
        data[time[index]] += float(string_list)
        print(data)
        count += 1
        
ser.close() # close the connection
print(len(data))
temp_values =[]
for k,v in data.items():
  temp_values.append(v/10)

#with open(sys.argv[0]+".txt", "w") as output:
#  for i in range(0,len(data)):
#    if i != len(data)-1:
#      output.write(str(data[i]))
#      output.write(",")
#      print("writing record", i, data[i])
#    else:
#      output.write(str(data[4]))
#output.close()

fig = plt.figure(figsize=(10,5))
plt.bar(time,temp_values,color='red')
plt.xlabel('Time')
plt.ylabel('Gas Reading')
plt.title('BME680 Gas Sensor')
plt.savefig('BME680 Gas Sensor readings')
plt.show()
