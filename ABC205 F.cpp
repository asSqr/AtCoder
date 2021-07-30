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
#include <atcoder/all>
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

ll H, W, N;

ll row( ll r )
{ return r; }

ll col( ll c )
{ return H+c; }

ll interval( ll i, bool fl )
{ return fl ? H+W+i+N : H+W+i; }

int main() {
  std::cin >> H >> W >> N;

  atcoder::mf_graph<ll> G(H+W+N*2+2);

  ll s = H+W+N*2;
  ll t = s+1;

  rep( i, H ) {
    G.add_edge( s, row(i), 1 );
  }

  rep( i, W ) {
    G.add_edge( col(i), t, 1 );
  }

  rep( i, N ) {
    ll A, B, C, D;
    std::cin >> A >> B >> C >> D;
    --A; --B;

    repi( r, A, C )
      G.add_edge( row(r), interval(i, false), 1 );

    repi( c, B, D )
      G.add_edge( interval(i, true), col(c), 1 );

    G.add_edge( interval(i, false), interval(i, true), 1 );
  }

  ll ans = G.flow( s, t );

  std::cout << ans << endl;

  return 0;
}