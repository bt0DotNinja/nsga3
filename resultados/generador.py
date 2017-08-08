#/usr/bin/env python

import sys
import numpy as np

if __name__ == '__main__':
    assert len(sys.argv) > 2, "Argumentos insuficientes"
    try:
        val=float(sys.argv[1])
        
	datos=np.loadtxt(sys.argv[2])
        datos= val - datos
        np.savetxt(sys.argv[3],datos)
        
        
    except IOError as e:
        print "I/O error({0}):{1}".format(e.errno,e.strerror)



