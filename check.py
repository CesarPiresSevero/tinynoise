import matplotlib.pyplot as plt
import numpy as np
import scipy

plot_title = "Numpy Random Uniform"

def get_fft(array,fs):
    ts=1/(int(fs))
    t=np.arange(0,(len(array)*ts),ts)
    n=np.size(t)
    fr=(int(fs)/2)*np.linspace(0,1,int(n/2))
    resp=np.fft.fft(array)
    freq=(2/n)*abs(resp[0:np.size(fr)]) 
    #(2/n) is for normalizing since the FFT size is set as the size of the input array 
    # FFT amplitude is always half of the FFT points
    # In this case N-FFT ( np.fft.fft(array,len(array)) ) is the same as the lenght of the input array ( len(array) )
    return freq,fr,t #Array, frequency in hz, time in sec
# f = open("log1.txt", "r")
# lines = f.readlines()
# data =[]
# for line in lines:
#     line = line.replace("\n", "")
#     line=int(line,16)
#     line=(line/(2**15-1))-1
#     data.append(line)
# u1=np.asarray(data, dtype=np.float32)

f = open("log.txt", "r")
lines = f.readlines()
data =[]
for line in lines:
    line = line.replace("\n", "")
    line=int(line,16)
    line=(line/(2**15-1))-1
    data.append(line)
u2=np.asarray(data, dtype=np.float32)

# u2=np.random.normal(size=10**5)
u2=np.random.uniform(size=10**5)

Tinnitus_array_fft,Tinnitus_fr,Tinnitus_t=get_fft(u2,1)

data=np.asarray(u2, dtype=np.float32)
fig1, (ax1_1, ax2_1) = plt.subplots(1, 2)
fig1.suptitle(plot_title)
count, bins, ignored = ax1_1.hist(data, 30, density=True)
ax1_1.plot(bins, 1/(np.std(data) * np.sqrt(2 * np.pi)) *np.exp( - (bins - data.mean())**2 / (2 * np.std(data)**2) ),linewidth=2, color='r')
ax1_1.set(xlabel='Amplitude',ylabel='samples')
ax2_1.specgram(data, Fs= 1, NFFT= 128, noverlap=64)
ax2_1.set(xlabel='Seconds',ylabel='Frequency')
plt.show()




plt.figure()
plt.ylabel('Magnitude')
plt.plot(Tinnitus_fr,20*np.log10(Tinnitus_array_fft),'b'); plt.title(plot_title)
plt.xlabel('Frequency');plt.ylabel('Magnitude')
plt.grid()
plt.show()
