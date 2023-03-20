// -*- coding: utf-8 -*-

#define EIGEN_DONT_PARALLELIZE // 並列化を無効化．

#include <iostream>
#include <ostream>
#include <fstream>
#include <vector>
#include <random>
//#include <Eigen/Dense>
#include <chrono>
#include <cmath>
#include <omp.h>
#include <numeric>
#include <execution>
#include <algorithm>
//#include <ranges>

//dbg-------------------
//#include <variant>
//#include <complex>
//#include <type_traits>
//#include <concepts>
//#include <typeinfo>
//dbg-------------------

int main(){
  std::cout.precision(10); // Show 10 digits

  std::mt19937 engine;
  std::uniform_real_distribution<> dist(-1.0, 1.0);

  std::cout << "hello" << std::endl;

//  int n = 5000;
//  int m = 5000;
  int n;
  int m;
  {
    std::ifstream fr("input");
    fr >> n >> m;
  }
  std::vector<std::vector<double>> A(n, std::vector<double>(m, 0.0));
  std::vector<std::vector<double>> D(n, std::vector<double>(m, 0.0));
  std::vector<std::vector<double>> E(n, std::vector<double>(m, 0.0));
  std::vector<double> b(m, 0.0);
  std::vector<double> c(m, 0.0);
  std::vector<int> idx(n, 0);
  std::vector<int> jdx(m, 0);
  std::vector<int> ijdx(n*m, 0);
  //  std::vector<std::vector<double>> AA(n, std::vector<double>(m, 0.0));
  //  std::vector<std::vector<double>> DD(n, std::vector<double>(m, 0.0));
  //  std::vector<std::vector<double>> EE(n, std::vector<double>(m, 0.0));
  std::vector<double> AA(n*m, 0.0);
  std::vector<double> DD(n*m, 0.0);
  std::vector<double> EE(n*m, 0.0);
  std::vector<double> bb(m, 0.0);
  std::vector<double> cc(m, 0.0);

  //  auto v = std::ranges::views::iota(0, n*m);

  for(int j = 0; j < n; j++){
    for(int i = 0; i < m; i++){
      DD[j*n + i] = D[j][i] = AA[j*n + i] = A[j][i] = dist(engine);
      ijdx[i*n + j] = i*n + j;
    }
    bb[j] = b[j] = dist(engine);
    idx[j] = jdx[j] = j;
  }

  std::chrono::system_clock::time_point start = std::chrono::system_clock::now();

  //#pragma omp parallel for
  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      //      c[i] += A[i][j]*b[j];
      E[i][j] = A[i][j] + D[i][j];
    }
  }

  std::chrono::system_clock::time_point mid = std::chrono::system_clock::now();

//  std::for_each(std::execution::par,
// 		idx.begin(), idx.end(),
// 		[&EE, &AA, &DD, &jdx](int idx){
// 		  std::for_each(std::execution::par_unseq,
// 				jdx.begin(), jdx.end(),
// 				//				[&](int jdx){cc[idx] += AA[idx][jdx]*bb[jdx];}
// 				[idx, &AA, &DD, &EE](int jdx){EE[idx][jdx] = AA[idx][jdx] + DD[idx][jdx];}
// 				);
// 		}
// 		);
  std::transform(std::execution::par_unseq,
		 AA.begin(), AA.end(), DD.begin(), EE.begin(),
		 [](double x, double y){
		   return x + y;}
		 );

  std::chrono::system_clock::time_point end = std::chrono::system_clock::now();

//  std::for_each(std::execution::seq,
// 		EE.begin(), EE.end(),
// 		[](double x){std::cout << "EE x " << x << std::endl;}
// 		);
//  std::for_each(std::execution::seq,
// 		AA.begin(), AA.end(),
// 		[](double x){std::cout << "AA x " << x << std::endl;}
// 		);
//  std::for_each(std::execution::seq,
// 		DD.begin(), DD.end(),
// 		[](double x){std::cout << "DD x " << x << std::endl;}
// 		);

  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      c[i] += E[i][j]*b[j];
      //      cc[i] += EE[i][j]*b[j];
      cc[i] += EE[i*n + j]*b[j];
    }
  }

  std::cout << "size " << n << std::endl;
  std::cout << "c sum " << std::accumulate(c.begin(), c.end(), 0.0) << std::endl;
  std::cout << "cc sum " << std::accumulate(cc.begin(), cc.end(), 0.0) << std::endl;
  std::cout << "elasped time for " << static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(mid - start).count()/1.0e6) << std::endl;
  std::cout << "elasped time for_each " << static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(end - mid).count()/1.0e6) << std::endl;
}
