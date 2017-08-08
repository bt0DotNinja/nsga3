#include<vector>

#ifndef METRICS_H
#define METRICS_H


namespace METRICS{
	std::vector<long double> nnps(std::vector<std::vector<long double>> &, std::vector<std::vector<long double>> &);
	std::vector<long double> und(std::vector<std::vector<long double>> &,long double &);
	long double euclidianDist(std::vector<long double>&, std::vector<long double>&);
	long double genDist(std::vector<std::vector<long double>>&, std::vector<std::vector<long double>>&);
	long double invGenDist(std::vector<std::vector<long double>>&, std::vector<std::vector<long double>>&);
	long double hypervol2d(std::vector<std::vector<long double>>&, std::vector<long double>&);
	long double deltaDiv(std::vector<std::vector<long double>>&, std::vector<std::vector<long double>>&);
}
#endif
