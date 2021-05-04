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
ll X[200010], C[200010];
std::vector<ll> vs[200010];
std::map<ll, ll> dp[2];

void chminMp( std::map<ll, ll> &mp, ll idx, ll x ) {
  if( !mp.count(idx) )
    mp[idx] = x;
  else
    mp[idx] = std::min( mp[idx], x );

  return;
}

int main() {
  std::cin >> N;

  rep( i, N ) {
    std::cin >> X[i] >> C[i];
    --C[i];

    vs[C[i]].emplace_back(X[i]);
  }

  rep( i, N )
    std::sort(all(vs[i]));

  ll x = 0;

  dp[0][0] = 0;

  ll p = 0;

  auto prv = dp[0], nxt = dp[1];

  rep( i, N ) {
    if( vs[i].empty() )
      continue;

    nxt.clear();

    itr( it, prv ) {
      ll x = it->first;

      ll idx = std::lower_bound(all(vs[i]), x)-vs[i].begin();

      if( idx && vs[i].size()-idx ) {
        ll d1 = llabs(vs[i][0]-x);
        ll d2 = llabs(vs[i][vs[i].size()-1]-x);

        chminMp(nxt, vs[i][vs[i].size()-1], prv[x]+d1*2+d2);
        chminMp(nxt, vs[i][0], prv[x]+d1+d2*2);
      } else if( idx ) {
        ll d1 = llabs(vs[i][0]-x);
        
        chminMp(nxt, vs[i][0], prv[x]+d1);
      } else if( vs[i].size()-idx ) {
        ll d2 = llabs(vs[i][vs[i].size()-1]-x);

        
        chminMp(nxt, vs[i][vs[i].size()-1], prv[x]+d2);
      }
    }

    std::swap(prv, nxt);
  }

  ll ans = INF;

  itr( it, prv ) {
    chmin( ans, it->second+llabs(it->first) );
  }

  std::cout << ans << endl;

  return 0;
}