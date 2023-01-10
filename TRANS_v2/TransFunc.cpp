//
// Created by s1805689 on 28/10/2022.
//

#include "ap_header.h"

void T_abc_to_alphabeta(float16_t in[3], float16_t out[3]) {
//#pragma HLS INTERFACE mode=ap_ctrl_none port=return

#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=out
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=in

    float16_t temp[3] = {0,0,0};
#pragma HLS ARRAY_PARTITION dim=2 type=complete variable=temp

    float16_h_t T_abc_to_alphabeta[3][3] =
            {{0.8165, -0.4082, -0.4082},
             {0.0000, 0.7071,  -0.7071},
             {0.5774, 0.5774,  0.5774}};
#pragma HLS ARRAY_PARTITION dim=2 type=complete variable=T_abc_to_alphabeta
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=T_abc_to_alphabeta

    for (ap_int_4 i = 0; i < 3; ++i) {
#pragma HLS UNROLL
        for (ap_int_4 k = 0; k < 3; ++k) {
            temp[i] += T_abc_to_alphabeta[i][k] * in[k];
        }
        out[i] = temp[i];
    }
};
