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

const ll mod = 998244353;
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

ll S;

mint comb( ll n, ll r ) {
  if( r < 0 || n < r ) 
    return 0;

  mint x = n;
  mint ret = 1;

  rep( j, r ) {
    ret *= x;
    x -= 1;
    ret /= j+1;
  }

  return ret;
}

int main() {
  std::cin >> S;

  S -= 6;

  mint ans = 0;
  
  // 1, 1, 1, 1, 1, 1 (1)
  {
    ans += comb(S+5, 5);
  }

  // 1, 1, 4 (6)
  {
    rep( r1, 4 ) rep( r2, 4 ) {
      ll M = S-r1-r2;

      if( M%4 )
        continue;

      ans += comb(M/4+2, 2)*6;
    }
  }

  // 1, 1, 2, 2 (3)
  {
    rep( r1, 2 ) rep( r2, 2 ) {
      ll M = S-r1-r2;

      if( M%2 )
        continue;

      ans += comb(M/2+3, 3)*3;
    }
  }

  // 3, 3 (8)
  {
    if( S%3 == 0 ) {
      ans += comb(S/3+1, 1)*8;
    }
  }

  // 2, 2, 2 (6)
  {
    if( S%2 == 0 ) {
      ans += comb(S/2+2, 2)*6;
    }
  }

  ans /= 24;

  std::cout << ans << endl;

  return 0;
}