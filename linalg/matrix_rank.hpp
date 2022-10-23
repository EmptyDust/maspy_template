template <typename T>
int matrix_rank(vc<vc<T>> a) {
  auto n = len(a), m = len(a[0]);
  int rk = 0;
  FOR(j, m) {
    if (a[rk][j] == 0) {
      FOR3(i, rk + 1, n) if (a[i][j] != 0) {
        swap(a[rk], a[i]);
        break;
      }
    }
    if (a[rk][j] == 0) continue;
    T c = T(1) / a[rk][j];
    FOR(k, j, m) a[rk][k] *= c;
    FOR(i, rk + 1, n) {
      T c = a[i][j];
      FOR3(k, j, m) { a[i][k] -= a[rk][k] * c; }
    }
    ++rk;
    if (rk == n) break;
  }
  return rk;
}
