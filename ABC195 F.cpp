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
#define abigint(a) (a).begin(), (a).end()
#define rabigint(a) (a).rbegin(), (a).rend()
#define endl '\n'
#define debug(x) std::cerr << #x << " = " << (x) << endl;

template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return 1; } return 0; }

using ll = long long;

bool used[100];
std::vector<ll> ps;
std::map<ll, ll> ip;

void sieve() {
  used[0] = used[1] = true;

  repi( i, 2, 73 ) {
    if( !used[i] ) {
      ps.emplace_back(i);
      ip[i] = ps.size()-1;

      for( ll j = i; j <= 72; j += i )
        used[j] = true;
    }
  }

  return;
}

ll prime_factor( ll x ) {
  ll ret = 0;

  rep( i, ps.size() ) if( x % ps[i] == 0 )
    ret |= 1ll<<i;

  return ret;
}

ll A, B;
ll dp[80][(1ll<<20)+10];

int main() {
  std::cin >> A >> B;
  
  sieve();

  ll N = ps.size();

  dp[0][0] = 1;

  rep( i, B-A+1 ) {
    ll x = i+A;
    ll bit = prime_factor(x);
    
    rep( j, 1ll<<N ) {
      if( !(j&bit) )
        dp[i+1][j|bit] += dp[i][j];
      
      dp[i+1][j] += dp[i][j];
    }
  }

  ll ans = 0;

  rep( j, 1ll<<N )
    ans += dp[B-A+1][j];

  std::cout << ans << endl;

  return 0;
}