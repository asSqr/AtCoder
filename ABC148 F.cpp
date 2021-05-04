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

template<typename T> // T: type of cost
struct lca {
  int n, root, l;
  vector<vector<int>> to;
  vector<vector<T>> co;
  vector<int> dep;
  vector<T> costs;
  vector<vector<int>> par;
  lca(int n):n(n),to(n),co(n),dep(n),costs(n) {
    l = 0;
    while ((1<<l) < n) ++l;
    par = vector<vector<int>>(n+1,vector<int>(l,n));
  }
  void addEdge(int a, int b, T c=0) {
    to[a].push_back(b); co[a].push_back(c);
    to[b].push_back(a); co[b].push_back(c);
  }
  void dfs(int v, int d=0, T c=0, int p=-1) {
    if (p != -1) par[v][0] = p;
    dep[v] = d;
    costs[v] = c;
    for (int i = 0; i < to[v].size(); ++i) {
      int u = to[v][i];
      if (u == p) continue;
      dfs(u, d+1, c+co[v][i], v);
    }
  }

  void init(int _root=0) {
    root = _root;
    dfs(root);
    for (int i = 0; i < l-1; ++i) {
      for (int v = 0; v < n; ++v) {
        par[v][i+1] = par[par[v][i]][i];
      }
    }
  }
  // LCA
  int operator()(int a, int b) {
    if (dep[a] > dep[b]) swap(a,b);
    int gap = dep[b]-dep[a];
    for (int i = l-1; i >= 0; --i) {
      int len = 1<<i;
      if (gap >= len) {
        gap -= len;
        b = par[b][i];
      }
    }
    if (a == b) return a;
    for (int i = l-1; i >= 0; --i) {
      int na = par[a][i];
      int nb = par[b][i];
      if (na != nb) a = na, b = nb;
    }
    return par[a][0];
  }
  int length(int a, int b) {
    int c = (*this)(a,b);
    return dep[a]+dep[b]-dep[c]*2;
  }
  T dist(int a, int b) {
    int c = (*this)(a,b);
    return costs[a]+costs[b]-costs[c]*2;
  }
};

ll N;
std::vector<ll> G[100010];
ll u, v;
ll b[100010], dep[100010];

ll dfs( ll v, ll d, ll p = -1 ) {
  dep[v] = d;

  for( auto u : G[v] ) if( u != p )
    chmax( b[v], dfs( u, d+1, v )+1 );

  return b[v];
}

int main() {
  std::cin >> N >> u >> v;
  lca<ll> lc(N);
  --u; --v;

  rep( i, N-1 ) {
    ll A, B;
    std::cin >> A >> B;
    --A; --B;

    G[A].emplace_back(B);
    G[B].emplace_back(A);
    lc.addEdge(A, B, 1);
  }

  dfs( v, 0 );
  lc.init(v);

  ll dis = lc.dist(u,v);
  ll de = b[u];

  ll turn = de&1;
  ll ans = de;

  if( de&1 ) {
    ++dis;
  }

  if( dis != 1 ) {
    if( turn == 1 && dis%2 == 0 )
      ans += dis==2?1:2*dis-5;
    else
      ans += dis==2?1:2*dis-4;
  } else {
    ans = 0;
  }

  std::cout << ans/2 << endl;

  return 0;
}