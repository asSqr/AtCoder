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

ll T;
bool sdp[10][100];
bool dp[30][20][20];

bool solve( const std::string &N, ll K ) {
  ll n = N.size();

  ll car = 0;

  rep( i, n+5 ) rep( j, 5 ) rep( rest, K+5 )
    dp[i][j][rest] = false;

  dp[0][0][K] = true;

  rep( i, n ) rep( j, 4 ) rep( rest, K+1 ) {
    ll d = N[n-1-i]-'0';

    rep( rest2, rest+1 ) rep( k, 4 ) if( d-j+10*k >= 0 ) {
      if( i+1 != n && !rest2 )
        continue;

      dp[i+1][k][rest2] |= dp[i][j][rest] & sdp[rest2][d-j+10*k];

      /*if( dp[i][j][rest] & sdp[rest2][d-j+10*k] ) {
        printf( "dp[%lld][%lld][%lld] |= dp[%lld][%lld][%lld] & sdp[%lld][%lld]\n", i+1, k, rest2, i, j, rest, rest2, d-j+10*k );
      }*/
    }
  }

  rep( rest, K+1 ) if( dp[n][0][rest] ) {
    // printf( "dp[%lld][%lld][%lld] = %lld\n", n, 0, rest, dp[n][0][rest] );

    return true;
  }

  return false;
}

int main() {
  std::cin >> T;

  sdp[0][0] = true;

  rep( i, 10 ) rep( j, 40 ) {
    repi( d, 1, 4 )
      sdp[i+1][j+d] |= sdp[i][j];
  }

  rep( t, T ) {
    std::string N;
    std::cin >> N;

    repi( K, 1, 10 ) {
      bool fl = solve(N, K);

      if( fl ) {
        std::cout << K << endl;

        goto end;
      }
    }

end:;
  }

  return 0;
}