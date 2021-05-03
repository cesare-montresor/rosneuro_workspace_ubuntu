#ifndef PROC_WINDOW_CPP
#define PROC_WINDOW_CPP

#include "Window.hpp"

namespace wtk {
	namespace proc {

Window::Window(int wtype) : Filter(Filter::inDomainTime) {
	this->_wtype = wtype;
}

Window::~Window(void) {
}

int Window::GetWindowType(void) {
	return this->_wtype;
}

std::string Window::GetWindowName(void) {
	return this->_wname;
}

void Window::GetWindow(Eigen::Ref<Eigen::VectorXd> window) {
	window = this->_window;
}

double Window::GetWindowNorm(void) {
	return this->_windownorm;
}

double Window::ComputeNorm (void) {
	return (this->_window.array().pow(2)).sum() / this->_window.size();
}

void Window::Apply(const Eigen::Ref<const Eigen::MatrixXd>& in, Eigen::Ref<Eigen::MatrixXd> out) {
	out = in.array() * this->_window.replicate(1, in.cols()).array();
}
	}
}

#endif
