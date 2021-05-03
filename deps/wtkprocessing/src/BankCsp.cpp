#ifndef PROC_BANKCSP_CPP
#define PROC_BANKCSP_CPP

#include "BankCsp.hpp"

namespace wtk {
	namespace proc {

BankCsp::BankCsp(void) : Filter(Filter::inDomainSpatial) {

    this->_stype 	= "filter";
    this->_name 	= "cnbi-bankcsp";

    this->config_.filename = "";
    this->isset_ = false;
  }

BankCsp::BankCsp(std::string filename, const int csp_num) : Filter(Filter::inDomainSpatial) {
  this->_stype 	= "filter";
  this->_name 	= "cnbi-bankcsp";

  this->config_.filename = filename;
  this->isset_ = false;

  this->Setup(filename, csp_num);
}

BankCsp::~BankCsp(void) {}

bool BankCsp::Setup(std::string filename, const int csp_num) {
  hdr_t hdr;

  std::ifstream ifs;
  ifs.exceptions (std::ifstream::failbit | std::ifstream::badbit);

  try {
    ifs.open(filename.c_str(), std::ios::in | std::ios::binary);

    proc_readheader(ifs, &hdr);

    proc_check_string(hdr.type, this->_stype, "Binary file has not CSP type" );
    proc_check_string(hdr.label, this->_name, "Binary file has not CSP label" );

    this->config_.filename 	    = filename;
    this->config_.subject		    = proc_readstring(ifs);
    this->config_.num_channels	= proc_readbyte<uint32_t>(ifs);
    this->config_.num_filters  	= proc_readbyte<uint32_t>(ifs);

    Eigen::MatrixXd csp_coefficients_bank;
    proc_readeigen(ifs, csp_coefficients_bank);
    Eigen::Matrix<uint32_t, Eigen::Dynamic, Eigen::Dynamic> csp_map_bank;
    proc_readeigen(ifs, csp_map_bank);

    this->csp_coefficients_bank_.erase(this->csp_coefficients_bank_.begin(),this->csp_coefficients_bank_.end());
    this->csp_map_bank_.erase(this->csp_map_bank_.begin(),this->csp_map_bank_.end());
    for (auto it=0; it != (int)config_.num_filters; it++) {
      this->csp_coefficients_bank_.push_back(csp_coefficients_bank.block(0 + it*this->config_.num_channels,
                                                                       0, this->config_.num_channels,
                                                                       this->config_.num_channels));
      std::vector<uint32_t> csp_map(csp_map_bank.col(it).data(), csp_map_bank.col(it).data() + csp_map_bank.rows());
      this->csp_map_bank_.push_back(csp_map);
    }
    this->isset_ = true;

    this->SetBankCspNumPatterns(csp_num);
;

    ifs.close();
  } catch (wtk::core::Exception& e) {
    throw std::runtime_error("Can't load CSP filter parameters: " + filename);
  } catch (std::ifstream::failure e) {
    throw std::runtime_error("Wrong format for CSP filter parameters: " + filename);
  }
  return this->IsSet();
}


bool BankCsp::Setup(const std::vector<Eigen::MatrixXd>& data_in,
                const std::vector<std::vector<uint32_t> >& data_labels,
                const int csp_num, std::string subject) {

  if (data_in.size() != data_labels.size()) {
    throw std::runtime_error("data_in length is different form data_labels length");
  }

  this->isset_ = false;

  this->_stype 	= "filter";
  this->_name 	= "cnbi-csp";

  this->config_.filename = "";
  this->config_.subject  = subject;
  this->config_.num_channels = data_in.at(0).cols();
  this->config_.num_filters = data_in.size();
  this->SetBankCspNumPatterns(csp_num);

  // Resetting stored csp_coefficients_bank and csp__map_bank
  this->csp_coefficients_bank_.erase(this->csp_coefficients_bank_.begin(), this->csp_coefficients_bank_.end());
  this->csp_map_bank_.erase(this->csp_map_bank_.begin(), this->csp_map_bank_.end());

  auto labelsit = data_labels.begin();
  for (auto init = data_in.begin(); init != data_in.end();
       init ++) {

    if ((*init).rows() != (int)(*labelsit).size()) {
      throw std::runtime_error("data_in number of rows has to be the same length of data_labels");
    }
    std::vector<uint32_t> class_labels((*labelsit));
    std::sort(class_labels.begin(), class_labels.end() );
    class_labels.erase(std::unique(class_labels.begin(), class_labels.end()), class_labels.end());
    if(*class_labels.begin() == 0) {
      class_labels.erase(class_labels.begin());
    }
    if (class_labels.size()>2) {
      throw std::runtime_error("More than two class labels are listed in data_labels: "
                                 "only two class events can be present in data_in");
    } else {
      std::vector<std::vector<uint32_t>::const_iterator> indexes_first_class;
      std::vector<std::vector<uint32_t>::const_iterator> indexes_second_class;
      for (auto it = (*labelsit).begin(); it != (*labelsit).end(); it++) {
        if (*it == *class_labels.begin()) {
          indexes_first_class.push_back(it);
        }
        else if(*it == *(class_labels.end() - 1)) {
          indexes_second_class.push_back(it);
        }
      }

      // extraction of data from first class
      Eigen::MatrixXd data_in_first_class(0, this->config_.num_channels);
      for (auto it = indexes_first_class.begin(); it!=indexes_first_class.end(); it++) {
        data_in_first_class.conservativeResize(data_in_first_class.rows()+1,
                                               data_in_first_class.cols());
        data_in_first_class.row(data_in_first_class.rows()-1) =
            (*init).row(std::distance((*labelsit).begin(), *it));
      }
      data_in_first_class.transposeInPlace();

      // extraction of data from second class
      Eigen::MatrixXd data_in_second_class(0, this->config_.num_channels);
      for (auto it = indexes_second_class.begin(); it!=indexes_second_class.end(); it++) {
        data_in_second_class.conservativeResize(data_in_second_class.rows()+1,
                                               data_in_second_class.cols());
        data_in_second_class.row(data_in_second_class.rows()-1) =
            (*init).row(std::distance((*labelsit).begin(), *it));
      }
      data_in_second_class.transposeInPlace();

      // Finding the covariance of each calss and composite covariance
      Eigen::MatrixXd R_first_class = data_in_first_class * data_in_first_class.transpose();
      R_first_class = R_first_class / R_first_class.trace();
      Eigen::MatrixXd R_second_class = data_in_second_class * data_in_second_class.transpose();
      R_second_class = R_second_class / R_second_class.trace();

      // Ramoser equation
      Eigen::MatrixXd R = R_first_class + R_second_class;

      // Sort eigenvalues in descending order
      Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> eigensolver(R);
      Eigen::MatrixXd eigen_vectors = eigensolver.eigenvectors();
      Eigen::VectorXd eigen_values  = eigensolver.eigenvalues();

      std::vector<uint32_t> indices(eigen_values.size());
      std::iota(indices.begin(), indices.end(), 0);
      std::sort(indices.begin(), indices.end(),
                  [&eigen_values](uint32_t a, uint32_t b){return eigen_values[a] > eigen_values[b];} );
      Eigen::MatrixXd sorted_eigen_vectors(eigen_vectors);
      Eigen::MatrixXd sorted_eigen_values(eigen_values);
      int column_pointer = 0;
      for (auto it = indices.begin(); it != indices.end(); it++) {
        sorted_eigen_vectors.col(column_pointer)  = eigen_vectors.col(*it);
        sorted_eigen_values(column_pointer)       = eigen_values(*it);
        column_pointer++;
      }

      // Find Whitening Transformation Matrix
      Eigen::MatrixXd temp(sorted_eigen_values.asDiagonal().inverse());
      Eigen::MatrixXd W = temp.array().sqrt().matrix() * sorted_eigen_vectors.transpose();
      // Whiten Data Using Whiting Transform
      Eigen::MatrixXd S_first_class = W * R_first_class * W.transpose();
      Eigen::MatrixXd S_second_class = W * R_second_class * W.transpose();
      // Generalized eigenvectors/values
      Eigen::GeneralizedSelfAdjointEigenSolver<Eigen::MatrixXd> generaleigensolver;
      generaleigensolver.compute(S_first_class, S_second_class);
      eigen_vectors = generaleigensolver.eigenvectors();
      eigen_values = generaleigensolver.eigenvalues();
      std::iota(indices.begin(), indices.end(), 0);
      std::sort(indices.begin(), indices.end(),
                  [&eigen_values](uint32_t a, uint32_t b){return eigen_values[a] < eigen_values[b];} );
      column_pointer = 0;
      for (auto it = indices.begin(); it != indices.end(); it++) {
        sorted_eigen_vectors.col(column_pointer)  = eigen_vectors.col(*it);
        column_pointer++;
      }
      // Resulting Projection Matrix-these are the spatial filter coefficients
      this->csp_coefficients_bank_.push_back(sorted_eigen_vectors.transpose() * W);
      this->csp_map_bank_.push_back(indices);
      labelsit++;
    }
    this->isset_ = true;
  }
  return this->IsSet();
}

void BankCsp::GetBankCspCoefficients(std::vector<Eigen::MatrixXd>& csp_coefficients_bank) {
  try {
     this ->IsSet();
     csp_coefficients_bank.erase(csp_coefficients_bank.begin(),csp_coefficients_bank.end());
     csp_coefficients_bank = this->csp_coefficients_bank_;
   }  catch (wtk::core::Exception& e) {
     throw std::runtime_error("Error getting CSP coefficients bank filter");
   }

}

void BankCsp::SetBankCspCoefficients(const std::vector<Eigen::MatrixXd>& csp_coefficients_bank) {
  this->csp_coefficients_bank_.erase(this->csp_coefficients_bank_.begin(),this->csp_coefficients_bank_.end());
  for (auto it = csp_coefficients_bank.begin(); it != csp_coefficients_bank.end(); it++) {
    this->csp_coefficients_bank_.push_back(*it);
  }
}

void BankCsp::GetBankCspMap(std::vector<std::vector<uint32_t> >& csp_map_bank) {
  try {
     this ->IsSet();
     csp_map_bank.erase(csp_map_bank.begin(),csp_map_bank.end());
     for (auto it = this->csp_map_bank_.begin(); it != this->csp_map_bank_.end(); it++) {
       csp_map_bank.push_back(*it);
     }
   }  catch (wtk::core::Exception& e) {
     throw std::runtime_error("Error getting CSP map bank filter");
   }

}

void BankCsp::SetBankCspMap(const std::vector<std::vector<uint32_t> >& csp_map_bank) {
  this->csp_map_bank_.erase(this->csp_map_bank_.begin(),this->csp_map_bank_.end());
  for (auto it = csp_map_bank.begin(); it != csp_map_bank.end(); it++) {
    this->csp_map_bank_.push_back(*it);
  }
}

void BankCsp::SetBankCspNumPatterns(const int csp_num) {
  try {
    if (csp_num > (int)config_.num_channels) {
      printf("[CSP bank filter] - WARNING:\n");
      printf("                  - num_patterns = %i\n", csp_num);
      printf("	          - Number of patterns selected is higher than channel dimmension csp_num set to %i\n",
            config_.num_channels);
      config_.num_patterns = config_.num_channels;
    }
    else if (csp_num == 0) {
      printf("[CSP bank filter] - WARNING:\n");
      printf("                  - num_patterns is not setted\n");
      printf("	          - Number of patterns selected is inizialized as channel dimmension\n");
      this->config_.num_patterns = config_.num_channels;
    }
    else if (csp_num % 2 != 0) {
      printf("[CSP bank filter] - WARNING:\n");
      printf("	          - csp_num = %i\n", csp_num);
      printf("	          - Number of patterns selected is odd, patterns composition will not be symmetric\n");
      this->config_.num_patterns = csp_num;
    }
    else {
      this->config_.num_patterns = csp_num;
    }
  } catch (wtk::core::Exception& e) {
    throw std::runtime_error("Can't set num_patterns");
  }
}

void BankCsp::GetBankW(std::vector<Eigen::MatrixXd>& W_bank) {
  try {
    this->IsSet();
    W_bank.erase(W_bank.begin(),W_bank.end());
    for (auto filterit = 1; filterit != (int)this->config_.num_filters; filterit++) {
      Eigen::MatrixXd cspfiltmat(config_.num_patterns, config_.num_channels);
      int patternid = 0;
      for (auto it = 0; it != (int)config_.num_patterns; it++) {
        if(it % 2 == 0) {
          cspfiltmat.row(it) = this->csp_coefficients_bank_.at(filterit).row(patternid);
        } else {
          cspfiltmat.row(it) = this->csp_coefficients_bank_.at(filterit).row(config_.num_channels - 1 - patternid);
          patternid++;
        }
      }
      W_bank.push_back(cspfiltmat.transpose());
    }
  } catch (wtk::core::Exception& e) {
    throw std::runtime_error("Can't get W filt bank matrix");
  }
}

void BankCsp::GetCspCoefficients(Eigen::Ref<Eigen::MatrixXd> csp_coefficients, const int filter_id) {
  try {
     this ->IsSet();
     csp_coefficients = this->csp_coefficients_bank_.at(filter_id);
   }  catch (wtk::core::Exception& e) {
     const std::string errorstring("Error getting CSP coefficients of "
                                   + std::to_string(filter_id) + "-th filter");
     throw std::runtime_error(errorstring);
   }

}

void BankCsp::SetCspCoefficients(const Eigen::Ref<const Eigen::MatrixXd>& csp_coefficients, const int filter_id) {
  this->csp_coefficients_bank_.at(filter_id) = csp_coefficients;
}

void BankCsp::GetCspMap(std::vector<uint32_t>& csp_map, const int filter_id) {
  try {
     this ->IsSet();
     csp_map.assign(this->csp_map_bank_.at(filter_id).begin(), this->csp_map_bank_.at(filter_id).end());
   }  catch (wtk::core::Exception& e) {
     const std::string errorstring("Error getting CSP map of "
                                   + std::to_string(filter_id) + "-th filter");
     throw std::runtime_error(errorstring);
   }
}

void BankCsp::SetCspMap(const std::vector<uint32_t>& csp_map, const int filter_id) {
  this->csp_map_bank_.at(filter_id) = csp_map;
}

void BankCsp::GetW(Eigen::Ref<Eigen::MatrixXd> W, const int filter_id) {
  try {
    this->IsSet();

    Eigen::MatrixXd cspfiltmat(config_.num_patterns, config_.num_channels);
    int patternid = 0;
    for (auto it = 0; it != (int)config_.num_patterns; it++) {
      if(it % 2 == 0) {
        cspfiltmat.row(it) = this->csp_coefficients_bank_.at(filter_id).row(patternid);
      } else {
        cspfiltmat.row(it) = this->csp_coefficients_bank_.at(filter_id).row(config_.num_channels - 1 - patternid);
        patternid++;
      }
    }
    W = cspfiltmat.transpose();
  } catch (wtk::core::Exception& e) {
    const std::string errorstring("Error getting W matrix of "
                                  + std::to_string(filter_id) + "-th filter");
    throw std::runtime_error(errorstring);
  }
}

void BankCsp::SetCspFilterId(const int filter_id) {
  this->csp_filter_id_ = filter_id;
}

void BankCsp::Apply(const Eigen::Ref<const Eigen::MatrixXd>& data_in, Eigen::Ref<Eigen::MatrixXd> data_out) {
  try {
     this ->IsSet();

     //int channels_num = data_in.cols();
     Eigen::MatrixXd W(this->config_.num_channels, this->config_.num_patterns);
     this->GetW(W,this->csp_filter_id_);
     data_out = data_in * W;

   }  catch (wtk::core::Exception& e) {
     const std::string errorstring("Error applying CSP in "
                                   + std::to_string(this->csp_filter_id_) + "-th filter");
     throw std::runtime_error(errorstring);
   }
}

void BankCsp::BankApply(const std::vector<Eigen::MatrixXd>& data_in, std::vector<Eigen::MatrixXd>& data_out) {
  try {
    this ->IsSet();
    for (auto it = 0; it != (int)this->config_.num_filters; it++) {
      this->SetCspFilterId(it);
      this->Apply(data_in.at(it), data_out.at(it));
    }

  } catch (wtk::core::Exception& e) {
    throw std::runtime_error("Error applying CSP bank filter");
  }
}

bool BankCsp::IsSet(void) {
  if(this->isset_ == false)
    throw wtk::core::Exception("The CSP bank filter is not setup");

  return this->isset_;
}

void BankCsp::Dump(void) {

  printf("[CSP bank filter] - Configuration:\n");
  printf("       	        | - Filter filename: 		%s\n", this->config_.filename.c_str());
  printf("	        | - Number of selected CSP patterns:  	%d\n", this->config_.num_patterns);
  printf("  	        | - Number of filters in the CSP bank:  %d\n", this->config_.num_filters);
}

	}
}
#endif
