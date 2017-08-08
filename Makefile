all: test

test: main.o nsga2.o pfront.o metrics.o benchmarks.o 
	g++ -g main.o pfront.o metrics.o benchmarks.o nsga2.o -std=c++11 -fopenmp -O3 -lm -o nsga2
nsga2.o: nsga2.cpp
	g++ -g -O3 -std=c++11 -c -o nsga2.o nsga2.cpp -fopenmp 
main.o: main.cpp
	g++ -g -O3 -std=c++11 -c -o main.o main.cpp
pfront.o: pfront.cpp
	g++ -g -O3 -std=c++11 -c -o pfront.o pfront.cpp -fopenmp 
metrics.o: metrics.cpp
	g++ -g -O3 -std=c++11 -c -o metrics.o metrics.cpp -fopenmp 
benchmarks.o: benchmarks.cpp
	g++ -g -O3 -std=c++11 -c -o benchmarks.o benchmarks.cpp -fopenmp 
clean:
	rm *.o nsga2

