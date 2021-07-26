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

ll H, W, C;
std::vector<std::vector<ll>> A( 1010, std::vector<ll>( 1010 ) ), B( 1010, std::vector<ll>( 1010 ) );
ll mi[1010][1010];
ll ans = INF;

void solve( const std::vector<std::vector<ll>> &A ) {
  rep( i, H ) rep( j, W ) {
    B[i][j] = A[H-1-i][W-1-j]+C*(H-1-i+W-1-j);
  }

  rep( i, H+1 ) rep( j, W+1 )
    mi[i][j] = INF;

  rep( i, H ) rep( j, W ) {
    mi[i+1][j+1] = std::min( { mi[i+1][j], mi[i][j+1], B[i][j] } );
  }

  rep( i, H ) rep( j, W ) {
    ll tmp = A[i][j];

    tmp += std::min( mi[H-i][W-j-1], mi[H-i-1][W-j] )-C*(i+j);

    chmin( ans, tmp );
  }

  return;
}

int main() {
  std::cin >> H >> W >> C;

  rep( i, H ) rep( j, W )
    std::cin >> A[i][j];

  rep( t, 4 ) {
    solve(A);

    auto C = A;

    rep( i, H ) rep( j, W ) 
      C[j][H-1-i] = A[i][j];

    std::swap( H, W );

    A = C;
  }

  std::cout << ans << endl;

  return 0;
}