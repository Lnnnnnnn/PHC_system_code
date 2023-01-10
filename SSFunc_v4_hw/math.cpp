//
// Created by s1805689 on 24/05/2022.
//

#include "ap_header.h"


//void multimartix (float16_t a[N][P], float16_t b[P][M], float16_t out[N][M]){
//// function to multiple matrix
//    for (ap_int_4 i = 0; i < N; ++i) {
//        for (ap_int_ 4 j = 0; j < M; ++j) {
//            for (float16_t k = 0; k < P; ++k) {
//                out[i][j] += a[i][k] * b[k][j];
//            }
//        }
//    }
//};

void mulvector3x3(float16_h_t a[3][3], float16_t b[3], float16_t out[3]) {
    for (ap_int_4 i = 0; i < 3; ++i) {
#pragma HLS UNROLL
        for (ap_int_4 k = 0; k < 3; ++k) {
#pragma HLS UNROLL
            out[i] += a[i][k] * b[k];
        }
    }
};


void mulvector5x5(float16_h_t a[5][5], float16_t b[5], float16_t out[5]) {
    for (ap_int_4 i = 0; i < 5; ++i) {
#pragma HLS UNROLL
        for (ap_int_4 k = 0; k < 5; ++k) {
#pragma HLS UNROLL
            out[i] += a[i][k] * b[k];
        }
    }
};

void mulvector5x6(float16_h_t a[5][6], float16_t b[6], float16_t out[5]) {
    for (ap_int_4 i = 0; i < 5; ++i) {
#pragma HLS UNROLL
        for (ap_int_4 k = 0; k < 6; ++k) {
#pragma HLS UNROLL
            out[i] += a[i][k] * b[k];
        }
    }
};

void mulvector5x2(float16_h_t a[5][2], float16_t b[2], float16_t out[5]) {
    for (ap_int_4 i = 0; i < 5; ++i) {
#pragma HLS UNROLL
        for (ap_int_4 k = 0; k < 2; ++k) {
#pragma HLS UNROLL
            out[i] += a[i][k] * b[k];
        }
    }
};


//void mulvector2 (float16_t a[2][2], float16_t b[2][1], float16_t out[2][1]){
//    for (float16_t i = 0; i < 2; ++i) {
//        for (ap_int_ 4 j = 0; j < 1; ++j) {
//            for (ap_int_4 k = 0; k < 2; ++k) {
//                out[i][j] += a[i][k] * b[k][j];
//            }
//        }
//    }
//};

//void absFunc(float16_t *value){
//    if (*value < 0){
//        *value = - *value;
//    } else{
//        *value = *value;
//    }
//}

float16_t JcalcValue(float16_t xref[XNSIZE], float16_t xn_current[XNSIZE], ap_int_4 laststate, ap_int_4 currentstate) {

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

    float16_t current_state[UNSIZE];
    float16_t previous_state[UNSIZE];
    for (ap_int_4 i = 0; i < UNSIZE; ++i) {
        current_state[0] = GATE[currentstate][0];
        current_state[1] = GATE[currentstate][1];
        current_state[2] = GATE[currentstate][2];
        current_state[3] = GATE[currentstate][3];
        current_state[4] = GATE[currentstate][4];
        current_state[5] = GATE[currentstate][5];

        previous_state[0] = GATE[laststate][0];
        previous_state[1] = GATE[laststate][1];
        previous_state[2] = GATE[laststate][2];
        previous_state[3] = GATE[laststate][3];
        previous_state[4] = GATE[laststate][4];
        previous_state[5] = GATE[laststate][5];

    }


    float_sp Qq = 0;
    float_sp Qsw = 0; // for J current doest matter
    float_sp QswConst = 0;
    float_sp Qcur = 0;


    float16_h_t Qquad[5] = {0.1, 0, 0.1, 0, 0};  // For i 1500 * 1500
    float16_t Qswitch[6] = {0, 0, 0, 0, 0, 0};
    float16_t QswitchConst[6] = {976.5, 976.5, 976.5, 50, 50, 50}; //For each 500
    float16_t Qcurrentlim[6] = {0, 0, 0, 7470, 7470, 7470}; // For each 1000

    float16_t CL = 500;

//for (ap_int_4 i = 0; i < UNSIZE; ++i) {
//        cout << "xn_current abr:  " << xn_current[i] << endl;
//    }
//    cout << " ------ " << endl;
//
//    float16_h_t T_alphabeta_to_abc_1[3][3] = {
//            {0.8165,  -0.0000, 0.5774},
//            {-0.4082, 0.7071,  0.5774},
//            {-0.4082, -0.7071, 0.5774}};
//#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=T_alphabeta_to_abc_1
//#pragma HLS ARRAY_PARTITION dim=2 type=complete variable=T_alphabeta_to_abc_1


    float16_h_t T_alphabeta_to_abc_2[3][3] = {
            {0.8165,  -0.0000, 0.5774},
            {-0.4082, 0.7071,  0.5774},
            {-0.4082, -0.7071, 0.5774}};
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=T_alphabeta_to_abc_2
#pragma HLS ARRAY_PARTITION dim=2 type=complete variable=T_alphabeta_to_abc_2

//    float16_t xnGrid_abr[3] = {xn_current[0],xn_current[2],0};
//#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=xnGrid_abr

    float16_t xnHF_abr[3] = {xn_current[1],xn_current[3],xn_current[4]};
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=xnHF_abr
//
//    float16_t xnGrid_abc[3] = {0,0,0};
//#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=xnGrid_abc
    float16_t xnHF_abc[3] = {0,0,0};
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=xnHF_abc

//    cout << "xnHF_abc:  "<< xnGrid_abr[0] << endl;
//    cout << "xnHF_abc:  "<< xnGrid_abr[1] << endl;
//    cout << "xnHF_abc:  "<< xnGrid_abr[2] << endl;
//    cout << "xnHF_abr,:  "<< xnHF_abr[0] << endl;
//    cout << "xnHF_abr,:  "<< xnHF_abr[1] << endl;
//    cout << "xnHF_abr,:  "<< xnHF_abr[2] << endl;
//    cout << " ------ "  << endl;

//    mulvector3x3(T_alphabeta_to_abc_1,xnGrid_abr,xnGrid_abc);
    mulvector3x3(T_alphabeta_to_abc_2,xnHF_abr,xnHF_abc);

    float16_t xn_abc_current[3] = {xnHF_abc[0],xnHF_abc[1],xnHF_abc[2]};
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=xn_abc_current

//    for (ap_int_4 i = 0; i < UNSIZE; ++i) {
//        cout << "xn_abc_current abr:  " << xn_abc_current[i] << endl;
//    }
//    cout << " ------ " << endl;

//    for (ap_int_4 i = 0; i < XNSIZE; ++i) {
//#pragma HLS UNROLL
//        float16_t temp = xref[i] - xn_current[i];
//        Qq += Qquad[i] * temp * temp;
//    }
    float16_t temp_0 = xref[0] - xn_current[0];
    float16_t temp_2 = xref[2] - xn_current[2];
    Qq = temp_0 * temp_0 * Qquad[0] + temp_2 * temp_2 * Qquad[2];

loop_region:{
#pragma HLS LOOP_MERGE
    for (ap_int_4 i = 0; i < UNSIZE; ++i) {
#pragma HLS UNROLL
        if (previous_state[i] - current_state[i] >= 0) {
            Qsw += Qswitch[i] * (previous_state[i] - current_state[i]);
        } else {
            Qsw += Qswitch[i] * (-(previous_state[i] - current_state[i]));
        }
    }

    for (ap_int_4 i = 0; i < UNSIZE; ++i) {
#pragma HLS UNROLL
        if (previous_state[i] - current_state[i] >= 0) {
            QswConst += QswitchConst[i] * (previous_state[i] - current_state[i]);
        } else {
            QswConst += QswitchConst[i] * (-(previous_state[i] - current_state[i]));
        }
    }
//
//for (ap_int_4 i = 0; i < UNSIZE; ++i) {
//    cout << "xn_abc_current:  " << xn_abc_current[i] << endl;
//}
//    cout << " ------ " << endl;



    for (ap_int_4 i = 0; i < 3; ++i) {
#pragma HLS UNROLL
        if (xn_abc_current[i] >= 0) {
            Qcur += 7470 * (xn_abc_current[i] > CL);
        } else {
            Qcur += 7470 * ((-xn_abc_current[i]) > CL);
        }
    }
}

//    cout << "Qq:  " << Qq << endl;
//    cout << "Qsw:  "<< Qsw << endl;
//    cout << "QswConst:  "<< QswConst << endl;
//    cout << "Qcur:  "<< Qcur << endl;
//    cout << " ------ "  << endl;
//    float16_t Jcalc = Qq + Qsw + QswConst + Qcur;

    float_sp temp = Qq + Qsw + QswConst + Qcur;
    float16_t Jcalc;

    if (temp > 4000){
        Jcalc = 4000;
    } else{
        Jcalc = temp;
    }
//    cout << "Jcalc:  "<< Jcalc << endl;
    return Jcalc;
}

void statespace(float16_t xn_in[XNSIZE], float16_t xn_out[XNSIZE], float16_t u[XNSIZE], float16_t v[XNSIZE]) {

    float16_t Aterm[XNSIZE] = {0,0,0,0,0};
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=Aterm
    float16_t Bterm[XNSIZE] = {0,0,0,0,0};
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=Bterm
    float16_t Eterm[XNSIZE] = {0,0,0,0,0};
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=Eterm

//Aterm
    Aterm[0] = xn_in[0];
    Aterm[1] = xn_in[1];
    Aterm[2] = xn_in[2];
    Aterm[3] = xn_in[3];
    Aterm[4] = xn_in[4];

//Bterm
//    Bterm[0] = B[0][0] * u[0] + B[0][1] * u[1];
//    Bterm[1] = B[1][0] * u[0] + B[1][1] * u[1];
//    Bterm[2] = B[2][2] * u[2] + B[2][3] * u[3];
//    Bterm[3] = B[3][2] * u[2] + B[3][3] * u[3];
//    Bterm[4] = B[4][4] * u[4] + B[4][5] * u[5];

//Bterm
    Bterm[0] = u[0];
    Bterm[1] = u[1];
    Bterm[2] = u[2];
    Bterm[3] = u[3];
    Bterm[4] = u[4];

//Eterm
    Eterm[0] = v[0];
    Eterm[1] = v[1];
    Eterm[2] = v[2];
    Eterm[3] = v[3];
    Eterm[4] = v[4];

//    mulvector5x5(A, xn_current, Aterm);
//    mulvector5x6(B, u, Bterm);
//    mulvector5x2(E, v, Eterm);

//    cout << "Bterm " << Bterm[0] << endl;
//    cout << "Bterm " << Bterm[1] << endl;
//    cout << "Bterm " << Bterm[2] << endl;
//    cout << "Bterm " << Bterm[3] << endl;
//    cout << "Bterm " << Bterm[4] << endl;
//    cout << " ------ "  << endl;


    for (ap_int_4 i = 0; i < XNSIZE; ++i) {
#pragma HLS UNROLL
        xn_out[i] = Aterm[i] + Bterm[i] + Eterm[i];
    }

}
