/***************************************************
				  Polar code encoder
Input:
Polar_encode: A_list, N, K, CRC length; noise variance sigma
Encode: position - indices of information subchannels;

Output: message, received_symbol

***************************************************/

#pragma once
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <stdlib.h>
#include "variables.h"
using namespace std;


/*****************************************head******************************************/

class Polar_encode
{
public:
	Polar_encode(int* list, int* pos, double sigma1);
	~Polar_encode();

	void Encode(int* message, double* received_symbol);

private:
	int i, j;
    double sigma;

	int A_list[N] = { 0 };
	int position[N] = { 0 };
	int code_symbol[N] = { 0 };

	void encode(int* u);         //x = u*G
	void BPSK_AWGN(double* a);    //BPSK_AWGN
};



/****************************************program****************************************/

Polar_encode::Polar_encode(int* list, int* pos, double sigma1)
{
	sigma = sigma1;

	for (int i = 0; i < N; i++)
	{
		A_list[i] = list[i];
	}

	for (int i = 0; i < K; i++)
	{
		position[i] = pos[i];
	}
}

Polar_encode::~Polar_encode()
{
}


/**
 * .polar encode and awgn_bpsk
 * 
 * \param message
 * \param received_symbol
 * \param position
 */
void Polar_encode::Encode(int* message, double* received_symbol)
{
	//set 0
	memset(code_symbol, 0, sizeof(code_symbol));

	// get message bit
	for (int i = 0; i < K; i++)
		message[i] = rand() % 2;

	// add the frozen bit
	for (int i = 0; i < K; i++)
		code_symbol[position[i]] = message[i];

	//x = u*G
	encode(code_symbol);

	//BPSK_AWGN
	BPSK_AWGN(received_symbol);
}


/**
 * .x = u*G
 * 
 * \param u
 */
void Polar_encode::encode(int* u)
{
	int i_s, i_g, del, base, i_sg;

	// Kronecker product
	for (i_s = 0; i_s < n; i_s++)
	{
		for (i_g = 0; i_g < (1 << (n - i_s - 1)); i_g++)
		{
			del = (1 << i_s);
			base = (1 << (i_s + 1)) * (i_g);
			for (i_sg = 0; i_sg < del; i_sg++)
			{
				u[base + i_sg] = u[base + i_sg] ^ u[base + i_sg + del];
			}
		}
	}
}


/**
 * .BPSK & AWGN
 * 
 * \param a
 */
void Polar_encode::BPSK_AWGN(double* a)
{
	double u, r, g;
	for (int i = 0; i < N; i++)
	{
		u = (float)rand() / (float)RAND_MAX;
		if (u == 1.0)
			u = 0.999999;
		r = sigma * sqrt(2.0 * log(1.0 / (1.0 - u)));

		u = (float)rand() / (float)RAND_MAX;
		if (u == 1.0)
			u = 0.999999;
		g = (float)r * cos(2 * pi * u);

		a[i] = (1 - 2 * code_symbol[i]) + g;
	}
}



