import matplotlib.pyplot as plt
import numpy as np
import scipy

f = open("log1.txt", "r")
lines = f.readlines()
data =[]
for line in lines:
    line = line.replace("\n", "")
    line=int(line,16)
    line=(line/(2**15-1))-1
    data.append(line)
u1=np.asarray(data, dtype=np.float32)

f = open("log.txt", "r")
lines = f.readlines()
data =[]
for line in lines:
    line = line.replace("\n", "")
    line=int(line,16)
    line=(line/(2**15-1))-1
    data.append(line)
u2=np.asarray(data, dtype=np.float32)


data=np.asarray(u2, dtype=np.float32)
fig1, (ax1_1, ax2_1) = plt.subplots(1, 2)
fig1.suptitle('White Noise Generator Results')
count, bins, ignored = ax1_1.hist(data, 30, density=True)
ax1_1.plot(bins, 1/(np.std(data) * np.sqrt(2 * np.pi)) *np.exp( - (bins - data.mean())**2 / (2 * np.std(data)**2) ),linewidth=2, color='r')
ax1_1.set(xlabel='Amplitude',ylabel='samples')
ax2_1.specgram(data, Fs= 1, NFFT= 128, noverlap=64)
ax2_1.set(xlabel='Seconds',ylabel='Frequency')
plt.show()
