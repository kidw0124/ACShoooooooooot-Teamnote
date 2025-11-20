struct sieve {
  const ll MAXN = 101010;
  vector<ll> sp, e, phi, mu, tau, sigma, primes;
  // sp : smallest prime factor, e : exponent, phi : euler phi, mu : mobius
  // tau : num of divisors, sigma : sum of divisors
  sieve(ll sz):sp(sz+1),e(sz+1),phi(sz+1),mu(sz+1),tau(sz+1),sigma(sz+1) {
    phi[1] = mu[1] = tau[1] = sigma[1] = 1;
    for (ll i = 2; i <= sz; i++) {
      if (!sp[i]) {
        primes.push_back(i), e[i] = 1, phi[i] = i - 1, mu[i] = -1, tau[i] = 2, sigma[i] = i + 1;
      }
      for (auto j : primes) {
        if (i * j > sz) break;
        sp[i * j] = j;
        if (i % j == 0) {
          e[i * j] = e[i] + 1, phi[i * j] = phi[i] * j, mu[i * j] = 0,
                tau[i * j] = tau[i] / e[i * j] * (e[i * j] + 1),
                sigma[i * j] = sigma[i] * (j - 1) / (powm(j, e[i * j]) - 1) *
                               (powm(j, e[i * j] + 1) - 1) / (j - 1);
          break;
        }
        e[i * j] = 1, phi[i * j] = phi[i] * phi[j], mu[i * j] = mu[i] * mu[j],
              tau[i * j] = tau[i] * tau[j], sigma[i * j] = sigma[i] * sigma[j];
      }
    }
  }
  sieve() : sieve(MAXN) {}
};