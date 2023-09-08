import matplotlib
from matplotlib.collections import PatchCollection
import matplotlib.patches as mpatches
from matplotlib.path import Path
import matplotlib.patches as patches
import numpy as np
from matplotlib import cm
from matplotlib import pyplot as plt
from copy import deepcopy
matplotlib.use('Tkagg')

event,t1_arr,t2_arr,t3_arr,t4_arr = np.genfromtxt('charges.txt',delimiter=' ',dtype=str,unpack=True)

event = list(map(int, event))
event = np.array(event)

t1_arr = np.array(t1_arr)
t2_arr = np.array(t2_arr)
t3_arr = np.array(t3_arr)
t4_arr = np.array(t4_arr)

tel_arr = np.array([t1_arr, t2_arr, t3_arr, t4_arr]).T

for e in range(event.size):
                
    fig, axs = plt.subplots(2, 2,figsize=(13,14))
    pixels = np.arange(0,499)
    patches =[]

    pixelnum,x,y = np.genfromtxt("coords.txt",usecols=(0,1,2),unpack=True)

    for i in range(pixelnum.size):
        x[i] = x[i]/4
        y[i] = y[i]/4
        hexagon = mpatches.RegularPolygon((x[i],y[i]), 6, radius=0.021)
        patches.append(hexagon)
        
    p = PatchCollection(patches,cmap=plt.cm.hot,alpha=0.8,edgecolor='k',clim=(400,1500))
    p_array = np.array([deepcopy(p), deepcopy(p), deepcopy(p), deepcopy(p)])

    for tel in range(1,5):
        
        if (tel == 1):
            axis = axs[0,0]
        if (tel == 2):
            axis = axs[0,1]
        if (tel == 3):
            axis = axs[1,0]
        if (tel == 4):
            axis = axs[1,1]
                        
        pixel_charge = tel_arr[e][tel-1]
        pixel_charge = pixel_charge.split(',')
        pixel_charge = np.array(pixel_charge)
        pixel_charge = pixel_charge[:pixel_charge.size-2]
        pixel_charge = pixel_charge[0:pixel_charge.size-1].astype(int)
                                
        collection = p_array[tel-1]
        axis.add_collection(collection)
        
        collection.set_array(pixel_charge)
        
        for i in range(pixelnum.size):
            axis.annotate('{}'.format(i),(x[i],y[i]),fontsize=5, ha='center', va='center')
        
        colorbar = fig.colorbar(collection, ax=axis)
        colorbar.set_label('Charge [d.c.]')
        axis.set_title(f'Event {event[e]}, T{tel}')
        axis.set_xlim(-0.5,0.5)
        axis.set_ylim(-0.5,0.5)
plt.show()
