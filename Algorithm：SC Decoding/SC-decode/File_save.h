/*****************************************************************//**
 * \file   File_save.h
 * \brief  Data saving
 * 
 * \author YZJ
 * \date   December 2023
 *********************************************************************/
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <fstream>
#include <vector>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include "variables.h"
using namespace std;

/*****************************************head******************************************/

class SAVE
{
public:
	SAVE(int LL);
	~SAVE();

    void Save_main();
    void writeData(double SNR);

private:

    string filename; // file name
    string filename2; // remark

    void clearFile(const std::string& filename);
    string formatDouble(double number);
};

/****************************************program****************************************/


SAVE::SAVE(int LL)
{
    string snr1 = formatDouble(SNR_start);
    string snr2 = formatDouble(SNR_finish);
    string snr3 = formatDouble(code_rate);
    string snr4 = formatDouble(GA_SNR);

    string s_title = "SC (" + to_string(N) + "," + to_string(K_msg) + ")";
    string s_snr = "; SNR [" + snr1 + "," + snr2 + "]";
    string s_other = " ";

    filename = s_title + s_other + s_snr + ".txt";

    string a1 = "/***************************************************\n\n";
    string b = "SC\n\nTraditional Successive Cancellation\n\n";
    string c = "Max error num = " + to_string(max_error_num) + "\n\n"
        + "Code rate = " + to_string(code_rate) + "\n\n"
        + "SNR Step = " + to_string(SNR_inc) + "\n\n";
    string d;
    if (flg_channel == 0)
    {
        d = "Channel construction: GA " + snr4 + "\n\n";
    }
    else if (flg_channel == 1)
    {
        d = "Channel construction: 5G NR\n\n";
    }
    string a2 = "***************************************************/\n\n";

    filename2 = a1 + b + c + d + a2;
}

SAVE::~SAVE()
{
    std::cout << "File saved successfully!" << std::endl;
}

/**
 * . Clear the file and write the first line
 */
void SAVE::Save_main()
{

    // clear the file
    clearFile(filename);

    // write the first line
    std::ofstream ofs;
    ofs.open(filename);
    if (ofs.is_open()) {
        ofs << filename << "\n\n";
        ofs << filename2;
        ofs << " Polar  code     SNR           BER                   FER                     FZD\n";
        ofs.close();
    }
    else {
        std::cout << "Error opening file: " << filename << std::endl;
        return;
    }



}

/**
 * . Clear the file
 * 
 */
void SAVE::clearFile(const std::string& filename)
{
    std::ofstream ofs;
    ofs.open(filename, std::ofstream::out | std::ofstream::trunc);
    ofs.close();
}

/**
 * .Convert double to string
 * 
 * \param number
 * \return 
 */
string SAVE::formatDouble(double number)
{
    std::ostringstream streamObj;
    streamObj << std::fixed << std::setprecision(2) << number;
    std::string formattedString = streamObj.str();
    return formattedString;
}

/**
 * . Write data: BER, FER, FZD
 * 
 */
void SAVE::writeData(double SNR)
{
    ofstream ofs;
    ofs.open(filename, std::ofstream::app);

    if (ofs.is_open()) {

        ofs << fixed << setprecision(2);  // 2 decimal places

        ofs << "(" << setw(5) << N << "," << setw(5) << K_msg << ")    "
            << setw(5) << SNR << "    "
            << scientific << setprecision(6) << uppercase << BER << "     "
            << scientific << setprecision(6) << uppercase << FER << "      "
            << scientific << setprecision(6) << uppercase << FZD << "      "
            << "\n";

        ofs.close();
    }
    else {
        cout << "Error opening file: " << filename << endl;
    }
}
