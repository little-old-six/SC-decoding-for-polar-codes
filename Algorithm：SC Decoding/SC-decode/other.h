/***************************************************
              Miscellaneous utilities
Obtain_input_parameters: read input parameters

***************************************************/

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "variables.h"
using namespace std;


/*****************************************head******************************************/

// read input parameters
static void Obtain_input_parameters();


/****************************************program****************************************/

static void Obtain_input_parameters()
{
    cout << "\n/***************************************************\n\n";
    printf("Successive Cancellation Decoding \n\nPolar code: (%d,%d)\n\n", N, K_msg);
    if (flg_channel == 0)
    {
        printf("Message bits filled in order\n\nChannel construction: GA %.1f\n\n", GA_SNR);
    }
    else if (flg_channel == 1)
    {
        printf("Message bits filled in order\n\nChannel construction: 5G\n\n");
    }
    cout << "/***************************************************\n\n";
    cout << "Version: V1.2 \n\n" << "Code rate = " << code_rate << "\n\nMax error num = " << max_error_num;
    printf("; Max run num = %.0E\n\n", max_run_time);
    cout << "SNR Step = " << SNR_inc << endl << endl;

    cout << "Enter start SNR: ";
    cin >> SNR_start;
    cout << "\nEnter finish SNR: ";
    cin >> SNR_finish;
    printf("\n");

}