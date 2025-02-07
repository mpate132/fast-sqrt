# Fast Square Root Computation in C++

## Overview

This project implements an optimized square root function in C++ using AVX SIMD instructions and bit manipulation. The algorithm significantly improves square root calculation speed compared to traditional methods, making it ideal for high-performance computing applications.

## Features

- Fast square root computation using AVX intrinsics.
- SIMD parallel processing for handling multiple values simultaneously.
- Bitwise approximation technique with a tuned magic number.
- Newton-Raphson iterations for improved accuracy.
- Scalar fallback for handling remaining elements outside SIMD batches.
- Benchmarked for performance against the standard sqrt() function.

## Technologies Used

- C++ (Standard Library, AVX Intrinsics)
- SIMD (Single Instruction, Multiple Data)
- Numerical Methods (Newton-Raphson Approximation, Bit Manipulation)

## How It Works

### 1. SIMD Optimization with AVX

- Loads multiple floating-point values into AVX registers.
- Computes an initial approximation using a magic number.
- Applies Newton-Raphson iterations for refinement.
- Stores computed square roots back into memory.

### 2. Bit Manipulation Trick

- Uses the floating-point representation of numbers to approximate roots efficiently:

  ```cpp
  int bits = *reinterpret_cast<const int*>(&num);
  bits = (bits >> 1) + MAGIC_NUMBER;
  float guess = *reinterpret_cast<float*>(&bits);
  ```

- Provides a fast initial approximation before refinement.

### 3. Newton-Raphson Refinement

Newton-Raphson iteration is used to refine the initial guess for the square root.

#### Steps of Newton-Raphson Method

1. Compute the square of the current guess.
2. Find the difference between this square and the original number.
3. Adjust the guess by subtracting the ratio of the difference over twice the guess.
4. Repeat this process for better accuracy.

#### Newton-Raphson Formula

  ```cpp
  guess = guess - (guess * guess - num) / (2.0f * guess);
  ```

- Ensures accuracy in floating-point square root computation.

## Code Explanation

### Main Functions

- `fastsqrt(const float* in, float* out, unsigned count)`: Computes square roots for an array of numbers using AVX and Newton’s method.
- **SIMD Loop**: Processes multiple elements at a time for efficiency.
- **Scalar Fallback**: Handles remaining elements sequentially.
- **Magic Number Approximation**: Provides a fast starting point for Newton’s refinement.

## Usage

### Compiling the Program

To compile the program with AVX optimizations, use:

```bash
g++ -mavx2 fastsqrt.cpp -o fastsqrt
```

### Running the Program

```bash
./fastsqrt
```

Example Input:

```
[4.0, 9.0, 16.0, 25.0, 36.0, 49.0, 64.0, 81.0]
```

Output:

```
[2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0]
```

## Potential Improvements

- Extend to double precision for more accuracy.
- Benchmark against different hardware architectures.
- Increase Newton-Raphson iterations for improved precision.

## License

This project is open-source and available under the MIT License.

## Author

[Your Name]


