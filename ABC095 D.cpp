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

ll N, C;
ll x[100010], v[100010];
ll left[100010][2], right[1000010][2];

int main() {
  std::cin >> N >> C;

  rep( i, N )
    std::cin >> x[i] >> v[i];

  ll S = 0;
  rep( i, N ) {
    rep( j, 2 )
      right[i+1][j] = right[i][j];
    
    S += v[i];
    chmax( right[i+1][0], S-x[i] );
    chmax( right[i+1][1], right[i+1][0]-x[i] );
  }

  S = 0;

  repd( i, N ) {
    rep( j, 2 )
      left[i][j] = left[i+1][j];

    S += v[i];
    chmax( left[i][0], S-(C-x[i]) );
    chmax( left[i][1], left[i][0]-(C-x[i]) );
  }

  ll ans = 0;

  rep( i, N+1 ) {
    chmax( ans, left[i][0]+right[i][1] );
    chmax( ans, left[i][1]+right[i][0] );
  }

  std::cout << ans << endl;

  return 0;
}