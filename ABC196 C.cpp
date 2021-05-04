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
ll dp[20][2][2][20];

int main() {
  std::cin >> N;

  dp[0][0][0][0] = 1;

  rep( i, N.size() ) rep( smaller, 2 ) rep( nzero, 2 ) rep( last, N.size() ) {
    ll n = N[i]-'0';

    if( nzero && (N.size()-last)%2 == 0 && i-last >= N.size()-i ) {
      if( !smaller ) {
        ll pad = (N.size()-last)/2;

        repi( k, last, last+pad ) {
          ll d = N[k]-'0';
          ll d2 = N[k+pad]-'0';

          if( d < d2 )
            goto tend;

          if( d > d2 )
            goto lend;
        }
      }

tend:;

      dp[i+1][smaller][nzero][last] += dp[i][smaller][nzero][last];
      
lend:;
      continue;
    }

    rep( d, smaller?10:n+1 ) {
      if( !nzero && d && (N.size()-i)&1 )
        continue;

      dp[i+1][smaller || d < n][nzero || d][nzero ? last : d ? i : 0] += dp[i][smaller][nzero][last];
    }
  }

  ll ans = 0;

  rep( smaller, 2 ) rep( last, N.size() ) if( (N.size()-last)%2 == 0 )
    ans += dp[N.size()][smaller][1][last];

  std::cout << ans << endl;

  return 0;
}