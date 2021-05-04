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

using Fld = std::vector<std::vector<bool>>;

ll H, W, A, B;
ll b[20][20];
ll three[20];

using Tup = std::tuple<ll, ll, ll, ll>;

int main() {
  std::cin >> H >> W >> A >> B;

  three[0] = 1;

  rep( i, 20 )
    three[i+1] = three[i]*3;

  std::vector<Tup> ts;

  rep( i, H ) rep( j, W-1 ) {
    ts.emplace_back( i, j, i, j+1 );
  }

  rep( j, W ) rep( i, H-1 )
    ts.emplace_back( i, j, i+1, j );

  ll C = ts.size();

  ll ans = 0;

  rep( bit, 1ll<<C ) {
    ll p = 0;

    if( __builtin_popcountll(bit) != A )
      continue;

    std::vector<std::vector<bool>> fld( H, std::vector<bool>( W, false ) );

    rep( i, C ) {
      if( bit>>i&1 ) {
        auto [fi, fj, ti, tj] = ts[i];

        if( fld[fi][fj] || fld[ti][tj] )
          goto end;

        fld[fi][fj] = fld[ti][tj] = true;
      }
    }  

  ++ans;

end:;
  }

  std::cout << ans << endl;

  return 0;
}