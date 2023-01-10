//
// Created by s1805689 on 24/05/2022.
//

#include "ap_header.h"

void SimplifyCal(float_sp *Jmin, float16_t *CalcNum, ap_int_4 *nextgate,
                 ap_int_4 *index, ap_int_4 location[HORIZON],
                 float_sp *J_current, bool prestate[UNSIZE],
                 float16_t xref[XNSIZE], float16_t U_SET[XNSIZE][64], ap_int_4 GATE[64][UNSIZE], float16_t x[XNSIZE], float16_t v[XNSIZE],
                 APFIX_16_Qquad Qquad, APFIX_16_Qsw Qswitch, APFIX_16_QswConst_IGBT QswitchConst_IGBT, APFIX_16_QswConst_MOS QswitchConst_MOS,
                 APFIX_16_Qcur Qcurrentlim, float16_t CL) {

// STEP 2: Calculate state-space function and cost value for new J_current
    *CalcNum = *CalcNum + 1;  // count the total calcNum

    float16_t u[XNSIZE];
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=u
    for (ap_int_4 i = 0; i < XNSIZE; ++i) {
#pragma HLS UNROLL
        u[i] = U_SET[i][location[*index]];
    }


    bool previous_state[UNSIZE];
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=previous_state
    if (*index == 0) {
        for (ap_int_4 i = 0; i < UNSIZE; ++i) {
#pragma HLS UNROLL
            previous_state[i] = prestate[i];
        }
    } else {
        for (ap_int_4 i = 0; i < UNSIZE; ++i) {
#pragma HLS UNROLL
            previous_state[i] = GATE[location[*index - 1]][i];
        }
    }



    bool current_state[UNSIZE];
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=current_state
    for (ap_int_4 i = 0; i < UNSIZE; ++i) {
#pragma HLS UNROLL
        current_state[i] = GATE[location[*index]][i];
    }


    float16_t xn_currentNew[XNSIZE] = {0, 0, 0, 0, 0};

    if (*index == 0) {
        statespace(x, u, v);
    }
    if (*index == 1) {
        for (ap_int_4 i = 0; i < XNSIZE; ++i) {
#pragma HLS UNROLL
            xn_currentNew[i] = x[i];
        }
        statespace(x, u, v);
    }

    float_sp Jcalc = JcalcValue(xref, x, Qquad,
                                Qswitch, previous_state, current_state,
                                Qcurrentlim, QswitchConst_IGBT, QswitchConst_MOS, CL);


    *J_current = *J_current + Jcalc;

    if (*index == 1) {
        if (*J_current < *Jmin) {
            *Jmin = *J_current;
            *nextgate = location[0];
        }
        *J_current = *J_current - Jcalc;
        for (ap_int_4 i = 0; i < XNSIZE; ++i) {
#pragma HLS UNROLL
            x[i] = xn_currentNew[i];
        }
        location[*index] = location[*index] + 1;
    }

}

void MPCthread(float_sp *Jmin, float16_t *CalcNum, ap_int_4 *nextgate,
               ap_int_4 *index, ap_int_4 location[],
               float_sp *J_current, float16_t xref[XNSIZE], float16_t x[XNSIZE], float16_t v[XNSIZE],
               bool prestate[6],
               APFIX_16_Qquad Q_quad, APFIX_16_Qsw Q_switch, APFIX_16_QswConst_IGBT Q_switchConst_IGBT, APFIX_16_QswConst_MOS Q_switchConst_MOS,
               APFIX_16_Qcur Q_currentlim) {


    static float16_t U_SET[5][64] =
            {{0.00, 0.47,  -0.23, 0.23,  -0.23, 0.23,  -0.47, 0.00,  1.01, 1.47, 0.77,  1.24,  0.77,  1.24,  0.54,  1.01,  -0.50, -0.03, -0.74, -0.27, -0.74, -0.27, -0.97, -0.50, 0.50, 0.97, 0.27, 0.74, 0.27, 0.74, 0.03, 0.50,  -0.50, -0.03, -0.74, -0.27, -0.74, -0.27, -0.97, -0.50, 0.50,  0.97,  0.27,  0.74,  0.27,  0.74,  0.03,  0.50,  -1.01, -0.54, -1.24, -0.77, -1.24, -0.77, -1.47, -1.01, 0.00, 0.47,  -0.23, 0.23,  -0.23, 0.23,  -0.47, 0.00},
             {0.00, -1.01, 0.50,  -0.50, 0.50,  -0.50, 1.01,  0.00,  2.01, 1.01, 2.51,  1.51,  2.51,  1.51,  3.02,  2.01,  -1.01, -2.01, -0.50, -1.51, -0.50, -1.51, 0.00,  -1.01, 1.01, 0.00, 1.51, 0.50, 1.51, 0.50, 2.01, 1.01,  -1.01, -2.01, -0.50, -1.51, -0.50, -1.51, 0.00,  -1.01, 1.01,  0.00,  1.51,  0.50,  1.51,  0.50,  2.01,  1.01,  -2.01, -3.02, -1.51, -2.51, -1.51, -2.51, -1.01, -2.01, 0.00, -1.01, 0.50,  -0.50, 0.50,  -0.50, 1.01,  0.00},
             {0.00, 0.00,  0.41,  0.41,  -0.41, -0.41, 0.00,  0.00,  0.00, 0.00, 0.41,  0.41,  -0.41, -0.41, 0.00,  0.00,  0.87,  0.87,  1.28,  1.28,  0.46,  0.46,  0.87,  0.87,  0.87, 0.87, 1.28, 1.28, 0.46, 0.46, 0.87, 0.87,  -0.87, -0.87, -0.46, -0.46, -1.28, -1.28, -0.87, -0.87, -0.87, -0.87, -0.46, -0.46, -1.28, -1.28, -0.87, -0.87, 0.00,  0.00,  0.41,  0.41,  -0.41, -0.41, 0.00,  0.00,  0.00, 0.00,  0.41,  0.41,  -0.41, -0.41, 0.00,  0.00},
             {0.00, 0.00,  -0.87, -0.87, 0.87,  0.87,  0.00,  0.00,  0.00, 0.00, -0.87, -0.87, 0.87,  0.87,  0.00,  0.00,  1.74,  1.74,  0.87,  0.87,  2.61,  2.61,  1.74,  1.74,  1.74, 1.74, 0.87, 0.87, 2.61, 2.61, 1.74, 1.74,  -1.74, -1.74, -2.61, -2.61, -0.87, -0.87, -1.74, -1.74, -1.74, -1.74, -2.61, -2.61, -0.87, -0.87, -1.74, -1.74, 0.00,  0.00,  -0.87, -0.87, 0.87,  0.87,  0.00,  0.00,  0.00, 0.00,  -0.87, -0.87, 0.87,  0.87,  0.00,  0.00},
             {0.00, -0.24, -0.24, -0.48, -0.24, -0.48, -0.48, -0.72, 0.24, 0.00, 0.00,  -0.24, 0.00,  -0.24, -0.24, -0.48, 0.24,  0.00,  0.00,  -0.24, 0.00,  -0.24, -0.24, -0.48, 0.48, 0.24, 0.24, 0.00, 0.24, 0.00, 0.00, -0.24, 0.24,  0.00,  0.00,  -0.24, 0.00,  -0.24, -0.24, -0.48, 0.48,  0.24,  0.24,  0.00,  0.24,  0.00,  0.00,  -0.24, 0.48,  0.24,  0.24,  0.00,  0.24,  0.00,  0.00,  -0.24, 0.72, 0.48,  0.48,  0.24,  0.48,  0.24,  0.24,  0.00}};
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=U_SET

    ap_int_4 GATE[64][6] = {{0, 0, 0, 0, 0, 0},
                            {1, 0, 0, 0, 0, 0},
                            {0, 1, 0, 0, 0, 0},
                            {1, 1, 0, 0, 0, 0},
                            {0, 0, 1, 0, 0, 0},
                            {1, 0, 1, 0, 0, 0},
                            {0, 1, 1, 0, 0, 0},
                            {1, 1, 1, 0, 0, 0},
                            {0, 0, 0, 1, 0, 0},
                            {1, 0, 0, 1, 0, 0},
                            {0, 1, 0, 1, 0, 0},
                            {1, 1, 0, 1, 0, 0},
                            {0, 0, 1, 1, 0, 0},
                            {1, 0, 1, 1, 0, 0},
                            {0, 1, 1, 1, 0, 0},
                            {1, 1, 1, 1, 0, 0},
                            {0, 0, 0, 0, 1, 0},
                            {1, 0, 0, 0, 1, 0},
                            {0, 1, 0, 0, 1, 0},
                            {1, 1, 0, 0, 1, 0},
                            {0, 0, 1, 0, 1, 0},
                            {1, 0, 1, 0, 1, 0},
                            {0, 1, 1, 0, 1, 0},
                            {1, 1, 1, 0, 1, 0},
                            {0, 0, 0, 1, 1, 0},
                            {1, 0, 0, 1, 1, 0},
                            {0, 1, 0, 1, 1, 0},
                            {1, 1, 0, 1, 1, 0},
                            {0, 0, 1, 1, 1, 0},
                            {1, 0, 1, 1, 1, 0},
                            {0, 1, 1, 1, 1, 0},
                            {1, 1, 1, 1, 1, 0},
                            {0, 0, 0, 0, 0, 1},
                            {1, 0, 0, 0, 0, 1},
                            {0, 1, 0, 0, 0, 1},
                            {1, 1, 0, 0, 0, 1},
                            {0, 0, 1, 0, 0, 1},
                            {1, 0, 1, 0, 0, 1},
                            {0, 1, 1, 0, 0, 1},
                            {1, 1, 1, 0, 0, 1},
                            {0, 0, 0, 1, 0, 1},
                            {1, 0, 0, 1, 0, 1},
                            {0, 1, 0, 1, 0, 1},
                            {1, 1, 0, 1, 0, 1},
                            {0, 0, 1, 1, 0, 1},
                            {1, 0, 1, 1, 0, 1},
                            {0, 1, 1, 1, 0, 1},
                            {1, 1, 1, 1, 0, 1},
                            {0, 0, 0, 0, 1, 1},
                            {1, 0, 0, 0, 1, 1},
                            {0, 1, 0, 0, 1, 1},
                            {1, 1, 0, 0, 1, 1},
                            {0, 0, 1, 0, 1, 1},
                            {1, 0, 1, 0, 1, 1},
                            {0, 1, 1, 0, 1, 1},
                            {1, 1, 1, 0, 1, 1},
                            {0, 0, 0, 1, 1, 1},
                            {1, 0, 0, 1, 1, 1},
                            {0, 1, 0, 1, 1, 1},
                            {1, 1, 0, 1, 1, 1},
                            {0, 0, 1, 1, 1, 1},
                            {1, 0, 1, 1, 1, 1},
                            {0, 1, 1, 1, 1, 1},
                            {1, 1, 1, 1, 1, 1}};
#pragma HLS ARRAY_PARTITION dim=2 type=complete variable=GATE

//    APFIX_16_Qquad Qquad[5] = {1, Q_quad, 1, Q_quad, Q_quad};  // For i 1500 * 1500
//    APFIX_16_Qsw Qswitch[6] = {Q_switch, Q_switch, Q_switch, Q_switch, Q_switch, Q_switch};
//    APFIX_16_QswConst QswitchConst[6] = {Q_switchConst_IGBT, Q_switchConst_IGBT, Q_switchConst_IGBT, Q_switchConst_MOS,
//                                 Q_switchConst_MOS, Q_switchConst_MOS}; //For each 500
//    APFIX_16_Qcur Qcurrentlim[6] = {0, 0, 0, Q_currentlim, Q_currentlim, Q_currentlim}; // For each 1000

    float16_t CL = 10;


    SimplifyCal(Jmin, CalcNum, nextgate,
                index, location,
                J_current, prestate,
                xref, U_SET, GATE, x, v,
                Q_quad, Q_switch, Q_switchConst_IGBT, Q_switchConst_MOS,Q_currentlim, CL);

}
