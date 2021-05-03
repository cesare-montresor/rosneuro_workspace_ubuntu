#ifndef PROC_BANDPASSFILTER_HPP
#define PROC_BANDPASSFILTER_HPP

#include "BandPassFilter.hpp"

namespace wtk {
  namespace proc {


  BandPassFilter::BandPassFilter(void) : BandPassFilter() {
    this->_name = "BandPassFilter";
    this->lower_cut_off =
    this->upper_cut_off =
  }
  BandPassFilter::~BandPassFilter(void) {}


}

  }
}
