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

ll r1o, c1o, r2, c2;

bool f( ll r1, ll c1, ll r2, ll c2 ) {
  return llabs(r1-r2)+llabs(c1-c2) <= 3;
}

int main() {
  std::cin >> r1o >> c1o >> r2 >> c2;

  ll ans = r1o==r2&&c1o==c2?0:INF;

  rep( i, 4 ) rep( j, 4 ) {
    if( i+j > 3 )
      continue;

    ll r1 = r1o+i, c1 = c1o+j;
    
    if( f(r1,c1,r2,c2) ) {
      chmin( ans, 1ll+(i||j?1:0) );
    }

    ll x = 1+(llabs(r1+c1-r2-c2)+2)/3;
    ll y = 1+(llabs(r1-c1+r2-c2)+2)/3;
    ll z = 1+(llabs(r1+c1-c2-r2)+2)/3;
    ll w = 1+(llabs(r1-c1+c2-r2)+2)/3;

    ll mi = std::min({x,y,z,w});

    ll a = r1+r2-c1+c2, b = r2+c2-r1+c1;

    if( a%2 == 0 && b%2 == 0 ) {
      chmin( ans, 2ll+(i||j?1:0) );
    }

    chmin( ans, mi+(i||j?1:0) );
  }

  std::cout << ans << endl;

  return 0;
}