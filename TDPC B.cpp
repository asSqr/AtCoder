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

ll A, B;
ll a[1010], b[1010];
ll Sa[1010], Sb[1010];
ll dp[1010][1010];

int main() {
  std::cin >> A >> B;

  rep( i, A )
    std::cin >> a[i];

  rep( i, A )
    Sa[i+1] = Sa[i]+a[A-1-i];

  rep( i, B )
    std::cin >> b[i];

  rep( i, B )
    Sb[i+1] = Sb[i]+b[B-1-i];

  dp[0][0] = 0;

  rep( i, A+1 ) rep( j, B+1 ) {
    if( !i && !j )
      continue;

    if( !i ) {
      dp[i][j] = Sa[i]+Sb[j]-dp[i][j-1];
    } else if( !j ) {
      dp[i][j] = Sa[i]+Sb[j]-dp[i-1][j];
    } else {
      dp[i][j] = Sa[i]+Sb[j]-std::min(dp[i-1][j], dp[i][j-1]);
    }
  }

  std::cout << dp[A][B] << endl;

  return 0;
}