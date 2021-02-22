/* Albino Bacolla
   MDACC
   Molecular & Cellular Oncology
   6767 Bertner Avenue
   Houston TX 77033
   abacolla@mdanderson.org
   April 2019
   vga_linearRegression.cpp -- return regression coefficient R and p-value for linear regression from 1 2-col file
*/

#include <iostream>
#include <vector>
#include <string>
#include "vga_linearRegression.hpp"
#include "vga_tTest_unequal_sd_s.hpp"

using namespace vga;

int main(int argc, char* argv[]) {
	// Step 1 - Usage
	if (argc != 2) {
		std::cout << "\nAuthor: albino bacolla\n"
        << "Synopsis: return r and p values for linear regression\n"
		<< "Usage: vga_linearRegression inFile\n"
		<< "Notes: inFifle is a 2-column file with paiwise data\n\n";

		return 0;
	}

  // Step 2 - Read data from file
  LinearRegr<std::string, std::vector<std::pair<double, double>>> mySet;
  std::vector<std::pair<double, double>> vec1;
  mySet.readPairOfVals(argv[1], vec1);

  // Step 3 - get R and P
  double rValue = mySet.r_value;
//  std::cout << argv[1] << "\tR\t" << mySet.r_value << '\n';
  double Fvalue = mySet.getF(rValue);
  int totN = mySet.N;
  double pValue = p_valueR(Fvalue, totN);
  std::cout << argv[1] << "\tR\t" << rValue << '\n';
  std::cout << argv[1] << "\tP\t" << std::setprecision(3) << std::scientific << pValue << '\n';  
 
}
