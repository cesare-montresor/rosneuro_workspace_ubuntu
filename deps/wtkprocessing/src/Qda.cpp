#ifndef PROC_QDA_CPP
#define PROC_QDA_CPP

#include "Qda.hpp"


namespace wtk {
	namespace proc {

Qda::Qda(unsigned int nclasses, unsigned int nfeatures) : Classifier(Classifier::AsQDA) {}

Qda::~Qda(void) {}

void Qda::Load(std::string filename) {}

void Qda::Run(const Ref<const VectorXd>& features, Ref<Vector2d> pp) {}
	}
}

#endif
