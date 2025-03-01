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
# output=np.asarray(data, dtype=np.float32)

f = open("log.txt", "r")
lines = f.readlines()
data =[]
for line in lines:
    line = line.replace("\n", "")
    line=int(line,16)
    line=(line/(2**15-1))-1
    data.append(line)
output=np.asarray(data, dtype=np.float32)

output=np.random.normal(scale=0.25,size=10**5)
output=np.random.uniform(low=-1.0,high=1.0,size=10**5)

output_fft,output_fr,output_t=get_fft(output,1)

data=np.asarray(output, dtype=np.float32)
fig1, (ax1_1, ax2_1, ax3_1) = plt.subplots(1, 3)
fig1.suptitle(plot_title)
count, bins, ignored = ax1_1.hist(data, 30, density=True)
ax1_1.plot(bins, 1/(np.std(data) * np.sqrt(2 * np.pi)) *np.exp( - (bins - data.mean())**2 / (2 * np.std(data)**2) ),linewidth=2, color='r')
ax1_1.set(xlabel='Amplitude',ylabel='Probability Density')
ax2_1.specgram(data, Fs= 1, NFFT= 128, noverlap=64)
ax2_1.set(xlabel='Samples',ylabel='Frequency')
ax3_1.plot(output_fr,20*np.log10(output_fft),'b');
ax3_1.set(xlabel='Frequency',ylabel='Magnitude')
plt.show()




