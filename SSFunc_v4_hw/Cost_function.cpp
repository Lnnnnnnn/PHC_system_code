//
// Created by s1805689 on 30/09/2022.
//

#include "ap_header.h"


void Cost_function(float16_t xref[XNSIZE], float16_t xn_current[THREADNUM][XNSIZE], ap_int_4 laststate,float16_t Js[THREADNUM]) {
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=xn_current
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=Js

    float16_t xrefs[THREADNUM][XNSIZE];
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=xrefs
    ap_int_4 laststates[THREADNUM];
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=laststates
    float16_t currentstate[THREADNUM];
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=currentstate

    for (ap_int_4 i = 0; i < THREADNUM; ++i) {
#pragma HLS UNROLL
        xrefs[i][0] = xref[0];
        xrefs[i][1] = xref[1];
        xrefs[i][2] = xref[2];
        xrefs[i][3] = xref[3];
        xrefs[i][4] = xref[4];
        laststates[i] = laststate;


    }
    for (ap_int_4 i = 0; i < THREADNUM; ++i) {
#pragma HLS UNROLL
        currentstate[i] = i;
    }


    for (ap_int_4 i = 0; i < THREADNUM; ++i) {
#pragma HLS UNROLL
        Js[i] = JcalcValue(xrefs[i], xn_current[i], laststates[i], currentstate[i]);
    }


    for (ap_int_4 i = 0; i < THREADNUM; ++i) {

    }


}
