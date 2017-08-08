#include<vector>
#include<functional>
#include<random>
#define PI 3.1415926535897932384626433832795029

#ifndef BENCHMARKS_H
#define BENCHMARKS_H

namespace BENCHMARKS{
std::vector<std::vector<long double>> rank(std::vector<std::vector<long double>> &, std::function<std::vector<long double>(std::vector<long double> &)>);
	std::vector<std::vector<long double>> genPop(int,int,std::mt19937 &);
	std::vector<long double> ZDT2(std::vector<long double> &);
	std::vector<long double> ZDT3(std::vector<long double> &);
	std::vector<long double> ZDT6(std::vector<long double> &);
	std::vector<long double> DTLZ2(std::vector<long double> &);
}
#endif
