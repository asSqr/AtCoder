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

ll N;
ll a[3010];
ll dp[3010][3010];

ll rec( ll l, ll r, bool turn ) {
  if( r-l <= 0 )
    return dp[l][r] = 0;

  if( ~dp[l][r] )
    return dp[l][r];

  ll &ret = dp[l][r];

  ll x = rec(l+1,r,!turn);
  ll y = rec(l,r-1,!turn);
  
  if( !turn ) {
    if( x+a[l] > y+a[r-1] ) {
      ret = x+a[l];
    } else {
      ret = y+a[r-1];
    }
  } else {
    if( x-a[l] < y-a[r-1] ) {
      ret = x-a[l];
    } else {
      ret = y-a[r-1];
    }
  }

  return ret;
}

int main() {
  std::cin >> N;

  rep( i, N )
    std::cin >> a[i];

  rep( i, N+1 ) rep( j, N+1 )
    dp[i][j] = -1;

  rec( 0, N, false );

  std::cout << dp[0][N] << endl;

  return 0;
}