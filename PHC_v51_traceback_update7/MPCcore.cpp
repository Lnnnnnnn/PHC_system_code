//
// Created by s1805689 on 24/05/2022.
// v50:
// 1.update the IGBT and MOS count value, they can be reset by CountReset setting to 1.
// 2.update the Q_quad to free range value
//

#include "ap_header.h"

void MPCcore(ap_int_4 *y, float_sp *J, float16_t &Calc,
             float16_t xref[5], float16_t x[5], bool gateT[6],
             float16_t v[2], bool p_state[6], float16_t x_pdic[5],
             APFIX_16_Qquad Q_quad, APFIX_16_Qsw Q_switch, APFIX_16_QswConst_IGBT Q_switchConst_IGBT, APFIX_16_QswConst_MOS Q_switchConst_MOS,
             APFIX_16_Qcur Q_currentlim) {
#pragma HLS INTERFACE mode=ap_ctrl_none port=return
//
//    cout << Q_quad << endl;
//    cout << Q_switchConst_IGBT << endl;
//    cout << Q_switchConst_MOS << endl;
//
//    for (int i = 0; i < 5; ++i) {
//        cout << xref[i] << endl;
//    }
//
//    for (int i = 0; i < 5; ++i) {
//        cout << x[i] << endl;
//    }
//
//    for (int i = 0; i < 2; ++i) {
//        cout << v[i] << endl;
//    }

#pragma HLS INTERFACE port=Calc register
#pragma HLS INTERFACE port=J register
#pragma HLS INTERFACE port=y register
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=v
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=x

#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=x_pdic
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=xref
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=p_state
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=gateT

    float16_t xrefs[THREADNUM][XNSIZE];
#pragma HLS ARRAY_PARTITION dim=2 type=complete variable=xrefs
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=xrefs
    for (ap_int_4 i = 0; i < THREADNUM; ++i) {
#pragma HLS UNROLL
        for (ap_int_4 j = 0; j < XNSIZE; ++j) {
#pragma HLS UNROLL
            xrefs[i][j] = xref[j];
        }
    }

    float16_t xs[THREADNUM][XNSIZE];
#pragma HLS ARRAY_PARTITION dim=2 type=complete variable=xs
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=xs
    for (ap_int_4 i = 0; i < THREADNUM; ++i) {
#pragma HLS UNROLL
        for (ap_int_4 j = 0; j < XNSIZE; ++j) {
#pragma HLS UNROLL
            xs[i][j] = x[j];
        }
    }

    float16_t vs[THREADNUM][VNSIZE];
#pragma HLS ARRAY_PARTITION dim=2 type=complete variable=vs
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=vs
    for (ap_int_4 i = 0; i < THREADNUM; ++i) {
#pragma HLS UNROLL
        for (ap_int_4 j = 0; j < VNSIZE; ++j) {
#pragma HLS UNROLL
            vs[i][j] = v[j];
        }
    }

    bool prestates[THREADNUM][UNSIZE];
#pragma HLS ARRAY_PARTITION dim=2 type=complete variable=prestates
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=prestates
    for (ap_int_4 i = 0; i < THREADNUM; ++i) {
#pragma HLS UNROLL
        for (ap_int_4 j = 0; j < UNSIZE; ++j) {
#pragma HLS UNROLL
            prestates[i][j] = p_state[j];
        }
    }


    float_sp Jmins[THREADNUM];
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=Jmins
    for (ap_int_4 i = 0; i < THREADNUM; ++i) {
#pragma HLS UNROLL
        Jmins[i] = 8000000;
    }

//    cout << "Jmins " << Jmins[0] << " " << Jmins[3] << endl;

    float16_t CalcNums[THREADNUM];
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=CalcNums
    for (ap_int_4 i = 0; i < THREADNUM; ++i) {
#pragma HLS UNROLL
        CalcNums[i] = 0;
    }
    ap_int_4 nextgates[THREADNUM];
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=nextgates
    for (ap_int_4 i = 0; i < THREADNUM; ++i) {
#pragma HLS UNROLL
        nextgates[i] = 0;
    }


    ap_int_4 indexsInLevel1[THREADNUM]; // all index begin from worker
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=indexsInLevel1
    for (ap_int_4 i = 0; i < THREADNUM; ++i) {
#pragma HLS UNROLL
        indexsInLevel1[i] = 0;
    }

    ap_int_4 indexsInLevel2[THREADNUM]; // all index begin from worker
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=indexsInLevel2
    for (ap_int_4 i = 0; i < THREADNUM; ++i) {
#pragma HLS UNROLL
        indexsInLevel2[i] = 1;
    }


    ap_int_4 locationsInLevel1[THREADNUM][HORIZON] = {{0,  0},
                                                      {1,  0},
                                                      {2,  0},
                                                      {3,  0},
                                                      {4,  0},
                                                      {5,  0},
                                                      {6,  0},
                                                      {7,  0},
                                                      {8,  0},
                                                      {9,  0},
                                                      {10, 0},
                                                      {11, 0},
                                                      {12, 0},
                                                      {13, 0},
                                                      {14, 0},
                                                      {15, 0},
                                                      {16, 0},
                                                      {17, 0},
                                                      {18, 0},
                                                      {19, 0},
                                                      {20, 0},
                                                      {21, 0},
                                                      {22, 0},
                                                      {23, 0},
                                                      {24, 0},
                                                      {25, 0},
                                                      {26, 0},
                                                      {27, 0},
                                                      {28, 0},
                                                      {29, 0},
                                                      {30, 0},
                                                      {31, 0},
                                                      {32, 0},
                                                      {33, 0},
                                                      {34, 0},
                                                      {35, 0},
                                                      {36, 0},
                                                      {37, 0},
                                                      {38, 0},
                                                      {39, 0},
                                                      {40, 0},
                                                      {41, 0},
                                                      {42, 0},
                                                      {43, 0},
                                                      {44, 0},
                                                      {45, 0},
                                                      {46, 0},
                                                      {47, 0},
                                                      {48, 0},
                                                      {49, 0},
                                                      {50, 0},
                                                      {51, 0},
                                                      {52, 0},
                                                      {53, 0},
                                                      {54, 0},
                                                      {55, 0},
                                                      {56, 0},
                                                      {57, 0},
                                                      {58, 0},
                                                      {59, 0},
                                                      {60, 0},
                                                      {61, 0},
                                                      {62, 0},
                                                      {63, 0}};

#pragma HLS ARRAY_PARTITION dim=2 type=complete variable=locationsInLevel1
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=locationsInLevel1

    ap_int_4 locationsInLevel2[THREADNUM][HORIZON] = {{0,  0},
                                                      {1,  0},
                                                      {2,  0},
                                                      {3,  0},
                                                      {4,  0},
                                                      {5,  0},
                                                      {6,  0},
                                                      {7,  0},
                                                      {8,  0},
                                                      {9,  0},
                                                      {10, 0},
                                                      {11, 0},
                                                      {12, 0},
                                                      {13, 0},
                                                      {14, 0},
                                                      {15, 0},
                                                      {16, 0},
                                                      {17, 0},
                                                      {18, 0},
                                                      {19, 0},
                                                      {20, 0},
                                                      {21, 0},
                                                      {22, 0},
                                                      {23, 0},
                                                      {24, 0},
                                                      {25, 0},
                                                      {26, 0},
                                                      {27, 0},
                                                      {28, 0},
                                                      {29, 0},
                                                      {30, 0},
                                                      {31, 0},
                                                      {32, 0},
                                                      {33, 0},
                                                      {34, 0},
                                                      {35, 0},
                                                      {36, 0},
                                                      {37, 0},
                                                      {38, 0},
                                                      {39, 0},
                                                      {40, 0},
                                                      {41, 0},
                                                      {42, 0},
                                                      {43, 0},
                                                      {44, 0},
                                                      {45, 0},
                                                      {46, 0},
                                                      {47, 0},
                                                      {48, 0},
                                                      {49, 0},
                                                      {50, 0},
                                                      {51, 0},
                                                      {52, 0},
                                                      {53, 0},
                                                      {54, 0},
                                                      {55, 0},
                                                      {56, 0},
                                                      {57, 0},
                                                      {58, 0},
                                                      {59, 0},
                                                      {60, 0},
                                                      {61, 0},
                                                      {62, 0},
                                                      {63, 0}};

#pragma HLS ARRAY_PARTITION dim=2 type=complete variable=locationsInLevel2
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=locationsInLevel2


    float_sp J_currents[THREADNUM];
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=J_currents
    for (ap_int_4 i = 0; i < THREADNUM; ++i) {
#pragma HLS UNROLL
        J_currents[i] = 0;
    }

    float16_h_t E[5][2] = {{-0.01806188, 0},
                           {-0.012314701, 0},
                           {0,       -0.01806188},
                           {0,       -0.01231470},
                           {0,       0}};
#pragma HLS ARRAY_PARTITION dim=2 type=complete variable=E
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=E

    float16_t v_temp[XNSIZE];
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=v_temp
    v_temp[0] = E[0][0] * v[0];
    v_temp[1] = E[1][0] * v[0];
    v_temp[2] = E[2][1] * v[1];
    v_temp[3] = E[3][1] * v[1];
    v_temp[4] = 0;

    float16_t V_SETs[THREADNUM][XNSIZE];
#pragma HLS ARRAY_PARTITION dim=2 type=complete variable=V_SETs
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=V_SETs
    for (ap_int_4 i = 0; i < THREADNUM; ++i) {
#pragma HLS UNROLL
        V_SETs[i][0] = v_temp[0];
        V_SETs[i][1] = v_temp[1];
        V_SETs[i][2] = v_temp[2];
        V_SETs[i][3] = v_temp[3];
        V_SETs[i][4] = v_temp[4];
    }


//    ap_int_4 assignmentLists_1[THREADNUM] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
//                                             11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21,
//                                             22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32,
//                                             33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43,
//                                             44, 45, 46, 47, 49, 50, 51, 52, 53, 54, 55,
//                                             56, 57, 58, 59, 60, 61, 62, 63};

    bool GATE[64][6] = {{0, 0, 0, 0, 0, 0},
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


    APFIX_16_Qquad Q_quads[THREADNUM];
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=J_currents
    for (ap_int_4 i = 0; i < THREADNUM; ++i) {
#pragma HLS UNROLL
        Q_quads[i] = Q_quad;
    }

    APFIX_16_Qsw Q_switchs[THREADNUM];
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=J_currents
    for (ap_int_4 i = 0; i < THREADNUM; ++i) {
#pragma HLS UNROLL
        Q_switchs[i] = Q_switch;
    }

    APFIX_16_QswConst_IGBT Q_switchConst_IGBTs[THREADNUM];
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=J_currents
    for (ap_int_4 i = 0; i < THREADNUM; ++i) {
#pragma HLS UNROLL
        Q_switchConst_IGBTs[i] = Q_switchConst_IGBT;
    }

    APFIX_16_QswConst_MOS Q_switchConst_MOSs[THREADNUM];
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=J_currents
    for (ap_int_4 i = 0; i < THREADNUM; ++i) {
#pragma HLS UNROLL
        Q_switchConst_MOSs[i] = Q_switchConst_MOS;
    }

    APFIX_16_Qcur Q_currentlims[THREADNUM];
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=J_currents
    for (ap_int_4 i = 0; i < THREADNUM; ++i) {
#pragma HLS UNROLL
        Q_currentlims[i] = Q_currentlim;
    }


    float_sp minValue = 8000000;
//    cout << "minValue " << minValue << endl;

    ap_int_4 minIndex = 0;

    // begin the while loop
    ap_int_4 round = 0;

    for (ap_int_4 i = 0; i < THREADNUM; ++i) {
#pragma HLS UNROLL
        MPCthread(&Jmins[i], &CalcNums[i], &nextgates[i],
                  &indexsInLevel1[i], locationsInLevel1[i],
                  &J_currents[i], xrefs[i], xs[i], V_SETs[i],
                  prestates[i],
                  Q_quads[i], Q_switchs[i], Q_switchConst_IGBTs[i], Q_switchConst_MOSs[i], Q_currentlims[i]);
    }

    MPCcore_MainWhile:
    while (round < GATESIZE) {
#pragma HLS PIPELINE rewind
//        if (round > 100) {
//            break;
//        }
//
//        for (ap_int_4 i = 0; i < THREADNUM; ++i) {
//            cout << "worker" << i << " location " << locationsInLevel2[i][0] << " "
//                 << locationsInLevel2[i][1] << " xn_current " << xn_currents[i][0] << " " << xn_currents[i][1] << " J "
//                 << J_currents[i] << " jmins " << Jmins[i] << " nextgates " << nextgates[i] << " helpedLists "
//                 << endl;
//        }
//        cout << "-----round-----" << endl;

        round += 1;

        for (ap_int_4 i = 0; i < THREADNUM; ++i) {
#pragma HLS UNROLL
            MPCthread(&Jmins[i], &CalcNums[i], &nextgates[i],
                      &indexsInLevel2[i], locationsInLevel2[i],
                      &J_currents[i], xrefs[i], xs[i], V_SETs[i],
                      prestates[i],
                      Q_quads[i], Q_switchs[i], Q_switchConst_IGBTs[i], Q_switchConst_MOSs[i], Q_currentlims[i]);
        }
} // end while loop

//// ------------- for some update --------------------
//        if ((round == 24) || (round == 88) || (round == 152) || (round == 232)||
//            (round == 48) || (round == 112) || (round == 176) || (round == 240)){
//            // find the minimum value
//            MPCcore_globalUpdateFindMin:
//            for (ap_int_4 i = 0; i < THREADNUM; ++i) {
//#pragma HLS PIPELINE rewind
//                if (Jmins[i] < minValue) {
//                    minValue = Jmins[i];
//                    minIndex = i;
//                }
//            }
////        cout << "Jmin value " << minValue << endl;
//            // set the minimum value for all Jmin
//            MPCcore_globalUpdateWriteMin:
//            for (ap_int_4 i = 0; i < THREADNUM; ++i) {
//#pragma HLS UNROLL
//                Jmins[i] = minValue;
//                nextgates[i] = nextgates[minIndex];
//            }
//        } else {
//            *y = nextgates[minIndex];
//        }
//// ------------- end for some update --------------------


//// ------------- for all update --------------------
//        for (ap_int_4 i = 0; i < THREADNUM; ++i) {
//            if (Jmins[i] < minValue) {
//                minValue = Jmins[i];
//                minIndex = i;
//            }
//        }
////        cout << "Jmin value " << minValue << endl;
//        // set the minimum value for all Jmin
//        for (ap_int_4 i = 0; i < THREADNUM; ++i) {
//#pragma HLS UNROLL
//            Jmins[i] = minValue;
//            nextgates[i] = nextgates[minIndex];
//        }
//// ------------- end for all update --------------------




//// ------------- for final update --------------------
    for (ap_int_4 i = 0; i < THREADNUM; ++i) {
        if (Jmins[i] < minValue) {
            minValue = Jmins[i];
            minIndex = i;
        }
    }
//        cout << "Jmin value " << minValue << endl;
    // set the minimum value for all Jmin
    for (ap_int_4 i = 0; i < THREADNUM; ++i) {
#pragma HLS UNROLL
        Jmins[i] = minValue;
        nextgates[i] = nextgates[minIndex];
    }
//// ------------- end for final update --------------------




//    for (ap_int_4 i = 0; i < THREADNUM; ++i) {
//        cout << "cal" << i << " : " << CalcNums[i] << endl;
//    };

    // set the final output value

    *y = nextgates[minIndex];
    *J = Jmins[0];
    Calc = CalcNums[0] + CalcNums[1] + CalcNums[2] + CalcNums[3] + CalcNums[4] + CalcNums[5] +
            CalcNums[6] + CalcNums[7] + CalcNums[8] + CalcNums[9] + CalcNums[10] + CalcNums[11] +
            CalcNums[12] + CalcNums[13] + CalcNums[14] + CalcNums[15] + CalcNums[16] + CalcNums[17] +
            CalcNums[18] + CalcNums[19] + CalcNums[20] + CalcNums[21] +
            CalcNums[22] + CalcNums[23] + CalcNums[24] + CalcNums[25] + CalcNums[26] + CalcNums[27] +
            CalcNums[28] + CalcNums[29] + CalcNums[30] + CalcNums[31];



    x_pdic[0] = xs[minIndex][0];
    x_pdic[1] = xs[minIndex][1];
    x_pdic[2] = xs[minIndex][2];
    x_pdic[3] = xs[minIndex][3];
    x_pdic[4] = xs[minIndex][4];


    gateT[0] = GATE[minIndex][0];
    gateT[1] = GATE[minIndex][1];
    gateT[2] = GATE[minIndex][2];
    gateT[3] = GATE[minIndex][3];
    gateT[4] = GATE[minIndex][4];
    gateT[5] = GATE[minIndex][5];


}

