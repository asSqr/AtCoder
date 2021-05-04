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

ll H, W;
std::string S[1010];
std::vector<ll> rs, cs;

int main() {
  std::cin >> H >> W;

  rep( i, H )
    std::cin >> S[i];

  ll p = 0;

  rep( i, H )
    rs.emplace_back(p++);

  rep( j, W )
    cs.emplace_back(p++);

  atcoder::dsu d( p+10 );

  d.merge( rs[0], cs[0] );
  d.merge( rs[0], cs[W-1] );
  d.merge( rs[H-1], cs[W-1] );
  d.merge( rs[H-1], cs[0] );

  rep( i, H ) rep( j, W ) {
    if( S[i][j] == '.' )
      continue;

    d.merge( rs[i], cs[j] );
  }

  std::set<ll> row, col;

  rep( i, H )
    row.emplace(d.leader(rs[i]));
  
  rep( i, W )
    col.emplace(d.leader(cs[i]));

  ll ans = std::min( row.size()-1, col.size()-1 );

  std::cout << ans << endl;

  return 0;
}