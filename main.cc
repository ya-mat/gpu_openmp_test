// -*- coding: utf-8 -*-

#define EIGEN_DONT_PARALLELIZE // 並列化を無効化．

#include <iostream>
#include <ostream>
#include <fstream>
#include <vector>
#include <random>
#include <Eigen/Dense>
#include <chrono>
#include <cmath>

//dbg-------------------
//#include <variant>
#include <complex>
//#include <type_traits>
#include <concepts>
//#include <typeinfo>
//dbg-------------------

int main(){
  std::cout.precision(10); // Show 10 digits

  //std::srand((unsigned int)time(NULL));
  //std::random_device seed_gen;
  //std::mt19937 engine(seed_gen());
  std::mt19937 engine;
  std::uniform_real_distribution<> dist(-1.0, 1.0);

  std::cout << "hello" << std::endl;

  double error = 0.0;
  int n = 1000;
  int m = 1000;
  std::vector<std::vector<double>> A(n, std::vector<double>(m, 0.0));
  std::vector<std::vector<double>> Anew(n, std::vector<double>(m, 0.0));

  for( int j = 1; j < n-1; j++) {
    for( int i = 1; i < m-1; i++ ) {
      A[j][i] = dist(engine);
    }
  }

#pragma omp parallel for reduction(max:error)
  for( int j = 1; j < n-1; j++) {
    for( int i = 1; i < m-1; i++ ) {
      Anew[j][i] = 0.25 * ( A[j][i+1] + A[j][i-1]
			    + A[j-1][i] + A[j+1][i]);
      error = fmax( error, fabs(Anew[j][i] - A[j][i]));
    }
  }

  std::cout << "error " << error << std::endl;
}
