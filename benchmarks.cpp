#include<vector>
#include<iostream>
#include<omp.h>
#include"benchmarks.h"


std::vector<std::vector<long double>> BENCHMARKS::rank(std::vector<std::vector<long double>> &pop, std::function<std::vector<long double>(std::vector<long double> &)> ff){
	int i;
	std::vector<std::vector<long double>> res;
	res.resize(pop.size());
	#pragma omp parallel for private(i)
	for(i=0;i<pop.size();i++){
		res[i]=ff(pop[i]);
		res[i].push_back(i);
	}
	return res;
}

std::vector<long double> BENCHMARKS::ZDT2(std::vector<long double> &ind){
	std::vector<long double> res;
	long double g=0.0;
	int n=ind.size();
	res.resize(2);
	
	res[0]=ind[0];
	for(int i=1;i<n;i++){
		g+=ind[i];
	}
	g*=(9.0/(n-1));
	g+=1;
	res[1]=g*(1-std::pow(ind[0]/g,2));	
	return res;
}
std::vector<long double> BENCHMARKS::ZDT3(std::vector<long double> &ind){
	std::vector<long double> res;
	long double g=0.0,second,one;
	int n=ind.size();
	res.resize(2);
	
	res[0]=ind[0];
	for(int i=1;i<n;i++){
		g+=ind[i];
	}
	g*=(9.0/(n-1));
	g+=1;
	one=std::sqrt(ind[0]/g);
	second=ind[0]/(g*std::sin(PI*10*ind[0]));

	res[1]=g*(1-one-second);	
	return res;
}
std::vector<long double> BENCHMARKS::ZDT6(std::vector<long double> &ind){
	std::vector<long double> res(2,0);
	long double g=0.0,second,one;
	int n=ind.size();
	for(int i=1;i<n;i++){
		g+=ind[i];
	}
	g/=(n-1);
	g= 1+9*std::pow(g,0.25);

	one=1-std::exp(-4*ind[0])*std::pow(std::sin(6*PI*ind[0]),6);
	second=1-std::pow(one/g,2);
	res[0]=one;
	res[1]=second;
	return res;
}
std::vector<long double> BENCHMARKS::DTLZ2(std::vector<long double> &ind){
	std::vector<long double> res(2,0);
	long double g=0.0,second,one;
	int n=ind.size();
	for(int i=0;i<n;i++){
		g+=std::pow(ind[i]-0.5,2);
	}
	one=(1+g)*std::cos((PI*ind[0])/2.0);
	second=(1+g)*std::sin((PI*ind[0])/2.0);
	res[0]=one;
	res[1]=second;
	return res;
}
std::vector<std::vector<long double>> BENCHMARKS::genPop(int popsize,int n,std::mt19937 &e){
	static std::uniform_real_distribution<double> d(0.0,1.0);
	std::vector<std::vector<long double>> pop(popsize,std::vector<long double>(n,0));
	
	for(int i=0;i<popsize;i++)
		for(int j=0;j<n;j++)
			pop[i][j]=d(e);

	return pop;
}
