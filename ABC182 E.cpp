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

ll H, W, N, M;
ll A[500010], B[500010];
ll C[100010], D[100010];
std::vector<P> hs[2000], vs[2000];

int main() {
  std::cin >> H >> W >> N >> M;

  rep( i, N ) {
    std::cin >> A[i] >> B[i];
    --A[i]; --B[i];

    hs[A[i]].emplace_back(B[i], 0);
    vs[B[i]].emplace_back(A[i], 0);
  }

  rep( i, M ) {
    std::cin >> C[i] >> D[i];
    --C[i]; --D[i];

    hs[C[i]].emplace_back(D[i], 1);
    vs[D[i]].emplace_back(C[i], 1);
  }

  rep( i, H ) {
    hs[i].emplace_back( -1, 2 );
    std::sort(all(hs[i]));
    hs[i].emplace_back( W, 2 );
  }
  rep( j, W ) {
    vs[j].emplace_back( -1, 2 );
    std::sort(all(vs[j]));
    vs[j].emplace_back( H, 2 );
  }

  ll ans = 0;

  rep( i, H ) rep( j, W ) {
    ll hidx = std::lower_bound( all(hs[i]), P( j, -1 ) )-hs[i].begin();
    ll vidx = std::lower_bound( all(vs[j]), P( i, -1 ) )-vs[j].begin();

    if( hs[i][hidx] == P( j, 1 ) )
      continue;
    if( vs[j][vidx] == P( i, 1 ) )
      continue;

    if( !hs[i][hidx].second )
    { ++ans; continue; }

    if( !hs[i][hidx-1].second )
    { ++ans; continue; }

    if( !vs[j][vidx].second )
    { ++ans; continue; }

    if( !vs[j][vidx-1].second )
    { ++ans; continue; }
  }

  std::cout << ans << endl;

  return 0;
}