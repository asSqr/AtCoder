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
ll a[200010];
std::string c[200010];

P min_diff( const std::vector<ll> &us, const std::vector<ll> &vs ) {
  ll n = us.size();
  ll m = vs.size();

  ll ans = INF;
  P pr;

  rep( i, n ) {
    ll idx = std::lower_bound(all(vs), us[i])-vs.begin();

    if( chmin( ans, vs[idx]-us[i] ) ) {
      pr = P(i, idx);
    }

    if( idx-1 >= 0 ) {
      if( chmin( ans, vs[idx-1]-us[i] ) ) {
        pr = P(i, idx-1);
      }
    }
  }

  return pr;
}

const std::string RGB = "RGB";
std::vector<ll> grp[5];

int main() {
  std::cin >> N;

  rep( i, 2*N ) {
    std::cin >> a[i] >> c[i];

    grp[RGB.find(c[i][0])].emplace_back(a[i]);
  }

  ll r = grp[0].size();
  ll g = grp[1].size();
  ll b = grp[2].size();

  if( r%2==0 && g%2==0 && b%2==0 ) {
    std::cout << 0 << endl;

    return 0;
  } else {
    std::vector<ll> gs[2];
    
    gs[r&1].emplace_back(0);
    gs[g&1].emplace_back(1);
    gs[b&1].emplace_back(2);

    ll z0 = gs[1][0], z1 = gs[1][1];
    ll o = gs[0][0];

    auto pr = min_diff(grp[z0], grp[z1] );
    ll ans = llabs(grp[z0][pr.first]-grp[z1][pr.second]);

    if( grp[o].size() >= 2 ) {
      auto ogrp = grp[o];

      auto prr = min_diff(grp[z0], ogrp);

      ll sum = grp[z0][prr.first]-ogrp[prr.second];

      ogrp.erase(ogrp.begin()+prr.second);

      auto prr2 = min_diff(grp[z1], ogrp);

      sum += grp[z1][prr2.first]-ogrp[prr2.second];

      chmin( ans, sum );
    }

    if( grp[o].size() >= 2 ) {
      auto ogrp = grp[o];

      auto prr = min_diff(grp[z1], ogrp);

      ll sum = grp[z1][prr.first]-ogrp[prr.second];

      ogrp.erase(ogrp.begin()+prr.second);

      auto prr2 = min_diff(grp[z0], ogrp);

      sum += grp[z0][prr2.first]-ogrp[prr2.second];

      chmin( ans, sum );
    }

    std::cout << ans << endl;

    return 0;
  }

  return 0;
}