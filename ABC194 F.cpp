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

combination comb( 200010 );
mint inc[20][200010], po[20][200010];

int main() {
  std::cin >> n >> K;

  ll N = n.size();

  rep( i, 20 ) {
    po[i][0] = 1;

    rep( j, N+5 )
      po[i][j+1] = po[i][j]*i;
  }

  rep( a, K+1 ) rep( b, N+1 ) {
    /*mint sign = 1;

    repi( k, K-a, 16-a+1 ) {
      inc[a][b] += sign*comb(b,k)*comb(16-a,k)*po[16][b-k];
      sign *= -1; 
    }*/

    repi( k, a, K+1 ) {
      inc[a][b] += comb(K-a, k-a)*po[k][b]*((K-k)&1 ? -1 : 1);
    }

    inc[a][b] *= comb(16-a, K-a);
  }

  ll bit = 0;
  mint ans = 0;

  rep( i, N ) {
    ll x = dig(n[i]);
    ll k = __builtin_popcountll(bit&((1ll<<x)-1));
    ll l = __builtin_popcountll(bit);

    bit |= 1ll<<x;

    if( !i ) {
      --x;

      if( bit&1 )
        --k;
    }

    ans += inc[l][N-i-1]*k;
    ans += inc[l+1][N-i-1]*(x-k);

    if( i )
      ans += inc[1][i-1]*15;
  }

  if( __builtin_popcountll(bit) == K )
    ans += 1;

  std::cout << ans << endl;

  return 0;
}