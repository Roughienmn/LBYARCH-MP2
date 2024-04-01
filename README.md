Comparative execution time of kernels
Short analysis of performance of kernels
Screenshots of program output w/ correctness check (C)
Screenshots of program output w/ correctness check (x86-64)

# x86-to-C Interface Programming Project
This project was made to compare the performance of two kernel versions, implemented in C and x86-64 Assembly. The performance is measured in terms of execution time, and are executed in both Debug and Release Configurations of Visual Studio 2022.
### Group Members:
Chan, Dane Marcus  
Gamboa, Rafael Tadeo  

## Specifications
The project comprises of 2 kernel versions (C and x86-64), and both are to simulate the DAXPY (AX + Y) function. 

**Input:**
- Scalar variable **_n_** (integer) contains the length of the vectors X, Y, and Z
  - For the analysis, n will have possible values of **2^20, 2^24,** and **2^28**
- Scalar variable **_A_** is a double-precision float value (set to **2.00** for the analysis)
- Vectors **_X, Y,_** and **_Z_** are double-precision floats of length n
  - For the analysis, **_X and Y_** are initialized with random double-precision float values
  
**Process:** **Z[i] = A • X[i] + Y[i]**  
Performs the DAXPY function (**D**ouble precision **AX** **P**lus **Y**) on the given inputs.

**Output:**  
Store the result in vector **_Z_**. Display the result of the first 10 elements of vector Z for all kernel versions (C and x86-64).  

## Results and Analysis
### Debug Mode

---------------------
### Release Mode

---------------------
### Summary of Results
#### Debug Mode Results
| Vector Size | C Execution Time (Average) (ms) | x86-64 Execution Time (Average) (ms) | Time Difference (C - x86-64) |
| :---------- | :------------------------------ | :----------------------------------- | :-------------- |
| 2^20        | 1.60ms                   |  1.10ms                       | 0.50ms   |
| 2^24        | 26.77ms                   |  19.27ms                       | [insert time]   |
| 2^28        | 456.83ms                   |  317.17ms                       | [insert time]   |


#### Release Mode Results
| Vector Size | C Execution Time (Average) (ms) | x86-64 Execution Time (Average) (ms) | Time Difference (C - x86-64) |
| :---------- | :------------------------------ | :----------------------------------- | :--------------------------- |
| 2^20        | 1.60ms                   |  1.10ms                       | -0.30ms   |
| 2^24        | 22.37ms                   |  23.03ms                       | -0.66ms   |
| 2^28        | 326.03ms                   |  333.67ms                       | -7.64ms  |
