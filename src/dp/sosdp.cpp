//iterative version O(N*2^N) with TC, MC
for(int mask = 0; mask < (1<<N); ++mask){
  dp[mask][-1] = A[mask];  //handle base case separately (leaf states)
  for(int i = 0;i < N; ++i){
    if(mask & (1<<i)) dp[mask][i] = dp[mask][i-1] + dp[mask^(1<<i)][i-1];
    else dp[mask][i] = dp[mask][i-1];
  }
  F[mask] = dp[mask][N-1];
}
// toggling, O(N*2^N) with TC, O(2^N) with MC
for(int i = 0; i<(1<<N); ++i) F[i] = A[i];
for(int i = 0;i < N; ++i) for(int mask = 0; mask < (1<<N); ++mask){
  if(mask & (1<<i)) F[mask] += F[mask^(1<<i)];
}