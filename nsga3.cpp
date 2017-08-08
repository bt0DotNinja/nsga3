#include <vector>
#include <cmath>
#include <iostream>
#include <limits>
#include <random>
#include <functional>
#include <omp.h>
#include <algorithm>
#include "nsga2.h" 
#include "pfront.h"

long double NSGA2::repara(long double val, long double min, long double max){
	long double X=val;
	while(!(X >= min && X <= max)){
		if(X > max)
			X = 0.5; 
		if(val < min)
			X = 0.5;
	}
	return X;
	
}

std::vector<std::vector<std::vector<long double>>> NSGA2::fnds(std::vector<std::vector<long double>> &pop){
	std::vector<std::vector<std::vector<long double>>> S;
	std::vector<std::vector<std::vector<long double>>> F;
	std::vector<std::vector<long double>> Q;
	std::vector<int> np(pop.size(),0);
	int tmp,p,q;
	S.resize(pop.size());
	F.resize(1);
	for(int i=0;i<pop.size();i++){
		for(int j=0;j<pop.size();j++){
			tmp=PFRONT::bentley(pop[i],pop[j]);
			if(tmp ==  1){
				S[i].push_back(pop[j]);
			}
			else if(tmp == -1 )
				np[i]++;
		}
		if(np[i] == 0){
			F[0].push_back(pop[i]);
		}
	}
	int k=0;
	while(!F[k].empty()){
		Q.clear();
		for(int i = 0;i < F[k].size();i++){
			p= find(pop.begin(), pop.end(), F[k][i]) - pop.begin();
			for(int j=0;j < S[p].size();j++){
				q= find(pop.begin(), pop.end(), S[p][j]) - pop.begin();
				np[q]--;
				if(np[q] == 0)
					Q.push_back(S[p][j]);
			}
		}
		F.push_back(Q);
		k++;
	}
	F.resize(k);
	return F;
}
std::vector<std::vector<long double>> NSGA2::cda(std::vector<std::vector<long double>> I){
	long double fmin,fmax;
	int l=I.size();
	int m=I[0].size()-1;
	for(int i=0;i < l;i++){
		I[i].push_back(0);
		}
	for(int i = 0; i< m;i++){
		std::sort(I.begin(),I.end());
		I[0][m+1-i]=100000000;//Revisar
		I[l-1][m+1-i]=100000000;
		fmin=I[0][0];
		fmin=I[l-1][0];
		for(int j=1;j<l-2;j++){
			I[j][m+1-i]+=(I[j+1][0] - I[j-1][0])/(fmax-fmin);
		}
		for(int k=0;k<l;k++)
			I[k].erase(I[k].begin());
	}
	std::sort(I.begin(), I.end(), [](std::vector<long double> a, std::vector<long double> b) {
			        return b[1] < a[1];   
				    });
	return I;
}
std::vector<std::vector<long double>> NSGA2::sbx(std::vector<long double> &P1, std::vector<long double> &P2, std::mt19937 &e){
	static std::uniform_real_distribution<long double> d(0.0,1.0);
	std::vector<std::vector<long double>> res;
	std::vector<long double> X,middle;
	long double B,u=d(e),x,y;
	
	if(u <= 0.5)
		B=std::cbrt(2*u);
	else
		B=std::cbrt(1/(2*(1-u)));
	
	res.resize(2);

	for(int i;i<P1.size();i++){
		x=0.5*((1+B)*P1[i] + (1-B)*P2[i]);
		if(x>1.0 || x<0.0)
			x=d(e);
		y=0.5*((1-B)*P1[i] + (1+B)*P2[i]);
		if(y>1.0 || y<0.0)
			y=d(e);	

		res[0].push_back(x);
		res[1].push_back(y);
	}
	return res;
}
std::vector<long double> NSGA2::rmut(std::vector<long double> &son, long double mutf, std::mt19937 &e){
	std::vector<long double> res;
	static std::uniform_real_distribution<long double> d(0.0,1.0);
	long double u,v,s;
	u=d(e);
	if(u <= 0.5){
		s=std::pow(2*u,1.0/21.0)-1;
		for(int i=0;i<son.size();i++){
			if(d(e) < mutf){
				v=son[i]+s*(son[i]);
				if(v>1 || v<0)
					v=d(e);
				res.push_back(v);
			}
			else{
				res.push_back(son[i]);
			}
		}
	}
	else{
		s=1-std::pow(2*(1-u),1.0/21.0);
		for(int i=0;i<son.size();i++){
			if(d(e) < mutf){
				v=son[i]+s*(1-son[i]);
				if(v>1 || v<0)
					v=d(e);
				res.push_back(v);
			}
			else{
				res.push_back(son[i]);
			}
		}
	}
	return res;
}
std::vector<std::vector<long double>> NSGA2::filler(std::vector<std::vector<long double>> &pop, std::vector<std::vector<std::vector<long double>>> &nds){
	std::vector<std::vector<long double>> res,tmp,tmp2;
	int popLen=pop.size()/2;
	int k=0, flag=1, i=0;
	
	tmp=nds[k];
	while(tmp.size() <= (popLen - i)){
		for(int j=0;j<tmp.size();j++){
			res.push_back(pop[(int) tmp[j][tmp[j].size()-1]]);
			i++;
			}
		k++;
		tmp=nds[k];
	}
	if(res.size()<popLen){
		tmp2=cda(tmp);
		for(int j=0;j<tmp2.size();j++){
			res.push_back(pop[(int)tmp2[j][0]]);
			if(res.size()==popLen)
				break;
		}
	}
	return res;
}
