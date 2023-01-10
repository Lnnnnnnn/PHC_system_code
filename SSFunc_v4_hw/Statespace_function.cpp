//
// Created by s1805689 on 30/09/2022.
//
#include "ap_header.h"

void Statespace_function(float16_t x_in[XNSIZE], float16_t x_out[XNSIZE], float16_t v[VNSIZE], ap_int_4 y) {
#pragma HLS INTERFACE mode=ap_ctrl_none port=return
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=v
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=x_in
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=x_out


    static float16_h_t E[5][2] = {{-0.0181, 0},
                                  {-0.0123, 0},
                                  {0,       -0.0181},
                                  {0,       -0.0123},
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

    float16_t vs[XNSIZE];
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=vs

    vs[0] = v_temp[0];
    vs[1] = v_temp[1];
    vs[2] = v_temp[2];
    vs[3] = v_temp[3];
    vs[4] = v_temp[4];

    static float16_t U_SET[5][64] =
            {{0.00, 0.47,  -0.23, 0.23,  -0.23, 0.23,  -0.47, 0.00,  1.01, 1.47, 0.77,  1.24,  0.77,  1.24,  0.54,  1.01,  -0.50, -0.03, -0.74, -0.27, -0.74, -0.27, -0.97, -0.50, 0.50, 0.97, 0.27, 0.74, 0.27, 0.74, 0.03, 0.50,  -0.50, -0.03, -0.74, -0.27, -0.74, -0.27, -0.97, -0.50, 0.50,  0.97,  0.27,  0.74,  0.27,  0.74,  0.03,  0.50,  -1.01, -0.54, -1.24, -0.77, -1.24, -0.77, -1.47, -1.01, 0.00, 0.47,  -0.23, 0.23,  -0.23, 0.23,  -0.47, 0.00},
             {0.00, -1.01, 0.50,  -0.50, 0.50,  -0.50, 1.01,  0.00,  2.01, 1.01, 2.51,  1.51,  2.51,  1.51,  3.02,  2.01,  -1.01, -2.01, -0.50, -1.51, -0.50, -1.51, 0.00,  -1.01, 1.01, 0.00, 1.51, 0.50, 1.51, 0.50, 2.01, 1.01,  -1.01, -2.01, -0.50, -1.51, -0.50, -1.51, 0.00,  -1.01, 1.01,  0.00,  1.51,  0.50,  1.51,  0.50,  2.01,  1.01,  -2.01, -3.02, -1.51, -2.51, -1.51, -2.51, -1.01, -2.01, 0.00, -1.01, 0.50,  -0.50, 0.50,  -0.50, 1.01,  0.00},
             {0.00, 0.00,  0.41,  0.41,  -0.41, -0.41, 0.00,  0.00,  0.00, 0.00, 0.41,  0.41,  -0.41, -0.41, 0.00,  0.00,  0.87,  0.87,  1.28,  1.28,  0.46,  0.46,  0.87,  0.87,  0.87, 0.87, 1.28, 1.28, 0.46, 0.46, 0.87, 0.87,  -0.87, -0.87, -0.46, -0.46, -1.28, -1.28, -0.87, -0.87, -0.87, -0.87, -0.46, -0.46, -1.28, -1.28, -0.87, -0.87, 0.00,  0.00,  0.41,  0.41,  -0.41, -0.41, 0.00,  0.00,  0.00, 0.00,  0.41,  0.41,  -0.41, -0.41, 0.00,  0.00},
             {0.00, 0.00,  -0.87, -0.87, 0.87,  0.87,  0.00,  0.00,  0.00, 0.00, -0.87, -0.87, 0.87,  0.87,  0.00,  0.00,  1.74,  1.74,  0.87,  0.87,  2.61,  2.61,  1.74,  1.74,  1.74, 1.74, 0.87, 0.87, 2.61, 2.61, 1.74, 1.74,  -1.74, -1.74, -2.61, -2.61, -0.87, -0.87, -1.74, -1.74, -1.74, -1.74, -2.61, -2.61, -0.87, -0.87, -1.74, -1.74, 0.00,  0.00,  -0.87, -0.87, 0.87,  0.87,  0.00,  0.00,  0.00, 0.00,  -0.87, -0.87, 0.87,  0.87,  0.00,  0.00},
             {0.00, -0.24, -0.24, -0.48, -0.24, -0.48, -0.48, -0.72, 0.24, 0.00, 0.00,  -0.24, 0.00,  -0.24, -0.24, -0.48, 0.24,  0.00,  0.00,  -0.24, 0.00,  -0.24, -0.24, -0.48, 0.48, 0.24, 0.24, 0.00, 0.24, 0.00, 0.00, -0.24, 0.24,  0.00,  0.00,  -0.24, 0.00,  -0.24, -0.24, -0.48, 0.48,  0.24,  0.24,  0.00,  0.24,  0.00,  0.00,  -0.24, 0.48,  0.24,  0.24,  0.00,  0.24,  0.00,  0.00,  -0.24, 0.72, 0.48,  0.48,  0.24,  0.48,  0.24,  0.24,  0.00}};
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=U_SET
    float16_t us[XNSIZE];
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=us
#pragma HLS ARRAY_PARTITION dim=2 type=complete variable=us

    us[0] = U_SET[0][y];
    us[1] = U_SET[1][y];
    us[2] = U_SET[2][y];
    us[3] = U_SET[3][y];
    us[4] = U_SET[4][y];


    statespace(x_in, x_out, us, vs);

}

