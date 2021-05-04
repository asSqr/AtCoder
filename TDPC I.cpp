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

std::string s;
ll dp[310][310];

ll f( ll l, ll r ) {
  ll &ret = dp[l][r];

  if( ~ret )
    return ret;

  if( r-l <= 2 )
    return ret = 0;

  if( r-l == 3 && s[l] == 'i' && s[l+1] == 'w' && s[l+2] == 'i' )
    return ret = 3;

  ret = 0;

  repi( k, l+1, r ) {
    chmax( ret, f(l,k)+f(k,r) );

    if( s[l] == 'i' && s[k] == 'w' && s[r-1] == 'i' && f(l+1,k) == (k-(l+1)) && f(k+1,r-1) == (r-1-(k+1)) ) {
      chmax( ret, (k-(l+1)) + (r-1-(k+1)) + 3 );
    }
  }

  return ret;
}

int main() {
  std::cin >> s;

  ll n = s.size();

  rep( i, n+1 ) rep( j, n+1 )
    dp[i][j] = -1;

  std::cout << f(0,n)/3 << endl;

  return 0;
}