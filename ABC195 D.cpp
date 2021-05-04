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

ll N, M, Q;
ll W[100], V[100];
ll X[100];
std::vector<P> ps;
ll dp[60][60];

int main() {
  std::cin >> N >> M >> Q;

  rep( i, N ) {
    std::cin >> W[i] >> V[i];

    ps.emplace_back(W[i], V[i]);
  }

  std::sort(all(ps));

  rep( i, M )
    std::cin >> X[i];

  rep( q, Q ) {
    ll L, R;
    std::cin >> L >> R;

    std::vector<ll> xs;

    rep( i, M ) {
      if( i >= L-1 && i < R )
        continue;

      xs.emplace_back(X[i]);
    }

    std::sort(all(xs));

    ll m = xs.size();

    rep( i, N+5 ) rep( j, m+5 )
      dp[i][j] = 0;

    rep( i, N ) rep( j, m+1 ) {
      ll k = std::lower_bound( xs.begin()+j, xs.end(), ps[i].first )-xs.begin();

      chmax( dp[i+1][k+1], dp[i][j]+ps[i].second );
      chmax( dp[i+1][j], dp[i][j] );
    }

    ll ans = 0;

    rep( j, m+1 )
      chmax( ans, dp[N][j] );

    std::cout << ans << endl;
  }

  return 0;
}