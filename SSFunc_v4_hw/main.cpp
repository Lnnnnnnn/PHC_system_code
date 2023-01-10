#include "ap_header.h"
#include <fstream>
#include <ctime>
#include <sstream>

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

    float16_t xref[5] = {9.965168807, 0, -61.66318523, 0, 0};
    float16_t v[2] = {110.0802557, -681.1624897};
    float16_t x[5] = {-23.59462496, 197.7574825, -98.21537648, 114.0159397, 25.46739295};
    float16_t prestate[6] = {1, 0, 1, 0, 0, 1};

    float16_t y = -1;
    float16_t J = -1;
    float16_t Calc = -1;

//    MPCcore(&y, &J, &Calc, xref, x, v, prestate);

    cout << y << endl;
    cout << J << endl;
    cout << Calc << endl;

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
    sprintf(name, "..\\data\\20000-TESTBENCHOUTDATA N-%d T-%d %d-%d %d-%d-%d.txt", HORIZON, THREADNUM, curr_tm->tm_mon,
            curr_tm->tm_mday, curr_tm->tm_hour, curr_tm->tm_min, curr_tm->tm_sec);

    fstream outFile(name, ios::out);
    fstream inFile("D:\\MyRespostiry\\Cpp\\PHC_v34_Justworker_def\\FPGA1E4.csv", ios::in);

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
    float16_t prestate[6] = {0, 1, 0, 1, 1, 1};

    int round = 0;

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
            prestate[j] = prestate_temp[j];
        }

        float16_t y = -1;
        float16_t J = -1;
        float16_t Calc = -1;

//        MPCcore(&y, &J, &Calc, xref, x, v, prestate);


        cout << y + 1 << endl;

        cout << "---- current round is , total round is -----" << content.size() << endl;
        cout << round << endl;
        round += 1;

        outFile << y + 1 << " " << J << endl;

    }

    outFile.close();
    inFile.close();

}

void CS_test() {
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

    float16_t xref[5] = {9.965168807, 0, -61.66318523, 0, 0};
    float16_t v[2] = {110.0802557, -681.1624897};
    float16_t x[5] = {-23.59462496, 197.7574825, -98.21537648, 114.0159397, 25.46739295};
    float16_t prestate[6] = {1, 0, 1, 0, 0, 1};

    float16_t y = -1;
    float16_t J = -1;
    float16_t Calc = -1;

    ap_int_4 ls = 5;

    float16_t xs[THREADNUM][XNSIZE] = {{-5,       -10.75,   78,       65,       -7640},
                                       {-239,     8086,     78,       7737,     -247.25},
                                       {8168.25,  36,       7766,     -261,     8188},
                                       {-3.5,     -57.75,   94,       -16.25,   -4.75},
                                       {-7478.25, -208.75,  -8131.75, 146,      -3058.5},
                                       {-2804.5,  8133,     61.75,    1746,     -2854},
                                       {79.5,     82.75,    1678,     -2784.25, 106.25},
                                       {-12.75,   5490.25,  -170.5,   -8128.5,  -7},
                                       {8016.75,  -68.5,    -8115.5,  65,       2.25},
                                       {-2749.75, 193.75,   78,       65,       0},
                                       {71.25,    223,      -7362,    -261,     8190.5},
                                       {90,       -2926.5,  -2707,    8174.5,   -2.5},
                                       {-7464.75, -21.75,   -8131.75, 146,      7456},
                                       {-154,     -8064,    61.75,    -6054,    -247.25},
                                       {-8131.5,  269.75,   138,      -178.75,  8188},
                                       {80.75,    176.25,   78,       65,       -4.75},
                                       {-7087.75, -348.5,   -8034.5,  227,      -6051.75},
                                       {-285.75,  7992.5,   159,      -5755,    -244.75},
                                       {8121.5,   -57.75,   5319.75,  -98.75,   8190.5},
                                       {-50.25,   -151.25,  175.25,   146,      -2.5},
                                       {-6430,    -111,     -8050.5,  308,      1.5},
                                       {-50.25,   -151.25,  142.75,   -6816,    -246.5},
                                       {8112,     -11,      -7377,    -17.75,   8188},
                                       {-59.75,   7351.5,   -85,      -7966.5,  -4.75},
                                       {-7502,    -162,     -8034.5,  227,      -559.5},
                                       {3676.5,   13.5,     159,      -7309,    -242.5},
                                       {-8169,    129.5,    176.75,   146,      2.25},
                                       {43.25,    37.5,     175.25,   150,      0},
                                       {-4889.75, -116.25,  -8050.75, 308,      -6673.75},
                                       {-201.5,   -8157.5,  142.75,   -5694,    -244.75},
                                       {-8178.25, 176.25,   -7249,    -17.75,   8190.5},
                                       {34,       -5919.25, -85.75,   -7966.5,  -2.5},
                                       {-6115.75, -349.25,  8187.25,  -97.25,   -3785.75},
                                       {-286,     7992.5,   -3.25,    -7505.25, -244.75},
                                       {8121.5,   -57.75,   -6041,    -423,     8190.5},
                                       {-50.25,   -677.25,  3636.75,  -154,     -2.5},
                                       {-7743.75, -303,     8171,     -16.25,   -6054},
                                       {-295,     8039.25,  -19.5,    -5422.5,  -247.75},
                                       {8112,     -11,      -6005.25, -342,     8188},
                                       {-59.75,   -6088.5,  -248,     8093.25,  -4.75},
                                       {-6166,    -162,     8187.25,  -97.25,   7676.5},
                                       {-192,     8179.75,  -3.25,    -6153.25, -242.5},
                                       {-8169,    129.5,    -6041,    -423,     -8191.25},
                                       {43.25,    -7372,    -231.75,  8012.25,  0},
                                       {-5323.5,  -115.75,  8171,     -16.25,   216.25},
                                       {-2806,    147,      -19.5,    -7160.25, -248.75},
                                       {-8178.25, 176.25,   -439.25,  3526.5,   0.75},
                                       {34,       -6045.25, -248,     8093.25,  -2.5},
                                       {-6090.5,  -442.75,  -8115.5,  65,       8.75},
                                       {936.5,    7899,     78,       541,      -2847},
                                       {-4.75,    -151.25,  -5376.5,  -69.25,   -8191},
                                       {-97,      -244.75,  94,       -16.25,   0},
                                       {-115.75,  -151.25,  61.75,    146,      3148.75},
                                       {3320,     7945,     61.75,    154,      0},
                                       {-125.25,  -104.5,   78,       65,       0},
                                       {-106.5,   -198,     78,       65,       -2.5},
                                       {-12.75,   -10.75,   78,       65,       1456.5},
                                       {3422.75,  8085.25,  78,       65,       4.5},
                                       {-22.25,   36,       98.25,    1008,     4.5},
                                       {-3.5,     420.25,   -2755.25, 94.75,    2.25},
                                       {-5492.75, -17,      -8131.5,  146,      4.5},
                                       {-3.5,     -57.75,   61.75,    146,      2.25},
                                       {-31.5,    82.75,    -8142,    3482,     -8192},
                                       {-12.75,   -0.75,    78,       65,       0}};
    float16_t Js[THREADNUM];

    Cost_function(xref, xs, ls, Js);

    for (auto &J: Js) {
        cout << J << " "<< endl;

    }
//    cout << y << endl;
//    cout << J << endl;
//    cout << Calc << endl;

//    ofs << y << endl;
//    ofs << J << endl;
//    ofs << Calc << endl;
//    ofs.close();

}

void SS_test() {

    time_t curr_time;
    struct tm *curr_tm;
    time(&curr_time);
    curr_tm = localtime(&curr_time);

    char name[256];
    sprintf(name, "..\\data\\v41-TESTBENCHOUTDATA N-%d T-%d %d-%d %d-%d-%d.txt", HORIZON, THREADNUM, curr_tm->tm_mon,
            curr_tm->tm_mday, curr_tm->tm_hour, curr_tm->tm_min, curr_tm->tm_sec);

    fstream outFile(name, ios::out);
    fstream inFile("D:\\MyRespostiry\\Cpp\\SSFunc_v4_hw\\debug_001.csv", ios::in);

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
    float y_temp;


    float16_t xref[5] = {680.7330891, 0, 2095.081021, 0, 0};
    float16_t v[2] = {213.2217261, 656.2289962};
    float16_t x[5] = {642.8562777, 248.1856559, 2079.605031, -78.0879658, -118.8860798};
    bool p_state[6] = {0, 1, 0, 1, 1, 1};
    float16_t y = 0;


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
        for (int j = 0; j < 1; ++j) {
            y_temp = stof(content[i][19 + j]);
            y = y_temp;
        }


        float16_h_t Q_quad = 100;
        float16_t Q_switch = 0;
        float16_t Q_switchConst_IGBT = 114.54;
        float16_t Q_switchConst_MOS = 34.79;
        float16_t Q_currentlim = 80.86;


//
//
//    float16_t xref[5] = {32.43783719, 0, -4.09785181, 0, 0};
//    float16_t v[2] = {57.04659533, -7.20666093};
//    float16_t x[5] = {25.93523848, -8.697942763, -9.021047598, -6.242694011, -4.76235938};
//    bool p_state[6] = {1, 0, 1, 1, 0, 1};

        float16_t x_out[5] = {0, 0, 0, 0, 0};
//
//    ap_int_4 y = 1;
//    float16_t J = -1;
//    float16_t Calc = -1;

        Statespace_function(x, x_out, v, y);
        cout << x_out[0] << " " << x_out[1] << " " << x_out[2] << " " << x_out[3] << " " << x_out[4] << " " <<  y << endl;

        outFile << x_out[0] << " " << x_out[1] << " " << x_out[2] << " " << x_out[3] << " " << x_out[4] << " " << y << endl;

//    cout << y << endl;
//    cout << J << endl;
//    cout << Calc << endl;

//    ofs << y << endl;
//    ofs << J << endl;
//    ofs << Calc << endl;
//    ofs.close();
    }
}

int main() {

//    ap_fixed<W,I,[Q,O,N]>

//    float16_t test = 1.35;
//    cout << test << endl;
//
//    ap_fixed<3, 2> z0 = -0.25;
//    cout << z0 << endl;

    float16_t neg = -100.12;
    float16_t pos_t1 = 0 - neg;
    float16_t pos_t2 = hls::abs(neg);

    cout << pos_t1 << endl;
    cout << pos_t2 << endl;


//

//
//    single_mpctest();
//    all_mpcFileTest();
//    SS_test();
//    CS_test();

    return 0;
}

