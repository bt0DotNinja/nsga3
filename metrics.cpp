#include <vector>
#include <omp.h>
#include <iostream>
#include <algorithm>
#include <cmath>
#include "metrics.h"


std::vector<long double> METRICS::und(std::vector<std::vector<long double>> &set,long double &promedio){
	std::vector<long double> distancias;
	long double sum=0.0;
	long double minimo,candidato;
	int i;
	#pragma omp parallel for private(minimo,i,candidato)
	for(i=0;i<set.size();i++){
		minimo=euclidianDist(set[i],set[0]);
		for(int j=0;j<set.size();j++){
			if(i!=j){
				candidato=euclidianDist(set[i],set[j]);
				if(candidato < minimo)
					minimo=candidato;
			}
		}
		#pragma omp critical
		distancias.push_back(minimo);
	}
	#pragma omp parallel for reduction(+:sum) 
	for(i=0;i<distancias.size();i++)
		sum+=distancias[i];

	promedio= sum/(long double) set.size();
	return distancias;
	
}
std::vector<long double> METRICS::nnps(std::vector<std::vector<long double>> &set1, std::vector<std::vector<long double>> &set2){
	std::vector<long double> distancias;
	long double minimo,candidato;
	int i;
	#pragma omp parallel for private(minimo,i,candidato)
	for(i=0;i<set1.size();i++){
		minimo=euclidianDist(set1[i],set2[0]);
		for(int j=1;j<set2.size();j++){
			candidato=euclidianDist(set1[i],set2[j]);
			if(candidato < minimo)
				minimo=candidato;
		}
		#pragma omp critical
		distancias.push_back(minimo);
	}
	return distancias;
}
long double METRICS::euclidianDist(std::vector<long double> &a, std::vector<long double> &b){
	long double sum=0.0;
	for(int i=0;i<a.size();i++)
		sum+=std::pow(a[i] - b[i],2);
	return std::sqrt(sum);
}
long double METRICS::genDist(std::vector<std::vector<long double>>&PFknow, std::vector<std::vector<long double>>&PFtrue){
	long double sum=0.0;
	int i=0;
	std::vector<long double> distancias = nnps(PFknow,PFtrue);
	#pragma omp parallel for reduction(+:sum) 
	for(i=0;i<distancias.size();i++)
		sum+=distancias[i];
	return sum/(long double)PFknow.size();
}
long double METRICS::invGenDist(std::vector<std::vector<long double>>&PFknow, std::vector<std::vector<long double>>&PFtrue){
	long double sum=0.0;
	int i=0;
	std::vector<long double> distancias = nnps(PFtrue,PFknow);
	#pragma omp parallel for reduction(+:sum) 
	for(i=0;i<distancias.size();i++)
		sum+=distancias[i];
	return sum/(long double)PFtrue.size();


}
long double METRICS::hypervol2d(std::vector<std::vector<long double>>&PFknow, std::vector<long double>& Ref){
	long double sum=0.0;
	std::vector<long double> nr=Ref;
	long double x,y;
	int i;
	for(i=0;i<PFknow.size()-1;i++){
		x=nr[0] - PFknow[i][0];
		y=nr[1] - PFknow[i][1];
		sum+=x*y;
		nr[1]=PFknow[i][1];
	}
	return sum;
}
long double METRICS::deltaDiv(std::vector<std::vector<long double>>&omega, std::vector<std::vector<long double>>&extremos){
	std::vector<long double> nn=nnps(extremos,omega);
	long double d,delta,sum=0.0,EO=0.0;
	std::vector<long double> distancias=und(omega,d);
	int i;	
	#pragma omp parallel for reduction(+:sum) 
	for(i=0;i<distancias.size();i++)
		sum+=std::abs(distancias[i] - d);
	
	#pragma omp parallel for reduction(+:EO) 
	for(i=0;i<nn.size();i++)
		EO+=nn[i];

	delta=(EO+sum)/(EO+d*(omega.size()-extremos.size()));
	return delta;
}
