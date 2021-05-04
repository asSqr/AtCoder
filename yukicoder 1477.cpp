#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <tuple>
#include <vector>
#define repi(i,a,b) for(ll i=(a);i<(b);++i)
#define rep(i,a) repi(i,0,a)
#define repdi(i,a,b) for(ll i=(a)-1;i>=(b);--i)
#define repd(i,a) repdi(i,a,0)
#define itr(it,a) for( auto it = (a).begin(); it != (a).end(); ++it )
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()
#define endl '\n'
#define debug(x) std::cerr << #x << " = " << (x) << endl;

using ll = long long;
using P = std::pair<ll, ll>;

constexpr ll INF = 1ll<<60;

template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return 1; } return 0; }

template<class S, class T>
std::ostream& operator<< ( std::ostream& out, const std::pair<S,T>& a )
{ std::cout << '(' << a.first << ", " << a.second << ')'; return out; }

template<class T>
std::ostream &operator<< ( std::ostream& out, const std::vector<T>& a )
{ std::cout << '['; rep( i, a.size() ){ std::cout << a[i]; if( i != a.size()-1 ) std::cout << ", "; } std::cout << ']'; return out; }

using namespace std;

ll N, M;
ll A[100010];
ll B[100010];
std::vector<ll> G[100010];
ll K;

// 有向グラフの接続行列 B に対し，線形方程式 Bx = c を (必要なら mod 2 で) 解くライブラリ
template<typename T>
struct LinearSystemIncidence {
  struct Edge {
    int id, to; bool fwd;
    Edge(int i, int t, bool f) : id(i), to(t), fwd(f) {}
  };
 
  int n, m;
  bool mod2;
  vector<T> x;
  vector<bool> seen;
  vector<vector<Edge>> G;
  
  LinearSystemIncidence(int n, vector<P> &E, bool mod2=false) : n(n), m(E.size()), G(n), mod2(mod2) {
    rep(i, m) {
      G[E[i].first].emplace_back(i, E[i].second, true);
      G[E[i].second].emplace_back(i, E[i].first, false);
    }
  }
 
  T dfs(vector<T> &c, int u) {
    seen[u] = true;
    T res = c[u];
    for (Edge e : G[u]) {
      if (seen[e.to]) continue;
      T tmp = dfs(c, e.to);
      if (e.fwd) x[e.id] = tmp;
      else x[e.id] = -tmp;
      res += tmp;
      if (mod2) {
        x[e.id] %= 2;
        if (x[e.id] < 0) x[e.id] += 2;
      }
    }
    if (mod2) res %= 2;
    return res;
  }
 
  pair<bool, vector<T>> solve(vector<T> &c) {
    x.assign(m, 0);
    seen.assign(n, false);
    rep(u, n) {
      if (seen[u]) continue;
      if (dfs(c, u)) return {false, vector<T>()};
    }
    return {true, move(x)};
  }
};

std::vector<P> es;

int main() {
  std::cin >> N >> M;

  rep( i, N )
    std::cin >> A[i];

  rep( i, M ) {
    ll u, v;
    std::cin >> u >> v;
    --u; --v;

    G[u].emplace_back(v);
    G[v].emplace_back(u);

    es.emplace_back(u, v);
  }

  std::cin >> K;

  rep( i, K )
    std::cin >> B[i];

  

  return 0;
}