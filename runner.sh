#!/bin/bash
for seed in {111..131}
do
	./nsga2 100 5 50 100 1 1 $seed salidasZDT2.txt >> resultados_ZDT2.dat
	./nsga2 100 5 50 100 2 1 $seed salidasZDT3.txt >> resultados_ZDT3.dat
	./nsga2 100 5 50 100 3 1 $seed salidasZDT6.txt >> resultados_ZDT6.dat
	./nsga2 100 5 50 100 4 1 $seed salidasDTLZ2.txt >> resultados_DTLZ2.dat
done
