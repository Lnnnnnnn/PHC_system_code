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
#include "hls_math.h"

using namespace std;


typedef ap_fixed<16, 2> float16_h_t;
typedef ap_fixed<16, 13> float16_t;
typedef ap_int<16> ap_int_4;

typedef ap_fixed<32, 28> float_sp;

//typedef float float16_h_t;
//typedef float float16_t;
//typedef int ap_int_4;
//
//typedef float float_sp;

const short XNSIZE = 5;
const short UNSIZE = 6;
const short VNSIZE = 2;

const short GATESIZE = 64;

const short HORIZON = 2;
const short THREADNUM = 64;


//Math Function
//void multimartix (float16_t a[N][P], float16_t b[P][M], float16_t out[N][M]);
void mulvector3x3(float16_h_t a[3][3], float16_t b[3], float16_t out[3]);

void mulvector5x5(float16_t a[5][5], float16_t b[5], float16_t out[5]);

void mulvector5x6(float16_t a[5][6], float16_t b[6], float16_t out[5]);

void mulvector5x2(float16_t a[5][2], float16_t b[2], float16_t out[5]);


float16_t JcalcValue(float16_t xref[XNSIZE], float16_t xn_current[XNSIZE], ap_int_4 laststate, ap_int_4 currentstate);

void statespace(float16_t xn_in[XNSIZE], float16_t xn_out[XNSIZE], float16_t u[XNSIZE], float16_t v[XNSIZE]) ;

void statespaceNew(float16_t xn_currentNew[], float16_t xn_current[], float16_t u[], float16_t v[], float16_h_t A[5][5],
                   float16_h_t B[5][6],
                   float16_h_t E[5][2]);

//Thread Function
void MPCworkstate(float16_t *Jmin, float16_t *CalcNum, ap_int_4 *nextgate, ap_int_4 *state, float16_t xn_current[],
                  float16_t xn_visited[][XNSIZE],
                  ap_int_4 *index, ap_int_4 INIT_index, ap_int_4 *branch, ap_int_4 INIT_branch, ap_int_4 location[],
                  float16_t *J_current, float16_t J_visited[],
                  ap_int_4 helpedList[], ap_int_4 assignmentList, float16_t prestate[],
                  float16_t xref[], float16_t U_SET[][64], ap_int_4 GATE[][6], float16_t x[],
                  float16_h_t A[5][5], float16_h_t B[5][6], float16_h_t E[5][2], float16_t v[],
                  float16_h_t Qquad[XNSIZE], float16_t Qswitch[UNSIZE], float16_t QswitchConst[UNSIZE],
                  float16_t Qcurrentlim[UNSIZE], float16_t CL);

void MPChelpstate(float16_t *Jmin, float16_t *CalcNum, ap_int_4 *nextgate, ap_int_4 *state, float16_t xn_current[],
                  float16_t xn_visited[][XNSIZE],
                  ap_int_4 *index, ap_int_4 INIT_index, ap_int_4 *branch, ap_int_4 INIT_branch, ap_int_4 location[],
                  float16_t *J_current, float16_t J_visited[],
                  ap_int_4 helpedList[], ap_int_4 assignmentList, float16_t prestate[],
                  float16_t xref[], float16_t U_SET[][64], ap_int_4 GATE[][6], float16_t x[],
                  float16_h_t A[5][5], float16_h_t B[5][6], float16_h_t E[5][2], float16_t v[],
                  float16_h_t Qquad[XNSIZE], float16_t Qswitch[UNSIZE], float16_t QswitchConst[UNSIZE],
                  float16_t Qcurrentlim[UNSIZE], float16_t CL);


void SimplifyCal(float16_t *Jmin, float16_t *CalcNum, ap_int_4 *nextgate, ap_int_4 *state, float16_t xn_current[XNSIZE],
                 ap_int_4 *index, ap_int_4 location[HORIZON],
                 float16_t *J_current, float16_t prestate[UNSIZE],
                 float16_t xref[XNSIZE], float16_t U_SET[XNSIZE][64], ap_int_4 GATE[64][UNSIZE], float16_t x[XNSIZE],
                 float16_h_t A[5][5], float16_h_t B[5][6], float16_h_t E[5][2], float16_t v[XNSIZE],
                 float16_h_t Qquad[XNSIZE], float16_t Qswitch[UNSIZE], float16_t QswitchConst[UNSIZE],
                 float16_t Qcurrentlim[UNSIZE], float16_t CL);

void MPCthread(float16_t *Jmin, float16_t *CalcNum, ap_int_4 *nextgate, ap_int_4 *state, float16_t xn_current[],
               float16_t xn_visited[][XNSIZE],
               ap_int_4 *index, ap_int_4 INIT_index, ap_int_4 *branch, ap_int_4 INIT_branch, ap_int_4 location[],
               float16_t *J_current, float16_t J_visited[],
               ap_int_4 helpedList[], ap_int_4 assignmentList,
               float16_t xref[XNSIZE], float16_t x[XNSIZE], float16_t v[VNSIZE], float16_t prestate[]);

bool MPCendCondition(ap_int_4 locations[THREADNUM][HORIZON]);

void Statespace_function (float16_t x_in[XNSIZE], float16_t x_out[XNSIZE], float16_t v[VNSIZE], ap_int_4 y);
void Cost_function(float16_t xref[XNSIZE], float16_t xn_current[THREADNUM][XNSIZE], ap_int_4 laststate,float16_t Js[THREADNUM]);

void MPCcore(float16_t *y, float16_t *J, float16_t *Calc,
             float16_t xref[5], float16_t x[5],
             float16_t v[2], float16_t prestate[6]);

#endif //PHC_DFS_PARALLEL_AP_HEADER_H
