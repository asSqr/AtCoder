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

std::string N;
ll K;
std::map<ll, ll> dp[20][2][2];
ll dp2[20][2][2][2];

int main() {
  std::cin >> N >> K;

  ll n = N.size();

  dp[0][0][1][1] = 1;
  dp2[0][0][0][0] = 1;

  ll ans = 0;

  rep( i, n ) {
    ll num = N[i]-'0';

    rep( smaller, 2 ) rep( zero, 2 ) itr( it, dp[i][smaller][zero] ) rep( d, smaller?10:num+1 ) if( (zero ? 1 : it->first*d) <= K ) {
      dp[i+1][smaller || d < num][zero && !d][(zero && !d) ? 1 : it->first*d] += it->second;

      if( i+1 == n && !(zero && !d) && ((zero && !d) ? 1 : it->first*d) && ((zero && !d) ? 1 : it->first*d) <= K )
        ans += it->second;
    }

    rep( smaller, 2 ) rep( zero, 2 ) rep( nzero, 2 ) rep( d, smaller?10:num+1 ) {
      dp2[i+1][smaller || d < num][zero || (nzero && !d)][!nzero && d ? 1 : nzero ? 1 : 0] += dp2[i][smaller][zero][nzero];
    }
  }

  /*rep( smaller, 2 ) repi( k, 1, K+1 ) {
    ans += dp[n][smaller][0][k];
    // printf( "dp[%lld][%lld][%lld][%lld] = %lld\n", n, smaller, zero, k, dp[n][smaller][zero][k]);
  }*/

  rep( smaller, 2 ) {
    ans += dp2[n][smaller][1][1]; 
    // printf( "dp2[%lld][%lld][%lld][%lld] = %lld\n", n, smaller, 1, 1, dp2[n][smaller][1][1]);
  }

  std::cout << ans << endl;

  return 0;
}