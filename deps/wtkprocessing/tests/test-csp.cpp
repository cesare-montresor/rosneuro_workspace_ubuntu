#include <wtkcore/Time.hpp>
#include <eigen3/Eigen/Dense>
#include "../src/Csp.hpp"
//#include "../src/BankCsp.hpp"


using namespace wtk::core;
using namespace wtk::proc;



int main(int argc, char** argv) {
  std::string filename  = "/home/cimolato/Documents/20160316_b9/classifier/b9_cspfilter_20161219.dat";
  Csp cspfilter(filename);

  printf("[test-csp] - Testing GetCspMap\n");
  printf("           - Printing stored CSP patterns map:\n");
  std::vector<uint32_t> csp_map;
  cspfilter.GetCspMap(csp_map);
  for (auto it=csp_map.begin(); it!=csp_map.end(); it++) {
    std::cout << *it << std::endl;
  }
  Time::Sleep(2000);

  printf("[test-csp] - Testing GetCspCoefficients\n");
  printf("           - Printing stored CSP coefficients:\n");
  Eigen::MatrixXd csp_coefficients(cspfilter.config_.num_channels,cspfilter.config_.num_channels);
  cspfilter.GetCspCoefficients(csp_coefficients);
  std::cout << csp_coefficients << std::endl;
  Time::Sleep(2000);

  printf("[test-csp] - Testing SetCspNumPatterns\n");
  printf("           - Now Number of patterns are %i\n", cspfilter.config_.num_patterns);
  uint32_t csp_num(32);
  printf("           - Setting Number of patterns to %i\n", csp_num);
  cspfilter.SetCspNumPatterns(csp_num);
  printf("           - Now Number of patterns are %i\n", cspfilter.config_.num_patterns);
  csp_num = 7;
  printf("           - Setting Number of patterns to %i\n", csp_num);
  cspfilter.SetCspNumPatterns(csp_num);
  printf("           - Now Number of patterns are %i\n", cspfilter.config_.num_patterns);
  csp_num = 6;
  printf("           - Setting Number of patterns to %i\n", csp_num);
  cspfilter.SetCspNumPatterns(csp_num);
  printf("           - Now Number of patterns are %i\n", cspfilter.config_.num_patterns);
  Time::Sleep(2000);

  printf("[test-csp] - Testing GetW\n");
  printf("           - Printing W filt matrix:\n");
  Eigen::MatrixXd W(cspfilter.config_.num_channels, cspfilter.config_.num_patterns);
  cspfilter.GetW(W);
  std::cout << W << std::endl;
  Time::Sleep(2000);

  printf("[test-csp] - Testing Apply\n");
  printf("           - Printing filtered patterns:\n");
  Eigen::MatrixXd X = Eigen::MatrixXd::Ones(100, cspfilter.config_.num_channels);
  Eigen::MatrixXd Y(100, cspfilter.config_.num_patterns);
  cspfilter.Apply(X, Y);
  std::cout << Y << std::endl;
  Time::Sleep(2000);


  printf("[test-csp] - Testing SetCspMap\n");
  csp_map.at(0) = 45;
  cspfilter.SetCspMap(csp_map);
  printf("           - Printing the new stored CSP patterns map:\n");
  cspfilter.GetCspMap(csp_map);
  for (auto it=csp_map.begin(); it!=csp_map.end(); it++) {
    std::cout << *it << std::endl;
  }
  Time::Sleep(2000);

  printf("[test-csp] - Testing SetCspCoeff\n");
  csp_coefficients.row(0) = csp_coefficients.row(1);
  cspfilter.SetCspCoefficients(csp_coefficients);
  printf("           - Printing stored CSP coefficients:\n");
  cspfilter.GetCspCoefficients(csp_coefficients);
  std::cout << csp_coefficients << std::endl;
  Time::Sleep(2000);

  printf("[test-csp] - Testing Setup with data_in\n");

  X = Eigen::MatrixXd::Identity(10, 2);
  X.col(0) << 9,8,7,6,5,4,3,2,1,0;
  X.col(1) << 0, 1,2,3,4,5,6,7,8,9;
  std::cout << X << std::endl;
  printf("           - and labels:\n");
  std::vector<uint32_t> data_labels={1, 1, 1, 2, 2, 2, 1, 1, 2, 2};
  for (auto it=data_labels.begin(); it!=data_labels.end(); it++) {
    std::cout << *it << std::endl;
  }
  cspfilter.Setup(X, data_labels);
    printf("           - Printing filt result:\n");
  Eigen::MatrixXd Z(10, 2);
  cspfilter.Apply(X, Z);
  std::cout << Z << std::endl;
  Time::Sleep(2000);


}
