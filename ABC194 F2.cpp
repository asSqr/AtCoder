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

std::string n;
ll K;

ll dig( char ch ) {
  if( ch >= '0' && ch <= '9' )
    return ch-'0';
  else
    return ch-'A'+10;
}

mint dp[200010][2][2][20];

int main() {
  std::cin >> n >> K;

  ll N = n.size();

  dp[0][0][0][0] = 1;

  ll bit = 0;

  rep( i, N ) rep( smaller, 2 ) rep( nzero, 2 ) rep( k, K+1 ) {
    ll x = dig(n[i]);

    if( !nzero ) {
      if( !k )
        dp[i+1][smaller || x > 0][0][k] += dp[i][smaller][nzero][k];

      ll ub = smaller?15:x;

      if( ub > 0 ) {
        if( ub > 1 )
          dp[i+1][1][1][1] += dp[i][smaller][nzero][k]*(ub-1);
        
        dp[i+1][smaller][1][1] += dp[i][smaller][nzero][k];
      }
    } else {
      if( !smaller ) {
        // <x
        ll cnt = __builtin_popcountll(bit&((1ll<<x)-1));

        dp[i+1][1][1][k] += dp[i][smaller][nzero][k]*cnt;
        dp[i+1][1][1][k+1] += dp[i][smaller][nzero][k]*(x-cnt);

        ll nk = __builtin_popcountll(bit|1ll<<x);
        
        dp[i+1][0][1][nk] += dp[i][smaller][nzero][k];
      } else {
        dp[i+1][smaller][1][k] += dp[i][smaller][nzero][k]*k;
        dp[i+1][smaller][1][k+1] += dp[i][smaller][nzero][k]*(16-k);
      }
    }

    bit |= 1ll<<x;
  }

  mint ans = 0;

  rep( smaller, 2 ) {
    ans += dp[N][smaller][1][K];

    //printf( "dp[%lld][%lld][%lld][%lld] = %lld\n", N, smaller, 1, K, dp[N][smaller][1][K].x );
  }

  std::cout << ans << endl;

  return 0;
}