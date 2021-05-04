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

ll K;
ll R[2048];
double dp[11][1030][1030];

double f( ll p, ll q ) {
  return 1.0 / (1.0 + pow(10.0, (R[q]-R[p])/400.0));
}

int main() {
  std::cin >> K;

  rep( i, 1ll<<K )
    std::cin >> R[i];

  rep( j, 1ll<<K )
    dp[0][j][j] = 1.0;

  rep( i, K ) rep( j, 1ll<<(K-i-1) ) rep( k, 1ll<<i ) rep( l, 1ll<<i ) {
    ll base = (1ll<<(i+1))*j;
    ll p1 = base+k;
    ll p2 = base+(1ll<<i)+l;

    dp[i+1][j][p1] += dp[i][(j<<1)][p1]*dp[i][(j<<1)+1][p2]*f(p1,p2);
    dp[i+1][j][p2] += dp[i][(j<<1)][p1]*dp[i][(j<<1)+1][p2]*f(p2,p1);
  }

  rep( i, 1ll<<K )
    printf( "%.12f\n", dp[K][0][i] );

  return 0;
}