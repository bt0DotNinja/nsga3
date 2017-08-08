#include <iostream>
#include <cstdio>
#include <fstream>
#include <limits>
#include <iomanip>
#include <sstream>
#include <string>
#include <functional>
#include <chrono>
#include <vector>
#include <algorithm>
#include <iterator>
#include <random>
#include "pfront.h"
#include "metrics.h"
#include "benchmarks.h"
#include "nsga2.h"

int main(int argc,char **argv){
	std::vector<std::vector<long double>> pop,pfit,parent, children,front;
	std::vector<std::vector<std::vector<long double>>> NDS;
	std::random_device rdev{};
	std::mt19937 e{rdev()};
	std::vector<long double> ref={11.0,11.0};
	std::vector<long double> onezero={1.0,0};
	std::vector<long double> zeroone={0.0,1};
	long double hyper;
	double tiempo;
	int r1int,r2int,cmp,k=0,sdebug=0;

	parent.resize(2);

	if(argc < 9){
		std::cout << "Error, se requieren argumentos" << std::endl;
		std::cout << argv[0] <<" popSize mutRatio CrossRatio generaciones funcion control semilla archivoSalida " << std::endl;
		std::cout << " 1 ZDT2" << std::endl;
		std::cout << " 2 ZDT3" << std::endl;
		std::cout << " 3 ZDT6" << std::endl;
		std::cout << " 4 DTLZ2" << std::endl;
		std::cout << " Otro ZDT2" << std::endl;
		return -1;
	}
	double tasaMut=std::atof(argv[2])/100.0;
	double tasaCruza=std::atof(argv[3])/100.0;
	int gen= std::atoi(argv[4]);
	int popLen =std::atoi(argv[1]);
	int funObj= std::atoi(argv[5]);
	static std::uniform_int_distribution<int> uid(0,popLen-1);
	int control=std::atoi(argv[6]);
	int semilla=std::atoi(argv[7]);
	std::ofstream dst(argv[8]);
	
	if(!!control)
		e.seed(semilla);
	
	std::function<std::vector<long double>(std::vector<long double> &)> ff=BENCHMARKS::ZDT2;
	switch(funObj){
		case 2:
			ff=BENCHMARKS::ZDT3;
			break;
		case 3:
			ff=BENCHMARKS::ZDT6;
			break;
		case 4:
			ff=BENCHMARKS::DTLZ2;
			break;
		default:
			break;
	}
	
	pop=BENCHMARKS::genPop(popLen,2,e);
	pfit=BENCHMARKS::rank(pop,ff);

	for(int i=0;i<(popLen/2);i++){
		for(int j=0;j<2;j++){
			r1int=uid(e);
			r2int=uid(e);
			while(r1int==r2int)
				r2int=uid(e);
			cmp=PFRONT::bentley(pfit[r1int],pfit[r2int]);
			if(cmp <= 0)
				parent[j]=pop[r1int];
			else
				parent[j]=pop[r2int];
		}
		
		children=NSGA2::sbx(parent[0],parent[1],e);
		for(int j=0;j<2;j++){
			children[j]=NSGA2::rmut(children[j],tasaMut,e);
			pop.push_back(children[j]);
			}
		
	}
	pfit=BENCHMARKS::rank(pop,ff);
	/******************************************************************************/
	auto startTime = std::chrono::system_clock::now();
	

	do{
	NDS=NSGA2::fnds(pfit);
	pop=NSGA2::filler(pop,NDS);
	for(int i=0;i<(popLen/2);i++){
		for(int j=0;j<2;j++){
			r1int=uid(e);
			r2int=uid(e);
			while(r1int==r2int)
				r2int=uid(e);
			cmp=PFRONT::bentley(pfit[r1int],pfit[r2int]);
			if(cmp <= 0)
				parent[j]=pop[r1int];
			else
				parent[j]=pop[r2int];

		}
		children=NSGA2::sbx(parent[0],parent[1],e);
		for(int j=0;j<2;j++){
			children[j]=NSGA2::rmut(children[j],tasaMut,e);
			pop.push_back(children[j]);
			}
		
	}	
	pfit=BENCHMARKS::rank(pop,ff);
	k++;
	}while(k<gen);

	auto endTime = std::chrono::system_clock::now();
	/******************************************************************************/
	std::chrono::duration<double> elapsed_seconds = endTime - startTime;
	tiempo=elapsed_seconds.count();

	front=PFRONT::domOnevsAll(pfit);
	std::sort(front.begin(),front.end());
	front.erase( std::unique( front.begin(), front.end() ), front.end() );
	
	hyper=METRICS::hypervol2d(front,ref);

	for(int i=0;i<front.size();i++){
               for(int j=0;j< front[i].size()-1;j++)
                        dst<< front[i][j] << ' ';
               dst << std::endl;
        }


	std::cout <<std::setprecision(std::numeric_limits<long double>::digits10 + 1);
//	std::cout << "Distancia generacional: " << distgen << std::endl;
//	std::cout <<"Distancia generacional inversa:  " << invdg << std::endl;
//	std::cout <<"Delta:  " << delta << std::endl;
	std::cout << hyper << std::endl;
//	std::cout << tiempo << std::endl;
	

//	dst<< distgen << std::endl;
//	dst<< invdg << std::endl;
//	dst<< delta << std::endl;
	dst<< hyper << " " << tiempo << "s" << std::endl;
	dst.close();

return 0;
}
