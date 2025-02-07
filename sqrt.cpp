#include <immintrin.h> // For AVX intrinsics

extern "C" void fastsqrt(const float *in, float *out, unsigned count) {
  constexpr int MAGIC_NUMBER =
      0x1fbd1df5;               // Tuned magic number for single precision
  constexpr int SIMD_WIDTH = 8; // AVX processes 8 floats at a time
  unsigned i = 0;

  // SIMD loop: process 8 elements at a time
  for (; i + SIMD_WIDTH <= count; i += SIMD_WIDTH) {
    // Load 8 floats from the input array
    __m256 nums0 = _mm256_loadu_ps(&in[i]);

    // Bit manipulation to compute the initial guess
    __m256i bits = _mm256_castps_si256(nums0); // Cast to integer
    bits = _mm256_srli_epi32(bits, 1); // Right shift to halve the exponent
    bits = _mm256_add_epi32(
        bits, _mm256_set1_epi32(MAGIC_NUMBER));  // Add magic number
    __m256 guesses0 = _mm256_castsi256_ps(bits); // Cast back to float

    // Unrolled Newton's method iterations
    __m256 guess_sq, diff, divisor;
    // Iteration 1
    guess_sq = _mm256_mul_ps(guesses0, guesses0);
    diff = _mm256_sub_ps(guess_sq, nums0);
    divisor = _mm256_mul_ps(_mm256_set1_ps(2.0f), guesses0);
    guesses0 = _mm256_sub_ps(guesses0, _mm256_div_ps(diff, divisor));

    // Iteration 2
    guess_sq = _mm256_mul_ps(guesses0, guesses0);
    diff = _mm256_sub_ps(guess_sq, nums0);
    divisor = _mm256_mul_ps(_mm256_set1_ps(2.0f), guesses0);
    guesses0 = _mm256_sub_ps(guesses0, _mm256_div_ps(diff, divisor));

    // Store results back to the output array
    _mm256_storeu_ps(&out[i], guesses0);
  }

  // Scalar loop for remaining elements
  for (; i < count; ++i) {
    float num = in[i];

    // Bit manipulation for initial guess
    int bits = *reinterpret_cast<const int *>(&num);
    bits = (bits >> 1) + MAGIC_NUMBER;
    float guess = *reinterpret_cast<float *>(&bits);

    // Unrolled Newton's method iterations
    // Iteration 1
    float guess_sq = guess * guess;
    float diff = guess_sq - num;
    float divisor = 2.0f * guess;
    guess -= diff / divisor;

    // Iteration 2
    guess_sq = guess * guess;
    diff = guess_sq - num;
    divisor = 2.0f * guess;
    guess -= diff / divisor;

    out[i] = guess;
  }
}
