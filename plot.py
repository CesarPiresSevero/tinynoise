# Imports
import matplotlib.pyplot as plt
import numpy as np
import scipy
from pyfi import fi

plot_title = "Tiny Noise Color Comparison"

# Helper Funcs
def get_fft(array,fs):
    ts=1/(int(fs))
    t=np.arange(0,(len(array)*ts),ts)
    n=np.size(t)
    fr=(int(fs)/2)*np.linspace(0,1,int(n/2))
    resp=np.fft.fft(array)
    freq=(2/n)*abs(resp[0:np.size(fr)]) 
    return freq,fr,t 

# Reading log file from C code
f = open("white.txt", "r")
lines = f.readlines()
data =[]
fi_obj = fi(word_len=16,frac_len=15,fixed=False,return_val=True)
for line in lines:
    line = line.replace("\n", "")
    line=int(line,16)
    data.append(fi_obj(line))
white=np.asarray(data, dtype=np.float32)

f = open("pink.txt", "r")
lines = f.readlines()
data =[]
fi_obj = fi(word_len=16,frac_len=15,fixed=False,return_val=True)
for line in lines:
    line = line.replace("\n", "")
    line=int(line,16)
    data.append(fi_obj(line))
pink=np.asarray(data, dtype=np.float32)

f = open("brown.txt", "r")
lines = f.readlines()
data =[]
fi_obj = fi(word_len=16,frac_len=15,fixed=False,return_val=True)
for line in lines:
    line = line.replace("\n", "")
    line=int(line,16)
    data.append(fi_obj(line))
brown=np.asarray(data, dtype=np.float32)

# Plotting data
white_fft,white_fr,white_t=get_fft(white,1)
brown_fft,brown_fr,brown_t=get_fft(brown,1)
pink_fft,pink_fr,pink_t=get_fft(pink,1)




fig1, (ax1_1, ax2_1, ax3_1) = plt.subplots(1, 3)
fig1.suptitle(plot_title)
ax1_1.plot(white_fr,20*np.log10(white_fft),'gray')
ax1_1.set(xlabel='Frequency',ylabel='Magnitude')
ax2_1.plot(brown_fr,20*np.log10(brown_fft),'saddlebrown')
ax2_1.set(xlabel='Frequency',ylabel='Magnitude')
ax3_1.plot(pink_fr,20*np.log10(pink_fft),'deeppink')
ax3_1.set(xlabel='Frequency',ylabel='Magnitude')
plt.show()




