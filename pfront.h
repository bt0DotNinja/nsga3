#include<vector>

#ifndef PFRONT_H
#define PFRONT_H


namespace PFRONT{
	int bentley(std::vector<long double>&, std::vector<long double>&);
	std::vector<std::vector<long double>> domAllvsAll(std::vector<std::vector<long double>> &);
	std::vector<std::vector<long double>> domOnevsAll(std::vector<std::vector<long double>> &);
	std::vector<std::vector<long double>> domBentleyBased(std::vector<std::vector<long double>> &);
}
#endif
