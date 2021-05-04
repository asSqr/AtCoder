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

const ll mod = 1000000007;
struct mint {
  ll x; // typedef long long ll;
  mint(ll x=0):x((x%mod+mod)%mod){}
  mint operator-() const { return mint(-x);}
  mint& operator+=(const mint a) {
    if ((x += a.x) >= mod) x -= mod;
    return *this;
  }
  mint& operator-=(const mint a) {
    if ((x += mod-a.x) >= mod) x -= mod;
    return *this;
  }
  mint& operator*=(const mint a) { (x *= a.x) %= mod; return *this;}
  mint operator+(const mint a) const { return mint(*this) += a;}
  mint operator-(const mint a) const { return mint(*this) -= a;}
  mint operator*(const mint a) const { return mint(*this) *= a;}
  mint pow(ll t) const {
    if (!t) return 1;
    mint a = pow(t>>1);
    a *= a;
    if (t&1) a *= *this;
    return a;
  }

  // for prime mod
  mint inv() const { return pow(mod-2);}
  mint& operator/=(const mint a) { return *this *= a.inv();}
  mint operator/(const mint a) const { return mint(*this) /= a;}
};
std::istream& operator>>(std::istream& is, mint& a) { return is >> a.x;}
std::ostream& operator<<(std::ostream& os, const mint& a) { return os << a.x;}

struct combination {
  std::vector<mint> fact, ifact;
  combination(int n):fact(n+1),ifact(n+1) {
    assert(n < mod);
    fact[0] = 1;
    for (int i = 1; i <= n; ++i) fact[i] = fact[i-1]*i;
    ifact[n] = fact[n].inv();
    for (int i = n; i >= 1; --i) ifact[i-1] = ifact[i]*i;
  }
  mint operator()(int n, int k) {
    if (k < 0 || k > n) return 0;
    return fact[n]*ifact[k]*ifact[n-k];
  }
};

ll N;
std::vector<ll> G[200010];

P dfs( ll v, ll d = 0, ll p = -1 ) {
  P ret( d, v );
  
  for( auto u : G[v] ) if( u != p ) {
    chmax( ret, dfs( u, d+1, v ) );
  }

  return ret;
}

std::vector<ll> bfs( ll s ) {
  std::vector<ll> dist(N, INF);

  std::queue<ll> que;
  que.emplace(s);
  dist[s] = 0;

  while( !que.empty() ) {
    ll v = que.front(); que.pop();

    for( auto u : G[v] ) if( dist[u] == INF ) {
      que.emplace(u);
      dist[u] = dist[v]+1;
    }
  }

  return dist;
}

mint two[200010];

int main() {
  std::cin >> N;

  rep( i, N-1 ) {
    ll a, b;
    std::cin >> a >> b;
    --a; --b;

    G[a].emplace_back(b);
    G[b].emplace_back(a);
  }

  ll s = dfs(0).second;
  ll t = dfs(s).second;

  std::vector<ll> ds = bfs(s), dt = bfs(t);

  two[0] = 1;
  rep( i, N+5 )
    two[i+1] = two[i]*2;

  mint ans = two[N-1]*ds[t];

  //std::cout << ds << endl;
  //std::cout << dt << endl;

  ll lb = 0;
  rep( i, N ) {
    chmax( lb, std::min(ds[i], dt[i]) );
  }

  //std::cout << lb << endl;

  std::vector<mint> fac(N, 1);

  rep( i, N ) {
    if( i == s || i == t )
      continue;

    ll ma = std::max(ds[i], dt[i]);
    fac[std::max(lb,ma)] *= 2;
  }

  //std::cout << fac << endl;

  // <1 ... <lb
  ans += two[N-1]*lb;

  // <lb+1 ... <N (each <i+1)
  mint prod = 1;
  repi( i, lb, N ) {
    prod *= fac[i];
    ans += (two[N-2]-prod)*2;
  }

  std::cout << ans << endl;

  return 0;
}