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

<<<<<<< HEAD
int main() {
=======
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
  mint& operator*=(const mint a) {
    (x *= a.x) %= mod;
    return *this;
  }
  mint operator+(const mint a) const {
    mint res(*this);
    return res+=a;
  }
  mint operator-(const mint a) const {
    mint res(*this);
    return res-=a;
  }
  mint operator*(const mint a) const {
    mint res(*this);
    return res*=a;
  }
  mint pow(ll t) const {
    if (!t) return 1;
    mint a = pow(t>>1);
    a *= a;
    if (t&1) a *= *this;
    return a;
  }

  // for prime mod
  mint inv() const {
    return pow(mod-2);
  }
  mint& operator/=(const mint a) {
    return (*this) *= a.inv();
  }
  mint operator/(const mint a) const {
    mint res(*this);
    return res/=a;
  }
};

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
std::vector<ll> G[2010];
// 0: not covered, 1: covered but not put, 2: covered and put
using vm = std::vector<mint>;
using vvm = std::vector<vm>;

vvm dfs( ll v, ll p = -1 ) {
  vvm dp(2, vm(3));
  dp[0][0] = dp[1][2] = 1;

  for( auto u : G[v] ) if( u != p ) {
    auto dp_u = dfs(u, v);

    ll nu = dp_u.size()-1;
    ll nv = dp.size()-1;

    vvm dp_v(nu+nv+2, vm(3));
    std::swap(dp, dp_v);

    rep( vi, nv+1 ) rep( vj, 3 ) rep( ui, nu+1 ) rep( uj, 3 ) {
      mint prod = dp_v[vi][vj]*dp_u[ui][uj];

      ll i = vi+ui, j;

      if( vj == 0 && uj != 2 ) {
        j = 0;
      } else if( vj == 2 ) {
        j = 2;
      } else {
        j = 1;
      }

      if( vj == 0 && uj == 2 ) {
        ++i;
      }
      if( vj == 2 && uj == 0 ) {
        ++i;
      }

      dp[i][j] += prod;
    } 
  }

  return dp;
}

int main() {
  std::cin >> N;

  rep( i, N-1 ) {
    ll u, v;
    std::cin >> u >> v;
    --u; --v;

    G[u].emplace_back(v);
    G[v].emplace_back(u);
  }

  auto dp = dfs( 0 );

  rep( j, N+1 ) {
    mint ans = 0;

    rep( k, 3 )
      ans += dp[j][k];

    std::cout << ans.x << endl;
  }
>>>>>>> d1b183a7884b6d60fea5f1e5108d0c9b5fbf5bfb

  return 0;
}