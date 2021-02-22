
/* Albino Bacolla
   MDACC
   Molecular & Cellular Oncology
   6767 Bertner Avenue
   Houston TX 77033
   abacolla@mdanderson.org
   April 2019
*/
//  vga_linearRegression.hpp -- workflow for computing regression coefficient R and p-value P for a linear regression

#ifndef VGA_LINEAREGR_HPP
#define VGA_LINEAREGR_HPP

#include <fstream>
#include <iostream>
#include <iterator>
#include <cmath>

namespace vga {

  template<typename InputIterator> // get R value for linear regression
  double forEachPair(InputIterator begin, InputIterator end) {
    double sumXY{};
    double sumX{};
    double sumY{};
    double sumX2{};
    double sumY2{};
    size_t n{};
    double r{};
    while (begin != end) {
      sumXY += (*begin).first * (*begin).second;
      sumX += (*begin).first;
      sumY += (*begin).second;
      sumX2 += (*begin).first * (*begin).first;
      sumY2 += (*begin).second * (*begin).second;
      ++n;
      ++begin;
    }
    float numerat = (n * sumXY) - (sumX * sumY);
    float denom1 = ((n * sumX2) - (sumX*sumX)) * ((n * sumY2) - (sumY*sumY));
    float denom2 = sqrt(denom1);
    r = numerat / denom2;
    return r;
  }

  template<typename T, typename Container>
  class LinearRegr {

    public:
    void readPairOfVals(T, Container);
    double r_value{};
    double getF(double const&);
    int N{}; // vector size and number of elements
  };

  template<typename T, typename Container>
  void LinearRegr<T, Container>::readPairOfVals(T inFile, Container coll) {
    if (!coll.empty()) {
        coll.clear();
    }
    std::ifstream file1(inFile);
    if (file1.is_open()) {
      double valFirst{}, valSecond{};
      while (file1 >> valFirst >> valSecond) {
        coll.emplace_back (std::pair<double, double>(valFirst, valSecond));
      }
      file1.close();
    }
    else {
      std::cerr << "Could not open " << inFile << '\n';
    }
    r_value = forEachPair(coll.begin(), coll.end());
    N = coll.size();
  } 
  
  template<typename T, typename Container>
  double LinearRegr<T, Container>::getF(double const& rVal) {
    double F = (r_value * r_value * (N - 2)) / (1 - r_value * r_value);
    return F;
  }
}
#endif // VGA_LINEAREGR_HPP
