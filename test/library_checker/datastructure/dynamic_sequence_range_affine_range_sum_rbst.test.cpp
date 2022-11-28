#define PROBLEM \
  "https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum"
#include "my_template.hpp"
#include "other/io.hpp"

#include "alg/acted_monoid/cntsum_affine.hpp"
#include "mod/modint.hpp"
#include "ds/bbst/rbst_acted_monoid.hpp"

using mint = modint998;

void solve() {
  LL(N, Q);
  VEC(mint, A, N);
  RBST_ActedMonoid<ActedMonoid_CntSum_Affine<mint>> X;
  vc<pair<mint, mint>> seg_raw(N);
  FOR(i, N) seg_raw[i] = {mint(1), A[i]};
  auto root = X.new_node(seg_raw);

  FOR(Q) {
    LL(t);
    if (t == 0) {
      LL(i, x);
      auto [a, b] = X.split(root, i);
      root = X.merge3(a, X.new_node({mint(1), mint(x)}), b);
    }
    if (t == 1) {
      LL(i);
      auto [a, b, c] = X.split3(root, i, i + 1);
      root = X.merge(a, c);
    }
    if (t == 2) {
      LL(l, r);
      root = X.reverse(root, l, r);
    }
    if (t == 3) {
      LL(l, r, b, c);
      root = X.apply(root, l, r, {mint(b), mint(c)});
    }
    if (t == 4) {
      LL(l, r);
      print(X.prod(root, l, r).se);
    }
  }
}

signed main() {
  solve();

  return 0;
}
