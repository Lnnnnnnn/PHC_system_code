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
        for (ap_int_4 k = 0; k < 3; ++k) {
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
float_sp JcalcValue(float16_t xref[XNSIZE], float16_t xn_current[XNSIZE], APFIX_16_Qquad Qquad,
                    APFIX_16_Qsw Qswitch, bool previous_state[UNSIZE], bool current_state[UNSIZE],
                    APFIX_16_Qcur Qcurrentlim, APFIX_16_QswConst_IGBT QswitchConst_IGBT, APFIX_16_QswConst_MOS QswitchConst_MOS, float16_t CL) {

    APFIX_32_Qq Qq = 0;
    APFIX_32_Qsw Qsw = 0; // for J current doest matter
    APFIX_32_QswConst QswConst = 0;
    APFIX_32_Qcur Qcur = 0;


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
            {0.816496581, 0,            0.577350269},
            {-0.40824829, 0.707106781,  0.577350269},
            {-0.40824829, -0.707106781, 0.577350269}};

//#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=T_alphabeta_to_abc_2
//#pragma HLS ARRAY_PARTITION dim=2 type=complete variable=T_alphabeta_to_abc_2

//    float16_t xnGrid_abr[3] = {xn_current[0],xn_current[2],0};
//#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=xnGrid_abr

    float16_t xnHF_abr[3] = {xn_current[1], xn_current[3], xn_current[4]};
//#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=xnHF_abr
//
//    float16_t xnGrid_abc[3] = {0,0,0};
//#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=xnGrid_abc
    float16_t xnHF_abc[3] = {0, 0, 0};
//#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=xnHF_abc

//    cout << "xnHF_abc:  "<< xnGrid_abr[0] << endl;
//    cout << "xnHF_abc:  "<< xnGrid_abr[1] << endl;
//    cout << "xnHF_abc:  "<< xnGrid_abr[2] << endl;
//    cout << "xnHF_abr,:  "<< xnHF_abr[0] << endl;
//    cout << "xnHF_abr,:  "<< xnHF_abr[1] << endl;
//    cout << "xnHF_abr,:  "<< xnHF_abr[2] << endl;
//    cout << " ------ "  << endl;

//    mulvector3x3(T_alphabeta_to_abc_1,xnGrid_abr,xnGrid_abc);
    mulvector3x3(T_alphabeta_to_abc_2, xnHF_abr, xnHF_abc);

    float16_t xn_abc_current[3] = {xnHF_abc[0], xnHF_abc[1], xnHF_abc[2]};
//#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=xn_abc_current

//    for (ap_int_4 i = 0; i < UNSIZE; ++i) {
//        cout << "xn_abc_current abr:  " << xn_abc_current[i] << endl;
//    }
//    cout << " ------ " << endl;

//    for (ap_int_4 i = 0; i < XNSIZE; ++i) {
//#pragma HLS UNROLL
//        float16_t temp = xref[i] - xn_current[i];
//        Qq += Qquad[i] * temp * temp;
//    }
    APFIX_32_Qq temp_0 = xref[0] - xn_current[0];
    APFIX_32_Qq temp_1 = xref[1] - xn_current[1];
    APFIX_32_Qq temp_2 = xref[2] - xn_current[2];
    APFIX_32_Qq temp_3 = xref[3] - xn_current[3];
    APFIX_32_Qq temp_4 = xref[4] - xn_current[4];

//    float16_t temp_0 = xref[0] - xn_current[0];
//    float16_t temp_2 = xref[2] - xn_current[2];
//
//    Qq = temp_0 * temp_0 * Qquad[0] + temp_2 * temp_2 * Qquad[2];

//    cout << "temp_0:  "<< temp_0 << endl;
//    cout << "temp_0:  " << temp_1 << endl;
//    cout << "temp_0:  "<< temp_2 << endl;
//    cout << "temp_0:  "<< temp_3 << endl;
//    cout << "temp_0:  "<< temp_4 << endl;
//    cout << " ------ "  << endl;

//    for (int i = 0; i < 5; ++i) {
//        cout << "Qquad:  "<< Qquad[i] << endl;
//    }

//    Qq = temp_0 * temp_0 * Qquad[0] + temp_1 * temp_1 * Qquad[1]+ temp_2 * temp_2 * Qquad[2]+ temp_3 * temp_3 * Qquad[3]+ temp_4 * temp_4 * Qquad[4];
// 64 52 + 64 52 65 52
    Qq = (temp_0 * temp_0 + temp_2 * temp_2) + (temp_1 * temp_1 + temp_3 * temp_3 + temp_4 * temp_4)  * Qquad;

//    cout << "temp_0:  "<< Qq << endl;
//    cout << " ------ "  << endl;
//        for (ap_int_4 i = 0; i < UNSIZE; ++i) {
////#pragma HLS UNROLL
//            if (previous_state[i] - current_state[i] >= 0) {
//                Qsw += Qswitch[i] * (previous_state[i] - current_state[i]);
//            } else {
//                Qsw += Qswitch[i] * (-(previous_state[i] - current_state[i]));
//            }
//        }

//        for (ap_int_4 i = 0; i < UNSIZE; ++i) {
////#pragma HLS UNROLL
//            if (previous_state[i] - current_state[i] >= 0) {
//                QswConst += QswitchConst[i] * (previous_state[i] - current_state[i]);
//            } else {
//                QswConst += QswitchConst[i] * (-(previous_state[i] - current_state[i]));
//            }
//        }

//    for (int i = 0; i < 6; ++i) {
////        cout << prestate[i] << endl;
//        cout << previous_state[i] << endl;
////        cout << current_state[i] << endl;
//}

    for (ap_int_4 i = 0; i < 3; ++i) {
        if (previous_state[i] != current_state[i]) {
            QswConst = QswConst + QswitchConst_IGBT;
        }
    }

    for (ap_int_4 i = 3; i < 6; ++i) {
        if (previous_state[i] != current_state[i]) {
            QswConst = QswConst + QswitchConst_MOS;
        }
    }

//for (ap_int_4 i = 0; i < UNSIZE; ++i) {
//    cout << "xn_abc_current:  " << xn_abc_current[i] << endl;
//}
//    cout << " ------ " << endl;

    float16_t xn_abc_current_pos[3] = {0, 0, 0};

    for (ap_int_4 i = 0; i < 3; ++i) {
#pragma HLS UNROLL
        xn_abc_current_pos[i] = xn_abc_current[i];
//        xn_abc_current_pos[i] = abs(xn_abc_current[i]);
    }

    APFIX_32_Qcur temp_cl = Qcurrentlim;


//#pragma HLS UNROLL
    for (ap_int_4 i = 0; i < 3; ++i) {
#pragma HLS PIPELINE
//#pragma HLS UNROLL
        if (xn_abc_current_pos[i] > CL) {
            Qcur = Qcur + 800000;
        }
        if (xn_abc_current_pos[i] < -CL) {
            Qcur = Qcur + 800000;
        }
    }


//    cout << "Qq:  " << Qq << endl;
//    cout << "Qsw:  "<< Qsw << endl;
//    cout << "QswConst:  "<< QswConst << endl;
//    cout << "Qcur:  "<< Qcur << endl;
//    cout << " ------ "  << endl;
//    float16_t Jcalc = Qq + Qsw + QswConst + Qcur;

    float_sp Jcalc = Qq + Qsw + QswConst + Qcur;
//    float_sp Jcalc;

//    if (temp > 4000){
//        Jcalc = 4000;
//    } else{
//    Jcalc = temp;
//    }
//    cout << "Jcalc:  "<< Jcalc << endl;
    return Jcalc;
}

void statespace(float16_t xn_current[XNSIZE], float16_t u[XNSIZE], float16_t v[XNSIZE]) {

    float16_t Aterm[XNSIZE] = {0, 0, 0, 0, 0};
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=Aterm
    float16_t Bterm[XNSIZE] = {0, 0, 0, 0, 0};
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=Bterm
    float16_t Eterm[XNSIZE] = {0, 0, 0, 0, 0};
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=Eterm

//Aterm
    Aterm[0] = xn_current[0];
    Aterm[1] = xn_current[1];
    Aterm[2] = xn_current[2];
    Aterm[3] = xn_current[3];
    Aterm[4] = xn_current[4];

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
        xn_current[i] = Aterm[i] + Bterm[i] + Eterm[i];
    }

}
