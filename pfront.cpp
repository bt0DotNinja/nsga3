#include <vector>
#include <omp.h>
#include <algorithm>
#include "pfront.h"

int PFRONT::bentley(std::vector<long double>&u, std::vector<long double>&v){
	int i=0,k;
	k=u.size()-1;
	while(i < k && u[i] == v[i]) 
		i++;
	if(k <= i)
		return 0;
	if(u[i] < v[i]){
		for(i;i<k;i++)
			if(u[i] > v[i])
				return 0;
		return 1;
	}
	else{
		for(i;i<k;i++)
			if(u[i] < v[i])
				return 0;
		return -1;
	}
			
}
std::vector<std::vector<long double>> PFRONT::domAllvsAll(std::vector<std::vector<long double>> &pop){
	std::vector<std::vector<long double>> front;
	std::vector<int> index;
	bool nonDominated=true;
	int d,i,j;
	#pragma omp parallel for private(nonDominated,i,d)
	for(i=0;i< pop.size();i++){
		nonDominated=true;
		for(j=0;j < pop.size();j++){
			if(i==j)
				continue;
			d=bentley(pop[i],pop[j]);
			if(d==-1){
				nonDominated=nonDominated && false;
				break;
			}
		}
		#pragma omp critical
		if(nonDominated)
			front.push_back(pop[i]);
	}
	return front;
}
std::vector<std::vector<long double>> PFRONT::domOnevsAll(std::vector<std::vector<long double>> &pop){
	std::vector<std::vector<long double>> front;
	std::vector<int> index;
	bool nonDominated=true;
	int d;
	index.push_back(0);
	for(int k=0;k<2;k++)	
	for(int i=1;i<pop.size();i++){
		nonDominated=true;
		for(int j=0;j<index.size();j++){
			d=bentley(pop[i],pop[index[j]]);
			if(d==-1){
				nonDominated=false;
				break;
			}
			if(d==1){
				index.erase(index.begin()+j);
				if(index.size()==0)
					index.push_back(i);
			}
		}
		if(nonDominated)
			index.push_back(i);
	}
	std::sort(index.begin(),index.end());
	index.erase(std::unique(index.begin(),index.end()),index.end());
	for(int i=0;i<index.size();i++)
		front.push_back(pop[index[i]]);
	return front;
}

std::vector<std::vector<long double>> PFRONT::domBentleyBased(std::vector<std::vector<long double>> &pop){
	std::vector<std::vector<long double>> front;
	std::vector<int> index;
	bool nonDominated=true;
	int d,jj=0;
	#pragma omp parallel for 
	for(int i=0;i<pop.size();i++)
		for(int j=i+1;j<pop.size();j++){
			d=bentley(pop[i],pop[j]);
			if(d==-1){
				#pragma omp critical
				index.push_back(i);
				break;
			}
			if(d==1){
				#pragma omp critical
				index.push_back(j);
			}
		}
	std::sort(index.begin(),index.end());
	index.erase(std::unique(index.begin(),index.end()),index.end());
	for(int i=0;i < pop.size() && jj<index.size();i++){
		if(i!=index[jj])
			front.push_back(pop[i]);
		else
			jj++;
	}
	return front;
}
