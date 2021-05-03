#ifndef PROC_DC_CPP
#define PROC_DC_CPP

#include "Dc.hpp"

namespace wtk {
	namespace proc {

Dc::Dc(void) : Filter(Filter::inDomainTime) {}

Dc::~Dc(void) {}

void Dc::Apply(const Eigen::Ref<const Eigen::MatrixXd>& in, Eigen::Ref<Eigen::MatrixXd> out) {
	out = in - (in.colwise().mean()).replicate(in.rows(), 1);
}

	}
}


#endif
