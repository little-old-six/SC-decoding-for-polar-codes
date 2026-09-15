/*****************************************************************//**
 * \file   SC-decode.cpp
 * \brief  SC decoding algorithm
 * 
 * \author YZJ
 * \date   November 2023
 *********************************************************************/

#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include <algorithm>
#include "Pol_encode.h"
#include "decode.h"
#include "ga.h"
#include "variables.h"
#include "other.h"
#include "File_save.h"
#include "5G_NR.h"
using namespace std;


float rate = code_rate;   // code rate


// SC decoding algorithm
int main()
{
	double N0, sigma;                                                // N0 noise variance; sigma noise std. dev.
	unsigned long long error[2] = { 0 }, error_num;                  // error[0] total error bits; error[1] total error frames; error_num error bits of this run

	int A_list[N] = { 0 };                                           // information bit positions
	int message[K] = { 0 };                                          // original information bits
	int message_decode[K] = { 0 };                                   // decoded information bits
	double received_symbol[N] = { 0 };                               // received symbols
	double llr[N] = { 0 };                                           // LLR of received symbols
	int data_position[K] = { 0 };                                    // position of message bit and crc bit 
	int frozen_position[N - K] = { 0 };                              // positions of frozen bits, earlier = less reliable 


	/* obtain input parameters */
	Obtain_input_parameters();

	//random seed
	srand((int)time(0));

	// polar construction: 0 = GA, 1 = 5G NR
	switch (flg_channel)
	{
	case 0:
	{
		//select the transmission channel for message bit
		Channel_GA c(GA_SNR, rate);
		c.Get_information_pos(A_list, data_position, K);
	}
	break;
	case 1:
	{
		// 5G NR construction
		NR_5G(A_list, frozen_position, data_position);
	}
	break;
	default:
		abort();
		break;
	}

	sort(data_position, data_position + K);

	//save to text
	SAVE s(0);
	s.Save_main();

	printf(" Polar  code     SNR     BER           FER            Block errors    Run times    Time cost \n\n");
	for (double SNR = SNR_start; SNR <= SNR_finish; SNR += SNR_inc)
	{
		//time start
		start = clock();

		// compute basic parameters
		N0 = 1 / (2 * rate) * pow(10, (-(double)(SNR) / 10));          // noise variance / 2
		sigma = sqrt(N0);                                              // noise std. dev.

		Polar_encode a(A_list, data_position, sigma);                  // encode	
		SC b(A_list);                                                  // decode

		error[0] = error[1] = error_num = run = 0;
		while (error[1] < max_error_num && run < max_run_time)
		{
			run++;

			//set 0
			memset(message, 0, sizeof(message));
			memset(received_symbol, 0, sizeof(received_symbol));
			memset(message_decode, 0, sizeof(message_decode));

			/* Polar encode */
			a.Encode(message, received_symbol);

			/* calcuate llr */
			for (int i = 0; i < N; i++)
				llr[i] = (2 / N0) * received_symbol[i];

			/* SC decode */
			int* U_decode = b.SC_decode(llr); // decoded result

			/* pick out the codeword */
			for (int i = 0; i < K; i++)
				message_decode[i] = U_decode[data_position[i]];
			delete[] U_decode;           //release

			/* check decoding errors */
			error_num = 0;
			for (int i = 0; i < K; i++)
			{
				if (message[i] != message_decode[i])
					error_num++;
			}

			error[0] += error_num;
			if (error_num != 0)
				error[1]++;

			/* calcuate BERand FER */
			BER = (double)error[0] / ((double)run * K_msg);
			FER = (double)error[1] / (double)run;
			printf("(%5d,%5d)    %2.2f    %1.3E     %1.3E      %-5d           %-7d\r", 
				N, K_msg, SNR, BER, FER, error[1], run);
		}

		//time end
		finish = clock();

		//calcuate the time cost
		cost = (double)(finish - start) / CLOCKS_PER_SEC;

		printf("(%5d,%5d)    %2.2f    %1.3E     %1.3E      %-5d           %-7d      %-d s\n\n", 
			N, K_msg, SNR, BER, FER, error[1], run, cost);

		//save to text
		s.writeData(SNR);
	}

	system("pause");
	getchar();
	return 0;
}
