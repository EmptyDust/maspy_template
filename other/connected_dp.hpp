namespace connected_dp {
// pair<新しい状態、今の成分 → 新しい成分>
vc<pair<vc<int>, vc<int>>> next_states(const vc<int>& now) {
  int N = len(now);
  vc<pair<vc<int>, vc<int>>> res;
  FOR(s, 1 << N) {
    vc<int> par(N + N);
    FOR(i, N) par[i] = (s & 1 << i ? i : -1);
    FOR(i, N) par[N + i] = (now[i] == -1 ? -1 : now[i] + N);
    auto find = [&](int x) -> int {
      while (par[x] != x) { x = par[x] = par[par[x]]; }
      return x;
    };
    auto merge = [&](int a, int b) -> void {
      a = find(a), b = find(b);
      if (a == b) return;
      if (a > b) swap(a, b);
      par[b] = a;
    };

    FOR(i, N - 1) if (par[i] != -1 && par[i + 1] != -1) merge(i, i + 1);
    FOR(i, N) if (par[i] != -1 && par[N + i] != -1) merge(i, N + i);
    FOR(i, N + N) if (par[i] != -1) par[i] = find(i);
    FOR(i, N, N + N) if (par[i] >= N) par[i] = -1;
    res.eb(vc<int>(par.begin(), par.begin() + N),
           vc<int>(par.begin() + N, par.end()));
  }
  return res;
}

vc<int> reverse_state(const vc<int>& now) {
  int N = len(now);
  vc<int> max_i(N, -1);
  FOR(i, N) if (now[i] != -1) max_i[now[i]] = i;
  vc<int> rev(N, -1);
  FOR(i, N) {
    if (now[i] == -1) continue;
    int x = max_i[now[i]];
    rev[N - 1 - i] = N - 1 - x;
  }
  return rev;
}

// 0, 1 ：空の列、領域の手前、後ろ
// 連結領域をひとつ作る。多角形とは限らない。
pair<vvc<int>, vc<pair<int, int>>> connedted_dp_graph(int N,
                                                      bool merge_reverse) {
  static HashMapLL<int> MP;
  MP.reset();
  vvc<int> states;
  vc<pair<int, int>> edges;

  states.eb(vc<int>(N, -1));
  states.eb(vc<int>(N, -1));
  MP[hash_vector<int>(states[0])] = 0;

  int p = -1;
  while (1) {
    if (++p == len(states)) break;
    if (p == 1) {
      edges.eb(1, 1);
      continue;
    }
    vc<int> now = states[p];
    for (auto&& [nxt, convert]: connected_dp::next_states(now)) {
      // 今の成分数、消える成分数
      int a = 0, b = 0;
      FOR(v, N) if (now[v] == v) {
        ++a;
        if (convert[v] == -1) ++b;
      }
      // 消える成分があってよいのは、終状態にいくときのみ
      if (b >= 2) continue;
      if (b == 1) {
        if (MAX(nxt) != -1) continue;
        edges.eb(p, 1);
        continue;
      }
      ll h = hash_vector<int>(nxt);
      if (merge_reverse) {
        chmin(h, hash_vector<int>(connected_dp::reverse_state(nxt)));
      }
      if (!MP.count(h)) {
        MP[h] = len(states);
        states.eb(nxt);
      }
      edges.eb(p, MP[h]);
    }
  }
  return {states, edges};
}

} // namespace connected_dp