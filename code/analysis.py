#!/usr/bin/env python
import matplotlib.pyplot as plt
import numpy as np
import math 

#usefull data
N_DATA = 61
N_EXPERIMENTS = 50

def readData(f,d):
    # function that read data and calculate the mean value at same time
    for data in range(N_DATA):
        lineData = [ float(_) for _ in f.readline().split() ]
        d['avg_time'][data] = ((d['avg_time'][data]*d['counter'])+lineData[0]/1000) / (d['counter']+1)
        d['avg_voltages'][data] = ((d['avg_voltages'][data]*d['counter'])+lineData[1]) / (d['counter']+1)
    d['counter']+=1        

def readFile(filename,cd,dd):
    with open(filename,'r') as file:
        for experiment in range(N_EXPERIMENTS):
            file.readline() # read "Experiment n.#"
            readData(file, cd) # read charging data
            file.readline() # read "discharging..."
            readData(file, dd) # read discharging data

def ddp(t):
    #mathematical function 
    fem = 5
    C = 1e-6
    R = 1e6
    return fem*(1-pow(math.e,-t/(C*R)))

def plot(data):
    fig = plt.figure()
    t = np.linspace(0.,6.,61)
    plt.plot(t,ddp(t), label="Expected result", color="orange")
    plt.ylabel('D.D.P [V]')
    plt.xlabel('Time [s]')
    fig.suptitle('D.D.P. condensatore su tempo')
    plt.scatter(data['avg_time'], data['avg_voltages'], label='Dati raccolti', marker = '.')
    plt.legend(loc = 'upper left')
    plt.show()


def main():
    #definition of data structure
    chargingData = {'avg_voltages': [0]*N_DATA, 'avg_time': [0]*N_DATA, 'counter': 0 }
    dischargingData = {'avg_voltages': [0]*N_DATA, 'avg_time': [0]*N_DATA, 'counter': 0 }
    readFile("capacitor_data.txt",chargingData, dischargingData) #read data
    plot(chargingData) #plot things
    

# main function implementation 
if __name__ == '__main__':
    main()