import matplotlib.pyplot as plt
temperature = []
distance = []

finalTemp = []
finalDist = []
path = r"C:\Users\Kuba\Desktop\Seminární práce fyzika\MĚŘENÍ vztahů\data.txt"
result = {}

f = open(path, "r")
l = f.readlines()
for line in l: #roztřídí z informace dokumentu 
    a,b = line.split(",")
    temperature.append(float(b.strip()))
    distance.append(int(float(a.strip())))


for i in range(1, max(distance)): # zprůměruje hodnoty z měření 
    if( i > 79):
        break
    temp = 0
    howManyTimes = 0
    y = 0
    for number in distance:
        if i == number:
            temp += temperature[y]
            howManyTimes += 1
        y += 1
    finalDist.append(i)
    finalTemp.append(round(temp / howManyTimes, 1))

print(result)

plt.plot(finalDist, finalTemp)
  
# naming the x axis
plt.xlabel('vzdálenost [cm]')
# naming the y axis
plt.ylabel('teplota [°C]')
  
# function to show the plot
plt.show()
