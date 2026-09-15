# SC decoding for polar codes

<p align="center">
  <b> C++ Implementation of SC Decoding for Polar Codes</b>
</p>

<p align="center">
  <a href="#description">Description</a> •
  <a href="#features">Features</a> •
  <a href="#file-structure">File Structure</a> •
  <a href="#simulation">Simulation</a> •
  <a href="#contact">Contact</a>
</p>

---

## Description

This repository provides the **C++ implementation of the Successive Cancellation (SC) decoding algorithm for Polar codes**.

The simulation is performed over an **AWGN channel with BPSK modulation**.

In addition to the SC decoder, this repository includes **Gaussian Approximation (GA)-based rate profiling** and **5G NR channel construction**, providing two commonly used approaches for Polar code construction.

---

## Features

### SC Decoding

The SC decoding algorithm is implemented in **`decode.h`**.

The main decoding function is:

```cpp
int* SC_decode(double* llr);
```

where `llr` denotes the received log-likelihood ratios (LLRs), and the function returns the SC decoding estimations.

### GA-Based Rate Profiling

The **Gaussian Approximation (GA)-based rate profiling** is implemented in **`ga.h`**.

It can be used to determine the information-bit and frozen-bit positions according to the target Polar code length and code rate.

### 5G NR Channel Construction

The channel construction specified in the **3GPP 5G NR standard** is implemented in **`5G_NR.h`**.

Users can therefore choose between GA-based rate profiling and the 5G NR channel construction according to their requirements.

---

## File Structure

| File           | Description                                           |
| :------------- | :---------------------------------------------------- |
| `main.cpp`     | Main program and simulation procedure                 |
| `variables.h`  | Configuration of Polar code and simulation parameters |
| `Pol_encode.h` | Polar encoding implementation                         |
| `decode.h`     | SC decoding implementation                            |
| `ga.h`         | GA-based rate profiling                               |
| `5G_NR.h`      | 5G NR channel construction                            |

---

## Simulation

The simulation setup is summarized below.

| Parameter         | Setting          |
| :---------------- | :--------------- |
| Modulation        | BPSK             |
| Channel           | AWGN             |
| Decoder           | SC               |
| Code construction | GA-based / 5G NR |
| Implementation    | C++              |

The Polar code parameters and other simulation settings can be configured in **`variables.h`**.

The typical simulation procedure is:

```text
Information Bits
       ↓
Polar Encoder
       ↓
BPSK Modulation
       ↓
AWGN Channel
       ↓
LLR Calculation
       ↓
SC Decoder
       ↓
Decoded Information Bits
```

---

## Getting Started
The code is developed and tested using Microsoft Visual Studio 2022.

Clone this repository and compile the source files using a C++ compiler.

The main simulation program is **`main.cpp`**.

Before running the simulation, please check the parameters in **`variables.h`** and select the desired Polar code construction method.

---


## Contact & Feedback

These algorithms might be confusing. Please read the paper carefully, and if you still do not understand it, feel free to contact me via email address ZhongjunYang at ieee dot org



