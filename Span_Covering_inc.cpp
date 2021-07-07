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

ll extgcd(ll a, ll b, ll& x, ll& y){
    ll d = a;
    if(b != 0) {
      d = extgcd(b, a%b, y, x);
      y -= (a/b) * x;
    } else {
      x = 1; y = 0;
    }

    return d;
}

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
  mint inv() const { 
    ll sx, sy;
    extgcd(x, mod, sx, sy);

    return (sx%mod + mod) % mod;
  }
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

ll N, X;
ll L[110];
mint arr[110][510][510], iarr[110][510][510];
combination comb( 10000 );
mint dp[2][510][510];

int main() {
  std::cin >> N >> X;

  rep( i, N )
    std::cin >> L[i];

  std::sort(L, L+N);

  rep( n, X+1 ) rep( s, X+1 )
    arr[0][n][s] = iarr[0][n][s] = 1;

  rep( i, N ) rep( n, X+1 ) rep( s, X+1 ) {
    arr[i+1][n][s] = arr[i][n][s] * std::max(0ll, s-(L[i]-1)*n);
    iarr[i+1][n][s] = iarr[i][n][s] / std::max(0ll, s-(L[i]-1)*n);
  }

  ll p = N-1;

  dp[0][0][0] = 1;

  for( ll x = X; x >= 1; --x ) {
    while( p >= 0 && L[p] > x )
      --p;

    ll i = (X-x)&1;
    ll ni = !i;

    rep( n, X+1 ) rep( s, X+1 )
      dp[ni][n][s] = 0;

    rep( n, (X+x)/(x+1)+1 ) rep( s, X+1 ) rep( k, X+1 ) {
      ll n2 = n+k;
      ll s2 = s+x*k;

      if( s2 > X )
        break;

      mint coef = dp[i][n][s];

      if( coef.x == 0 )
        continue;

      if( !n && p < N-1 )
        continue;
    
      if( n > 0 ) {
        coef *= iarr[p+1][n][s];
      }

      if( n2 > 0 )
        coef *= comb(n2, n) * arr[p+1][n2][s2];

      dp[ni][n2][s2] += coef;
    }

    /*rep( n, X+1 ) rep( s, X+1 )
      printf( "dp[%lld][%lld] = %lld\n", n, s, dp[ni][n][s].x );*/
  }

  mint ans = 0;

  ll ni = X&1;

  repi( n, 1, X+1 ) repi( s, 1, X+1 ) {
    ans += dp[ni][n][s] * comb( X-s+1, n ) * ((X-s)&1 ? -1 : 1);    
  }

  std::cout << ans.x << endl;

  return 0;
}