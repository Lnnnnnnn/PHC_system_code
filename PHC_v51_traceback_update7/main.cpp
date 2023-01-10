#include "ap_header.h"
#include <fstream>
#include <ctime>
#include <sstream>
#include <ap_int.h>

void single_mpctest() {
//    time_t curr_time;
//    struct tm * curr_tm;
//
//    time(&curr_time);
//    curr_tm = localtime(&curr_time);
//
//    char name[256];
//    ofstream ofs;
//    ofstream result;
//
//    sprintf(name, "..\\Savedata\\data %d.%d %d-%d-%d.txt",curr_tm->tm_mon,curr_tm->tm_mday,curr_tm->tm_hour,curr_tm->tm_min,curr_tm->tm_sec);
//    ofs.open(name,ios::out);

//    float16_t xref[5] = {-1684.53 ,	0.00 ,	-1223.88 	,0.00 ,	0.00};
//    float16_t v[2] = {-558.22 ,	1405.57};
//    float16_t x[5] = {-1709.90 ,	215.78 ,	-1244.76 ,	238.07 ,	-142.29};
//    float16_t prestate[6] = {0 ,	0 ,	1 	,0 ,	0 ,	1};

//    float16_t xref[5] = {10.10351216, 0, -31.09541305, 0, 0};
//    float16_t v[2] = {17.76847718, -54.68574969};
//    float16_t x[5] = {10.32639512, -2.222217164, -23.64241702, -13.79899832, -1.682817095};
//    bool p_state[6] = {1, 1, 1, 1, 0, 1};

    float16_t xref[5] = {7.23254286, 0, -31.88567068, 0, 0};
    float16_t v[2] = {12.71946534, -56.07553122};
    float16_t x[5] = {6.930769685, -2.500030409, -17.10623043, -12.79162832, -0.950573168};
    bool p_state[6] = {1, 0, 1, 0, 0, 1};

//    float16_t xref[5] = {7.21875, 0, -31.875, 0, 0};
//    float16_t v[2] = {12.625, -56};
//    float16_t x[5] = {6.92188, -2.5, -17.0938, -12.7813, -0.9375};
//    bool p_state[6] = {1, 0, 1, 0, 0, 1};


    float16_t x_pdc[5] = {0, 0, 0, 0, 0};

    ap_int_4 y = -1;
    float_sp J = -1;
    float16_t Calc = -1;

    float_sp IGBTcount = 0;
    float_sp MOScount = 0;
    bool CountReset = 0;

    APFIX_16_Qquad Q_quad = 0.0617;
    APFIX_16_Qsw Q_switch = 0;
    APFIX_16_QswConst_IGBT Q_switchConst_IGBT = 0;
    APFIX_16_QswConst_MOS Q_switchConst_MOS = 0;
    APFIX_16_Qcur Q_currentlim = 8000;

    bool gateT[6];

    MPCcore(&y, &J, Calc, xref, x, gateT, v, p_state, x_pdc, Q_quad, Q_switch,
            Q_switchConst_IGBT,
            Q_switchConst_MOS, Q_currentlim);

    cout << "Y: " << y << endl;
    cout << "j: " << J << endl;
    cout << "IGBTcount: " << IGBTcount << endl;
    cout << "MOScount: " << MOScount << endl;
    cout << x_pdc[0] << "  " << x_pdc[1] << "  " << x_pdc[2] << "  " << x_pdc[3] << "  " << x_pdc[4] << endl;
    cout << gateT[0] << "  " << gateT[1] << "  " << gateT[2] << "  " << gateT[3] << "  " << gateT[4] << "  "
         << gateT[5] << endl;

//    ofs << y << endl;
//    ofs << J << endl;
//    ofs << Calc << endl;
//    ofs.close();

}

void all_mpcFileTest() {

    time_t curr_time;
    struct tm *curr_tm;
    time(&curr_time);
    curr_tm = localtime(&curr_time);

    char name[256];
    sprintf(name, "..\\data\\v51-update6 N-%d T-%d %d-%d %d-%d-%d.txt", HORIZON, THREADNUM, curr_tm->tm_mon,
            curr_tm->tm_mday, curr_tm->tm_hour, curr_tm->tm_min, curr_tm->tm_sec);
    fstream outFile(name, ios::out);
    fstream inFile("..\\EXPORT1207.csv", ios::in);

    if (inFile.is_open()) {
        cout << "File has been opened" << endl;
    } else {
        cout << "NO FILE HAS BEEN OPENED" << endl;
    }


    vector<vector<string>> content;
    vector<string> row;
    string line, word;

    while (getline(inFile, line)) {
        row.clear();
        stringstream str(line);

        while (getline(str, word, ',')) {
            row.push_back(word);
        }

        content.push_back(row);

    }

    float xref_temp[5] = {680.7330891, 0, 2095.081021, 0, 0};
    float v_temp[2] = {213.2217261, 656.2289962};
    float x_temp[5] = {642.8562777, 248.1856559, 2079.605031, -78.0879658, -118.8860798};
    float prestate_temp[6] = {0, 1, 0, 1, 1, 1};


    float16_t xref[5] = {680.7330891, 0, 2095.081021, 0, 0};
    float16_t v[2] = {213.2217261, 656.2289962};
    float16_t x[5] = {642.8562777, 248.1856559, 2079.605031, -78.0879658, -118.8860798};
    bool p_state[6] = {0, 1, 0, 1, 1, 1};
    float16_t x_pdc[5] = {0, 0, 0, 0, 0};
    int round = 0;

    float_sp IGBTcount = 0;
    float_sp MOScount = 0;

    for (int i = 1; i < content.size(); i++) {
        for (int j = 0; j < 5; ++j) {
            xref_temp[j] = stof(content[i][1 + j]);
            xref[j] = xref_temp[j];
        }
        for (int j = 0; j < 5; ++j) {
            x_temp[j] = stof(content[i][6 + j]);
            x[j] = x_temp[j];
        }
        for (int j = 0; j < 2; ++j) {
            v_temp[j] = stof(content[i][11 + j]);
            v[j] = v_temp[j];
        }
        for (int j = 0; j < 6; ++j) {
            prestate_temp[j] = stof(content[i][13 + j]);
            p_state[j] = prestate_temp[j];
        }

        ap_int_4 y = -1;
        float_sp J = -1;
        float16_t Calc = -1;


        bool CountReset = 0;

        APFIX_16_Qquad Q_quad = 0.0617;
        APFIX_16_Qsw Q_switch = 0;
        APFIX_16_QswConst_IGBT Q_switchConst_IGBT = 1.2472;
        APFIX_16_QswConst_MOS Q_switchConst_MOS = 0.0016;
        APFIX_16_Qcur Q_currentlim = 8000;

        bool gateT[6];


        MPCcore(&y, &J, Calc, xref, x, gateT, v, p_state, x_pdc, Q_quad, Q_switch,
                Q_switchConst_IGBT,
                Q_switchConst_MOS, Q_currentlim);


//        cout << "---- current round is " << round << " ,total round is " << content.size() << " ---- " << endl;
//        cout << "Y: " << y << endl;
//        cout << "IGBTcount: " << IGBTcount << endl;
//        cout << "MOScount: " << MOScount << endl;
//        cout << x_pdc[0] << "  " << x_pdc[1] << "  " << x_pdc[2] << "  " << x_pdc[3] << "  " << x_pdc[4] << endl;
//        cout << gateT[0] << "  " << gateT[1] << "  " << gateT[2] << "  " << gateT[3] << "  " << gateT[4] << "  "
//             << gateT[5] << endl;
//
//        round += 1;
//        outFile << y << "  " << J << endl;

    }

    outFile.close();
    inFile.close();

}


int main() {

//    float16_t xref[5] = {7.23254286, 0, -31.88567068, 0, 0};
//    float16_t v[2] = {12.71946534, -56.07553122};
//    float16_t x[5] = {6.930769685, -2.500030409, -17.10623043, -12.79162832, -0.950573168};
//    bool p_state[6] = {1, 0, 1, 0, 0, 1};
//
//    APFIX_16_Qquad Q_quad = 0.0617;
//    APFIX_16_Qsw Q_switch = 0;
//    APFIX_16_QswConst Q_switchConst_IGBT = 1.2472;
//    APFIX_16_QswConst Q_switchConst_MOS = 0.0016;
//    APFIX_16_Qcur Q_currentlim = 8000;
//
//    cout << Q_quad << endl;
//    cout << Q_switchConst_IGBT << endl;
//    cout << Q_switchConst_MOS << endl;
////    float16_t xref[5] = {7.21875, 0, -31.875, 0, 0};
////    float16_t v[2] = {12.625, -56};
////    float16_t x[5] = {6.92188, -2.5, -17.0938, -12.7813, -0.9375};
////    bool p_state[6] = {1, 0, 1, 0, 0, 1};
//
//    for (const auto & i : xref) {
//            cout << i << endl;
//    }
//
//    for (const auto & i : v) {
//        cout << i << endl;
//    }
//
//    for (const auto & i : x) {
//        cout << i << endl;
//    }

//
//    bool Result;
//    ap_ufixed<8, 5> Val1 = 1.25;
//    ap_fixed<9, 4> Val2 = 17.25;
//    cout << Val2 << endl;
//    ap_fixed<10, 5> Val3 = 3.25;
//    Result = Val1 == Val2;
//    cout <<  Result << endl; // Yields true
//    Result = Val1 == Val3;
////    cout <<  Result << endl; // Yields false

float16_t a = 1.5;
//ap_int_4 b = 2;
//cout << a + b << endl;
    // Definition of basic data type
#define INPUT_DATA_WIDTH 12
#define IN_INTG_WIDTH 6
#define IN_QMODE AP_RND_ZERO
#define IN_OMODE AP_WRAP
    typedef ap_fixed<INPUT_DATA_WIDTH, IN_INTG_WIDTH, IN_QMODE, IN_OMODE>
            data_t;
// Definition of variables
    data_t Val1, Val2;
// Res is automatically sized at run-time to be 1-bit greater than INPUT_DATA_WIDTH
// The bit growth in Res will be in the integer bits
    ap_int <data_t::width+1> Res = 1;

    single_mpctest();
//    all_mpcFileTest();


    return 0;
}

