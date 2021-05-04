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
#include <atcoder/all>
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

using mint = atcoder::modint;

ll p;
ll a[3010];
mint b[3010];
mint po[3010][3010];
mint fact[3010], inv[3010];

mint comb( ll n, ll r ) {
  if( n < r )
    return 0;
  if( n < 0 )
    return 0;
  if( r < 0 )
    return 0;

  return fact[n]*inv[n-r]*inv[r];
}

int main() {
  std::cin >> p;

  mint::set_mod(p);

  rep( i, p )
    std::cin >> a[i];

  rep( i, p ) {
    po[i][0] = 1;

    rep( j, p ) 
      po[i][j+1] = po[i][j]*i;
  }

  fact[0] = 1;

  rep( i, p+5 )
    fact[i+1] = fact[i]*(i+1);

  inv[0] = 1;

  rep( i, p-1 )
    inv[i+1] = inv[i]*mint(i+1).inv();

  rep( i, p ) {
    ll sgn = (p-1)&1 ? -1 : 1;
    
    rep( k, p ) {
      b[k] += -comb(p-1,k)*a[i]*sgn*po[i][p-1-k];
      sgn *= -1;
    }

    b[0] += a[i];
  }

  rep( i, p )
    std::cout << b[i].val() << (i==p-1?'\n':' ');

  return 0;
}