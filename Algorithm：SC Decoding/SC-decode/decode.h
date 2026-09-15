/*****************************************************************//**
 * \file   sc.h
 * \brief  SC decoding
 * 
 * Input:
 * SC: A_list
 * SC_decode: llr
 * 
 * Output:
 * SC_decode: message_decode
 * 
 * \author YZJ
 * \date   July 2023
 *********************************************************************/

#pragma once
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <cstdlib>
#include <stdlib.h>
#include "variables.h"
using namespace std;


/*****************************************head******************************************/

class SC
{
public:
    SC(int* list);
    ~SC();

    int* SC_decode(double* llr);

private:
    int i, j;
    int A_list[N] = { 0 };

    //P array ------ C array
    double P[N][n + 1] = { 0.0 };
    int C[N][n + 1] = { 0 };

    double f(double a, double b);
    double g(double a, double b, int c);
    int mod(int a, int b);
};


/****************************************program****************************************/


SC::SC(int* list)
{
    for (int i = 0; i < N; i++)
    {
        A_list[i] = list[i];
    }
}

SC::~SC()
{
}

/**
 * .SC decoding function
 * 
 * \param llr
 * \return u
 */
int* SC::SC_decode(double* llr)
{
    /*****************************************Basic Parameter Setup*****************************************/

    int layer;
    // number of mod operations
    int A[N] = { 0 };
    for (int i = 0;i < N;i++) {
        int j = i + 1;
        layer = 0;
        while (j % 2 == 0) {
            j /= 2;
            layer += 1;
        }
        A[i] = layer;
    }

    // number of f operations
    int B[N] = { 0 };
    for (int i = 1; i < N; i++) {
        int j = i;
        layer = 0;
        while (j % 2 == 0) {
            j /= 2;
            layer += 1;
        }
        B[i] = layer;
    }

    //store input LLR in P[i][n]
    for (int i = 0; i < N; i++) {
        P[i][n] = llr[i];
    }

    /*******************************************Program Start********************************************/



    /****************************************First Codeword: start****************************************/

    /* compute C[0][0] first; it is special, decodes the first bit */
    int h = N;
    for (int j = n - 1; j >= 0; j--) {
        for (int i = 0; i < h / 2; i++) {
            P[i][j] = f(P[i][j + 1], P[i + h / 2][j + 1]);
        }
        h /= 2;
    }
    if (!A_list[0])
    {
        C[0][0] = 0;
    }
    else
    {
        C[0][0] = (int)P[0][0] > 0 ? 0 : 1;
    }

    /****************************************First Codeword: end****************************************/



    /***************************************Other Codewords: start****************************************/

    /* start from layer 2; decode bits 2 to N */
    for (int k = 1; k < N; k++)
    {
        /* odd index: g + mod */
        if (k % 2 == 1) {
            if (!A_list[k])
            {
                C[k][0] = 0;
            }
            else
            {
                int temp = (g(P[k - 1][1], P[k][1], C[k - 1][0]) > 0 ? 0 : 1);
                C[k][0] = (int)temp;
            }

            int num1 = A[k];                           //num1: number of mod operations

            for (int j = 0; j < num1; j++) {
                int num2 = pow(2, j);                  // num2: mod distance
                for (int l = 0; l < num2; l++) {
                    C[k - l - num2][j + 1] = mod(C[k - l - num2][j], C[k - l][j]);
                    C[k - l][j + 1] = C[k - l][j];
                }
            }
        }

        /* even index: g + f */
        if (k % 2 == 0)
        {
            int num3 = B[k];                           //num3: number of f operations

            // g operation
            int j = num3;
            int num4 = pow(2, num3);                  //num4: operation distance
            for (int r = 0; r < num4; r++) {
                P[k + r][j] = g(P[k - num4 + r][j + 1], P[k + r][j + 1], C[k - num4 + r][j]);
            }

            // f operations
            for (int q = j; q > 0; q--) {
                int num5 = pow(2, q - 1);
                for (int i = 0;i < num5;i++) {
                    P[k + i][q - 1] = f(P[k + i][q], P[k + num5 + i][q]);
                }
            }

            if (!A_list[k])
            {
                C[k][0] = 0;
            }
            else
            {
                int temp = P[k][0] > 0 ? 0 : 1;
                C[k][0] = (int)temp;
            }
        }

    }

    /****************************************Other Codewords: end****************************************/

    /*******************************************Program End********************************************/

    int* u_d = new int[N];
    for (int i = 0;i < N;i++) {
        u_d[i] = C[i][0];
    }

    return u_d;
}

/**
 * .f function
 * 
 * \param a
 * \param b
 * \return 
 */
double SC::f(double a, double b)
{
    double z = a * b > 0 ? 1 : -1;
    z = fmin(fabs(a), fabs(b)) * z;
    return z;
}

/**
 * .g function
 * 
 * \param a
 * \param b
 * \param c
 * \return 
 */
double SC::g(double a, double b, int c)
{
    return (1 - 2 * c) * a + b;
}

/**
 * .mod function
 * 
 * \param a
 * \param b
 * \return 
 */
int SC::mod(int a, int b)
{
    if (a == b) {
        return 0;
    }
    else {
        return 1;
    }
}