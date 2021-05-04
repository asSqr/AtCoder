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

ll H, W;
std::string a[2010];
ll si, sj, gi, gj;
std::vector<P> vs[30];
bool used[2010][2010];

const ll dx[4] = { 1, 0, -1, 0 }, dy[4] = { 0, 1, 0, -1 };

using Tup = std::tuple<ll, ll, ll, ll>;
std::map<P, ll> mp[30];
ll comp[2010][2010][2];

int main() {
  std::cin >> H >> W;

  rep( i, H ) {
    std::cin >> a[i];

    rep( j, W ) {
      if( a[i][j] == 'S' ) {
        si = i, sj = j;
      } else if( a[i][j] == 'G' ) {
        gi = i, gj = j;
      } else if( a[i][j] >= 'a' && a[i][j] <= 'z' ) {
        vs[a[i][j]-'a'].emplace_back(i, j);
        mp[a[i][j]-'a'][P(i,j)] = vs[a[i][j]-'a'].size()-1;
      }
    }
  }

  rep( i, H ) rep( j, W ) rep( k, 2 )
    comp[i][j][k] = INF;

  std::priority_queue<Tup, std::vector<Tup>, std::greater<Tup>> que;
  que.emplace(0,si,sj,0);
  comp[si][sj][0] = 0;

  while( !que.empty() ) {
    auto [di, i, j, tele] = que.top(); que.pop();

    if( comp[i][j][tele] < di )
      continue;

    rep( d, 4 ) {
      ll ni = i+dy[d], nj = j+dx[d];

      if( ni >= 0 && ni < H && nj >= 0 && nj < W && a[ni][nj] != '#' && chmin(comp[ni][nj][0], di+1) ) {
        que.emplace(comp[ni][nj][0],ni,nj,0);
      }
    }

    if( a[i][j] >= 'a' && a[i][j] <= 'z' ) {
      {
        ll idx = mp[a[i][j]-'a'][P(i,j)];
        auto [ni, nj] = vs[a[i][j]-'a'][(idx+1)%vs[a[i][j]-'a'].size()];
        
        if( ni >= 0 && ni < H && nj >= 0 && nj < W && a[ni][nj] != '#' && chmin(comp[ni][nj][1], di+(tele?0:1)) ) {
          que.emplace(comp[ni][nj][1],ni,nj,1);
        }
      }
    }
  }

  ll ans = std::min(comp[gi][gj][0], comp[gi][gj][1]);

  std::cout << (ans==INF?-1:ans) << endl;

  return 0;
}