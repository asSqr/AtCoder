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
ll a[310];
double dp[310][310][310];
ll x, y, z;

int main() {
  std::cin >> N;

  rep( i, N ) {
    std::cin >> a[i];

    if( a[i] == 1 )
      ++x;
    else if( a[i] == 2 )
      ++y;
    else
      ++z;
  }

  rep( k, N+1 ) rep( j, N+1 ) rep( i, N+1 ) {
    if( i+j+k > N )
      continue;
    if( !i && !j && !k )
      continue;
    
    double sum = double(N-i-j-k)/N;

    if( i )
      sum += (dp[i-1][j][k]+1)*(double(i)/N);
    if( j )
      sum += (dp[i+1][j-1][k]+1)*(double(j)/N);
    if( k )
      sum += (dp[i][j+1][k-1]+1)*(double(k)/N);

    sum /= (1.0-double(N-i-j-k)/N);

    dp[i][j][k] = sum;
  }

  printf( "%.12f\n", dp[x][y][z] );

  return 0;
}