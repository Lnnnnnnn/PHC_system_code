//
// Created by s1805689 on 25/04/2022.
//
#ifndef PHC_DFS_PARALLEL_AP_HEADER_H
#define PHC_DFS_PARALLEL_AP_HEADER_H

#include <ap_fixed.h>
#include <ap_int.h>
#include "hls_vector.h"
#include "vector"
#include <queue>
#include <iostream>
//#include <hls_math.h>

using namespace std;


typedef ap_fixed<16, 8> float16_h_t;
typedef ap_fixed<16, 10> float16_t;
typedef ap_int<16> ap_int_4;

typedef ap_fixed<32, 28> float_sp;

//typedef float float16_h_t;
//typedef float float16_t;
//typedef int ap_int_4;
////
//typedef float float_sp;

using namespace std;

const short XNSIZE = 5;
const short UNSIZE = 6;
const short VNSIZE = 2;

const short GATESIZE = 64;

const short HORIZON = 2;
const short THREADNUM = 64;


//Math Function
//void multimartix (float16_t a[N][P], float16_t b[P][M], float16_t out[N][M]);

void T_abc_to_alphabeta(float16_t in[3], float16_t out[3]);

#endif //PHC_DFS_PARALLEL_AP_HEADER_H
