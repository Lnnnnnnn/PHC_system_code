#include "ap_header.h"
#include <fstream>
#include <ctime>
#include <sstream>


//float16_h_t T_abc_to_alphabeta[3][3] =
//        {{0.8165, -0.4082, -0.4082},
//         {0.0000, 0.7071,  -0.7071},
//         {0.5774, 0.5774,  0.5774}};

void transtest() {
    float16_t abr_in[3] = {1, 100, 60};
    float16_t abc_out[3] = {0, 0, 0};

    T_abc_to_alphabeta(abr_in, abc_out);

    for (const auto &i: abc_out) {
        cout << i << endl;
    }

}

void all_mpcFileTest() {

    time_t curr_time;
    struct tm *curr_tm;
    time(&curr_time);
    curr_tm = localtime(&curr_time);

    char name[256];
    sprintf(name, "..\\v48-TESTBENCHOUTDATA N-%d T-%d %d-%d %d-%d-%d.txt", HORIZON, THREADNUM, curr_tm->tm_mon,
            curr_tm->tm_mday, curr_tm->tm_hour, curr_tm->tm_min, curr_tm->tm_sec);

    fstream outFile(name, ios::out);
    fstream inFile("D:\\MyRespostiry\\Cpp\\TRANS_v2\\testdata.csv", ios::in);

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

    float abr_in_temp[5] = {680.7330891, 0, 0};

    float16_t abr_in[3] = {1, 100, 60};
    float16_t abc_out[3] = {0, 0, 0};


    for (int i = 1; i < content.size(); i++) {
        for (int j = 0; j < 3; ++j) {
            abr_in_temp[j] = stof(content[i][j]);
            abr_in[j] = abr_in_temp[j];
        }

        T_abc_to_alphabeta(abr_in, abc_out);


        cout << abc_out[0] << "  " << abc_out[1] << "  " << abc_out[2] << endl;
        outFile << abc_out[0] << "  " << abc_out[1] << "  " << abc_out[2] << endl;

    }

    outFile.close();
    inFile.close();

}


int main() {




//    single_mpctest();
    all_mpcFileTest();
//    transtest();

    return 0;
}

