#include <immintrin.h>
alignas(32) int A[8]{ 1, 2, 3, 1, 2, 3, 1, 2 }, B[8]{ 1, 2, 3, 4, 5, 6, 7, 8 };
alignas(32) int C[8]; // alignas(bit size of <type>) <type> var[256/(bit size)]
// Must compute "index is multiply of 256bit"(ex> short->16k, int->8k, ...)
__m256i a = _mm256_load_si256((__m256i*)A);
__m256i b = _mm256_load_si256((__m256i*)B);
__m256i c = _mm256_add_epi32(a, b);
void _mm256_store_si256((__m256i*)C, c);
// d : double precision(64-bit), s : single precision(32-bit), i : integer
__m256i _mm256_abs_epi32 (__m256i a)
__m256i _mm256_set1_epi32 (int a) // set all elements to a
__m256i _mm256_and_si256 (__m256i a, __m256i b)
__m256i _mm256_setzero_si256 (void)
__m256d _mm256_add_pd(__m256d a, __m256d b) // double precision(64-bit)
__m256d _mm256_sub_pd(__m256 a, __m256 b) // double precision(64-bit)
__m256d _mm256_addsub_pd(__m256d m1, __m256d m2) // a0-b0,a1+b1,...
__m256d _mm256_andnot_pd (__m256d a, __m256d b) // (~a)&b
__m256i _mm256_avg_epu16 (__m256i a, __m256i b) // unsigned, (a+b+1)>>1
__m256d _mm256_ceil_pd (__m256d a)
__m256i _mm256_cmpeq_epi64 (__m256i a, __m256i b)
__m256i _mm256_cmpgt_epi16 (__m256i a, __m256i b)
__m256d _mm256_div_pd (__m256d a, __m256d b)
__m256i _mm256_max_epi32 (__m256i a, __m256i b)
__m256i _mm256_mul_epi32 (__m256i a, __m256i b)
__m256 _mm256_rcp_ps (__m256 a) // 1/a
__m256 _mm256_rsqrt_ps (__m256 a) // 1/sqrt(a)
__m256i _mm256_set1_epi64x (long long a)
__m256i _mm256_sign_epi16 (__m256i a, __m256i b) // a*(sign(b))
__m256i _mm256_sll_epi32 (__m256i a, __m128i count) // a << count
__m256d _mm256_sqrt_pd (__m256d a)
__m256i _mm256_sra_epi16 (__m256i a, __m128i count)
__m256i _mm256_xor_si256 (__m256i a, __m256i b)
void _mm256_zeroall (void)
void _mm256_zeroupper (void)
// Example codes for sum and min over [l,r) in arr[]
alignas(32) int arr[100000],tmp[8];
// sum
int ans=0;
while(l&7 && l<r)ans+=arr[l++];
while(r&7 && l<r)ans+=arr[--r];
__m256i sum=_mm256_setzero_si256();
while(l<r){
  __m256i a=_mm256_load_si256((__m256i*)(arr+l));
  sum=_mm256_add_epi32(sum,a);
  l+=8;
}
_mm256_store_si256((__m256i*)tmp,sum);
for(j=8;j;)ans+=tmp[--j];
// min
int ans=1e9;
while(l&7&&l<r)ans=min(ans,arr[l++]);
while(r&7&&l<r)ans=min(ans,arr[--r]);
__m256i minv=_mm256_set1_epi32(1e9);
while(l<r){
  __m256i v=_mm256_load_si256((__m256i*)(arr+l));
  minv=_mm256_min_epi32(minv,v);
  l+=8;
}
_mm256_store_si256((__m256i*)tmp, minv);
ans=min(ans,*min_element(tmp,tmp+8));