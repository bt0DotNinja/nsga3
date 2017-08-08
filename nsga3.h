#include<vector>
#include<random>

#ifndef NSGA2_H
#define NSGA2_H


namespace NSGA2{
	long double repara(long double, long double, long double);
	std::vector<std::vector<std::vector<long double>>> fnds(std::vector<std::vector<long double>> &);
	std::vector<std::vector<long double>> cda(std::vector<std::vector<long double>> );
	std::vector<std::vector<long double>> sbx(std::vector<long double> &, std::vector<long double> &, std::mt19937 &);
	std::vector<long double> rmut(std::vector<long double> &, long double, std::mt19937 &);
	std::vector<std::vector<long double>> filler(std::vector<std::vector<long double>> &,std::vector<std::vector<std::vector<long double>>>&);
}
#endif
