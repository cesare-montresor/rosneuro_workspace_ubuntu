#ifndef PROC_ENTROPY_CPP
#define PROC_ENTROPY_CPP

#include "Entropy.hpp"

using namespace std;

namespace wtk {
	namespace proc {

Entropy::Entropy(void) {
  this->isset_ = false;
}

Entropy::~Entropy(void) {}

bool Entropy::Setup(unsigned int num_bins) {
  try{
    this->num_bins_ = num_bins;
    this->isset_ = true;
  } catch (wtk::core::Exception& e) {
      printf("%s\n", e.Info().c_str());
  }

  return this->IsSet();
}

int Entropy::Apply(const Eigen::Ref<const Eigen::MatrixXd>& in) {
  try {
    this->IsSet();

    unsigned int num_channels = in.cols();
    this->entropy_ = Eigen::VectorXd(num_channels);
    this->distribution_binned_ = Eigen::MatrixXd(this->num_bins_, num_channels);
    this->centers_distribution_ = Eigen::MatrixXd(this->num_bins_, num_channels);

    for (unsigned int i = 0; i <num_channels; i++) {
      this->Compute(in.col(i), this->entropy_(i),
              this->distribution_binned_.col(i), this->centers_distribution_.col(i));
    }

    this->isapplied_ = true;
  } catch (wtk::core::Exception& e) {
    throw std::runtime_error("Error getting entropy values");
  }

  return 0;
}

bool Entropy::IsSet(void) {
  if(this->isset_ == false)
    throw wtk::core::Exception("The entropy method is not setup");

  return this->isset_;
}

bool Entropy::IsApplied(void) {
  if(this->isapplied_ == false)
    throw wtk::core::Exception("The entropy method is not applied");

  return this->isapplied_;
}

void Entropy::Get(Eigen::Ref<Eigen::VectorXd> out) {

  try {
    this->IsApplied();
    out = this->entropy_;
  } catch (wtk::core::Exception& e) {
    throw std::runtime_error("Error getting entropy values");
  }
}

void Entropy::Dump(void) {
    printf("[entropy] - Entropy configuration:\n");
    printf("        | - Number of bins: 	%i\n", this->num_bins_);
}


void Entropy::Get(Eigen::Ref<Eigen::VectorXd> out, Eigen::Ref<Eigen::MatrixXd> distribution_binned) {

  try {
    this->IsApplied();

    out = Eigen::VectorXd(this->entropy_);

    distribution_binned = Eigen::MatrixXd(this->distribution_binned_);
  } catch (wtk::core::Exception& e) {
    throw std::runtime_error("Error getting entropy values");
  }
}

void Entropy::Get(Eigen::Ref<Eigen::VectorXd> out, Eigen::Ref<Eigen::MatrixXd> distribution_binned,
         Eigen::Ref<Eigen::MatrixXd> centers_distribution) {
  try {
    this->IsApplied();

    out = Eigen::VectorXd(this->entropy_);

    distribution_binned = Eigen::MatrixXd(this->distribution_binned_);

    centers_distribution = Eigen::MatrixXd(this->centers_distribution_);
  } catch (wtk::core::Exception& e) {
    throw std::runtime_error("Error getting entropy values");
  }
}

void Entropy::Compute(const Eigen::Ref<const Eigen::VectorXd>& in, double& entropy,
                      Eigen::Ref<Eigen::VectorXd> distribution_binned,
                      Eigen::Ref<Eigen::VectorXd> centers_distribution) {
  try {
    std::vector<double> data_in(in.data(), in.data() + in.size());

    double in_max =  *std::max_element(data_in.begin(), data_in.end());
    double in_min =  *std::min_element(data_in.begin(), data_in.end());

    double spacing = (in_max - in_min)/this->num_bins_;
    double upperlim(in_min);
    std::vector<double> upperlim_centroids;

    for (auto it = 0; it != (int)this->num_bins_; it ++) {
      upperlim += spacing;
      upperlim_centroids.push_back(upperlim);
    }

    std::vector<int> centroids_counter(this->num_bins_);
    std::sort(data_in.begin(), data_in.end());
    int counter = 1;
    for (auto it = data_in.begin(); it != data_in.end(); it++) {
      if(( (it + 1) == data_in.end() ) | ( *it != *(it + 1) ) ){
        auto itt = upperlim_centroids.begin();
        while( ( *it > *itt ) & ( itt < upperlim_centroids.end()-1 ) ) {
          itt++;
        }
        int bin_id = std::distance(upperlim_centroids.begin(), itt);
        centroids_counter.at(bin_id) += counter;
        counter = 1;
      } else {
        counter++;
      }
    }

    distribution_binned = Eigen::VectorXi::Map(centroids_counter.data(),
                                                centroids_counter.size()).cast <double> ()
                                                / data_in.size();
    centers_distribution = Eigen::VectorXd::Map(upperlim_centroids.data(),
                                                upperlim_centroids.size()).array() - (spacing/2);

    entropy = 0;
    for (int it= 0; it != distribution_binned.size(); it++) {
      if (distribution_binned(it) != 0){
        entropy -= (distribution_binned(it) * std::log2(distribution_binned(it)));
      }
    }
  } catch (wtk::core::Exception& e) {
    throw std::runtime_error("Error getting entropy values");
  }
}

	}
}

#endif
