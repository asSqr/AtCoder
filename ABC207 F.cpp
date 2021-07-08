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
mint dp[2010][2010][3];
ll subtree[2010];

ll dfs( ll v, ll p = -1 ) {
  std::vector<std::vector<mint>> ndp( 2010, std::vector<mint>( 3, 0 ) );
  std::vector<mint> sdp( 2010, 1 ), pdp( 2010, 1 );
  std::vector<std::vector<bool>> used( 2010, std::vector<bool>( 3, false ) );

  ndp[0][0] = ndp[1][2] =  1;
  sdp[0] = pdp[0] = 1;

  ll sum = 0;

  subtree[v] = 1;

  if( G[v].size() > 1 ) {
    rep( j, N+1 ) rep( k, 3 )
      ndp[j][k] = 1;
  }

  used[0][0] = used[1][2] = true;

  for( auto u : G[v] ) if( u != p ) {
    subtree[v] += dfs(u, v);

    rep( j, sum+1 ) rep( k, subtree[u]+1 ) {
      ndp[j+k+1][2] *= dp[u][k][0]*ndp[j][2];
      used[j+k+1][2] = true;
      ndp[j][2] *= ndp[j][2]*(dp[u][k][1]+dp[u][k][2]);
      used[j][2] = true;
      ndp[j+k][0] *= dp[u][k][0]*ndp[j][0];
      used[j+k][0] = true;
      
    }

    sum += subtree[u];
  }

  rep( k, sum+1 )
    ndp[k][1] = 0;

  rep( j, sum+1 ) rep( k, 3 ) if( !used[j][k] )
    ndp[j][k] = 0;

  rep( k, sum+1 ) {
    ndp[k+1][1] = sdp[k]-pdp[k];

    printf( "dp[%lld][%lld][%lld]: %lld - %lld\n", v, k+1, 1, sdp[k].x, pdp[k].x );
  }

  rep( j, subtree[v]+1 ) rep( k, 3 )
    dp[v][j][k] = ndp[j][k];

  return subtree[v];
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

  dfs( 0 );

  rep( i, N ) rep( j, subtree[i]+1 ) rep( k, 3 )
    printf( "dp[%lld][%lld][%lld] = %lld\n", i, j, k, dp[i][j][k].x );

  rep( j, N+1 ) {
    mint ans = 0;

    rep( k, 3  )
      ans += dp[0][j][k];

    std::cout << ans.x << endl;
  }

  return 0;
}