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
typedef ap_fixed<16, 10> float16_t;
typedef ap_int<16> ap_int_4;
typedef ap_fixed<32, 24> float_sp;

typedef ap_fixed<32, 26> APFIX_32_Qq;
typedef ap_fixed<32, 26>  APFIX_32_Qsw;
typedef ap_fixed<32, 26>  APFIX_32_QswConst;
typedef ap_fixed<32, 26>  APFIX_32_Qcur;

typedef ap_fixed<16, 6> APFIX_16_Qquad;
typedef ap_fixed<16, 6> APFIX_16_Qsw;
typedef ap_int<16> APFIX_16_QswConst_IGBT;
typedef ap_fixed<16, 6> APFIX_16_QswConst_MOS;
typedef ap_fixed<16, 6> APFIX_16_Qcur;

//typedef float float16_h_t;
//typedef float float16_t;
//typedef int ap_int_4;
//typedef float float_sp;
//
//typedef float  APFIX_32_Qq;
//typedef float  APFIX_32_Qsw;
//typedef float  APFIX_32_QswConst;
//typedef float  APFIX_32_Qcur;
//
//typedef float APFIX_16_Qquad;
//typedef float APFIX_16_Qsw;
//typedef float APFIX_16_QswConst_IGBT;
//typedef float APFIX_16_QswConst_MOS;
//typedef float APFIX_16_Qcur;


using namespace std;

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

float_sp JcalcValue(float16_t xref[XNSIZE], float16_t xn_current[XNSIZE], APFIX_16_Qquad Qquad,
                    APFIX_16_Qsw Qswitch, bool previous_state[UNSIZE], bool current_state[UNSIZE],
                    APFIX_16_Qcur Qcurrentlim, APFIX_16_QswConst_IGBT QswitchConst_IGBT, APFIX_16_QswConst_MOS QswitchConst_MOS, float16_t CL);

void statespace(float16_t xn_current[XNSIZE], float16_t u[XNSIZE], float16_t v[XNSIZE]);

void statespaceNew (float16_t xn_currentNew[], float16_t xn_current[], float16_t u[], float16_t v[], float16_h_t A[5][5], float16_h_t B[5][6],
                    float16_h_t E[5][2]);

//Thread Function
//void MPCworkstate(float16_t *Jmin, float16_t *CalcNum, ap_int_4 *nextgate, ap_int_4 *state, float16_t xn_current[],
//                  float16_t xn_visited[][XNSIZE],
//                  ap_int_4 *index, ap_int_4 INIT_index, ap_int_4 *branch, ap_int_4 INIT_branch, ap_int_4 location[],
//                  float16_t *J_current, float16_t J_visited[],
//                  ap_int_4 helpedList[], ap_int_4 assignmentList, float16_t prestate[],
//                  float16_t xref[], float16_t U_SET[][64], ap_int_4 GATE[][6], float16_t x[],
//                  float16_h_t A[5][5], float16_h_t B[5][6], float16_h_t E[5][2], float16_t v[],
//                  float16_h_t Qquad[XNSIZE], float16_t Qswitch[UNSIZE], float16_t QswitchConst[UNSIZE],
//                  float16_t Qcurrentlim[UNSIZE], float16_t CL);

//void MPChelpstate(float16_t *Jmin, float16_t *CalcNum, ap_int_4 *nextgate, ap_int_4 *state, float16_t xn_current[],
//                  float16_t xn_visited[][XNSIZE],
//                  ap_int_4 *index, ap_int_4 INIT_index, ap_int_4 *branch, ap_int_4 INIT_branch, ap_int_4 location[],
//                  float16_t *J_current, float16_t J_visited[],
//                  ap_int_4 helpedList[], ap_int_4 assignmentList, float16_t prestate[],
//                  float16_t xref[], float16_t U_SET[][64], ap_int_4 GATE[][6], float16_t x[],
//                  float16_h_t A[5][5], float16_h_t B[5][6], float16_h_t E[5][2], float16_t v[],
//                  float16_h_t Qquad[XNSIZE], float16_t Qswitch[UNSIZE], float16_t QswitchConst[UNSIZE],
//                  float16_t Qcurrentlim[UNSIZE], float16_t CL);


void SimplifyCal(float_sp *Jmin, float16_t *CalcNum, ap_int_4 *nextgate,
                 ap_int_4 *index, ap_int_4 location[HORIZON],
                 float_sp *J_current, bool prestate[UNSIZE],
                 float16_t xref[XNSIZE], float16_t U_SET[XNSIZE][64], ap_int_4 GATE[64][UNSIZE], float16_t x[XNSIZE], float16_t v[XNSIZE],
                 APFIX_16_Qquad Qquad, APFIX_16_Qsw Qswitch, APFIX_16_QswConst_IGBT QswitchConst_IGBT, APFIX_16_QswConst_MOS QswitchConst_MOS,
                 APFIX_16_Qcur Qcurrentlim, float16_t CL);

void MPCthread(float_sp *Jmin, float16_t *CalcNum, ap_int_4 *nextgate,
               ap_int_4 *index, ap_int_4 location[],
               float_sp *J_current, float16_t xref[XNSIZE], float16_t x[XNSIZE], float16_t v[XNSIZE],
               bool prestate[6],
               APFIX_16_Qquad Q_quad, APFIX_16_Qsw Q_switch, APFIX_16_QswConst_IGBT Q_switchConst_IGBT, APFIX_16_QswConst_MOS Q_switchConst_MOS,
               APFIX_16_Qcur Q_currentlim);

void MPCcore(ap_int_4 *y, float_sp *J, float16_t &Calc,
             float16_t xref[5], float16_t x[5], bool gateT[6],
             float16_t v[2], bool p_state[6], float16_t x_pdic[5],
             APFIX_16_Qquad Q_quad, APFIX_16_Qsw Q_switch, APFIX_16_QswConst_IGBT Q_switchConst_IGBT, APFIX_16_QswConst_MOS Q_switchConst_MOS,
             APFIX_16_Qcur Q_currentlim);

#endif //PHC_DFS_PARALLEL_AP_HEADER_H
