#!/bin/env python2
# Alberto Rodriguez Sanchez 2016
import pylab
import numpy
import sys
#import tabulate as tb

def meanStdDev(dataset):
    '''
        Entrada: dataset es una lista 
        Salida:  una tupla formada por mean (media) 
                y stdDev desviacion estandar
    '''
    mean=sum(dataset)/float(len(dataset))
    stdDev=0
    for data in dataset:
        stdDev+=(data - mean)**2
    return (mean,(stdDev/len(dataset))**0.5)

def oneTwoThreeQuartiles(dataset):
    '''
        metodo Tukey's hinges
    '''
    tmp=numpy.array(dataset)
    return numpy.percentile(tmp,numpy.arange(25,100,25))

def graficaCaja(datasetList,low,hight,steps):
    '''
    genera una grafica de caja y bigote con los set de datos
    incluidos en datasetList
    '''
    pylab.Figure()
    pylab.title("Hipervolumen")
    pylab.ylabel("Hipervolumen")
    pylab.xlabel("Funciones")
    #pylab.yticks(range(low,hight,steps))
    pylab.boxplot(datasetList)
    pylab.xticks([1,2,3,4],['ZDT2','ZDT3','ZDT6','DTLZ2'])
    pylab.show()

if __name__ == '__main__':
    assert len(sys.argv) > 1 , "Argumentos insuficientes"
    dataSets=[]
    try:
        for i in range(1,len(sys.argv)):
            fdata=open(sys.argv[i],'r')
            tmp=map(float,fdata)
            dataSets.append(tmp)
            fdata.close()
    except IOError as e:
        print "I/O error({0}): {1}".format(e.errno, e.strerror)
        exit()
    
    results=[]
    low=None
    hight=None
    for i in range(len(dataSets)):
        tmp=[]
        tmp.append("muestra"+str(i+1))
        mN=min(dataSets[i])
        if mN < low or low==None:
            low=mN
        mX=max(dataSets[i])
        if mX > hight or hight==None:
            hight=mX
        tmp.extend([mN,mX])
        media, stdDev = meanStdDev(dataSets[i])
        tmp.extend([media,stdDev**2,stdDev])
        q1,q2,q3=oneTwoThreeQuartiles(dataSets[i])
        tmp.extend([q1,q2,q3])
        results.append(tmp)        

    print "Muestra\tMinimo\tMaximo\tMedia\tVarianza\tstdDev\tQ1\tQ2\tQ3"
    for muestra in results:
        for e in muestra:
            print str(e) + "\t" ,
        print 
    graficaCaja(dataSets, int(numpy.floor(low)-2),int(numpy.ceil(hight)+2),0.01)
