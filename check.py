# Imports
import matplotlib.pyplot as plt
import numpy as np
import scipy

plot_title = "Tiny Noise Uniform High Pass"

# Helper Funcs
def get_fft(array,fs):
    ts=1/(int(fs))
    t=np.arange(0,(len(array)*ts),ts)
    n=np.size(t)
    fr=(int(fs)/2)*np.linspace(0,1,int(n/2))
    resp=np.fft.fft(array)
    freq=(2/n)*abs(resp[0:np.size(fr)]) 
    return freq,fr,t 

def lp_filter(indata):
    data = [0]
    for i,val in enumerate(indata):
        data.append((val+data[-1])/2)
    return np.asarray(data)


def hp_filter(indata):
    data = [0]
    for i,val in enumerate(indata):
        data.append(val-(val+data[-1])/2)
    return np.asarray(data)


# Reading log file from C code
f = open("log.txt", "r")
lines = f.readlines()
data =[]
for line in lines:
    line = line.replace("\n", "")
    line=int(line,16)
    line=(line/(2**15-1))-1
    data.append(line)
output=np.asarray(data, dtype=np.float32)

# Numpy random generators
# output=np.random.normal(scale=0.25,size=10**5)
# output=np.random.uniform(low=-1.0,high=1.0,size=10**5)

# Filtering data
# output = lp_filter(output)
# output = lp_filter(lp_filter(output))
# output = hp_filter(output)
output = hp_filter(hp_filter(output))

# Plotting data
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




