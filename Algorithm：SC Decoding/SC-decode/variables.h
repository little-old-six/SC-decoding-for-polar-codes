#pragma once
#ifndef VARIABLES_H
#define VARIABLES_H 1

/*======== adjustable parameters ========*/
// polar code parameters
#define n 10



/*======== control parameters ========*/
#define flg_channel         0                                      // polar construction: 0 = GA, 1 = 5G NR



/*======== fixed parameters ========*/
#define SNR_inc             0.5                                    // SNR step
#define frozen_bit          0                                      // frozen bit
#define code_rate           0.5                                    // code rate
double GA_SNR = 2.5;                                               // GA construction SNR
#define pi                  3.1415926
#define inf                 9999999



/*======== general parameters ========*/
int max_error_num = 300;                                           // max_error_num: max number of errors
double max_run_time = 1E10;                                        // max_run_time: max number of runs
double min_run_time = 1E5;                                         // min_run_time: minimum number of runs
long int run;                                                      // run: current run number
double FZD = 0.0;                                                  // FZD: average complexity
double FER = 0.0, BER = 0.0;                                       // FER: frame error rate; BER: bit error rate
float SNR_start, SNR_finish;                                       // SNR range
clock_t start, finish;                                             // timing
int cost;                                                          // time cost of simulation



/*======== Polar code parameters ========*/
#define len_redundancy           0
#define N                        (1<<n)                            // number of codeword
#define K_msg                    int( N * code_rate)               // number of msg bits
#define K                        (K_msg + len_redundancy)          // number of information bits


#endif