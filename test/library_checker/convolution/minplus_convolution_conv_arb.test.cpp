#define PROBLEM \
  "https://judge.yosupo.jp/problem/min_plus_convolution_convex_arbitrary"
#include "my_template.hpp"
#include "other/io.hpp"

#include "convex/minplus_convolution_convex.hpp"

void solve() {
  LL(N, M);
  VEC(ll, A, N);
  VEC(ll, B, M);
  print(minplus_convolution<ll, 1, 0>(A, B));
}

signed main() {
  solve();
  return 0;
}