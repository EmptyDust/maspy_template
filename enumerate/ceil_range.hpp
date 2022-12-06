// f(q, l, r)：ceil が q になる範囲が [l, r)
// q == 1 のときには r == INF が入ることに注意
template <typename F>
void ceil_range(ll N, F f, ll INF) {
  ll q = 1, l = N, r = INF;
  while (1) {
    f(q, l, r);
    if (q == N) break;
    q = ceil(N, ceil(N, q) - 1);
    l = ceil(N, q);
    r = ceil(N, q - 1);
  }
}
