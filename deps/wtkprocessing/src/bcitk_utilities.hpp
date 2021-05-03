#ifndef BCITK_UTILITIES_HPP
#define BCITK_UTILITIES_HPP

#include <iostream>
#include <iomanip> 
#include <fstream>
#include <math.h>
#include <vector>
#include <Eigen/Dense>
#include <stdint.h>
#include "Device.hpp"

using namespace Eigen;

static inline void bcitk_progressbar(unsigned int x, unsigned int n, unsigned int w = 50)
{
    if ( (x != n) && (x % (n/100+1) != 0) ) return;
 
    float ratio  =  x/(float)n;
    int   c      =  ratio * w;
 
    std::cout << setw(3) << (int)(ratio*100 + 1) << "% [";
    for (int x=0; x<c; x++) std::cout << "=";
    for (int x=c; x<(int)w; x++) std::cout << " ";
    std::cout << "]\r" << std::flush;
}


template <typename Derived>
int bcitk_gettrigger(const MatrixBase<Derived>& in, std::vector<int>& pos, int value = 1)
{
	typedef typename Derived::Scalar Scalar;
	
	unsigned int i;
	int nre = 0;

	const Scalar nsamples = static_cast<Scalar>(in.rows());
	int cvalue;
	int pvalue;

	for (i = 1; i < nsamples; i++) {
		cvalue = static_cast<Scalar>(in(i));
		pvalue = static_cast<Scalar>(in(i-1));
		if(((cvalue - pvalue) > 0) & (cvalue == value)) { 	// raising edge and value
			pos.push_back(i);	
			nre++;
		}
	}

	return nre;
}


#endif
