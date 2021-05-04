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

ll N, M;
ll X[110], Y[110], Z[110];
ll dp[(1ll<<18)+10];
std::vector<P> qs[110];

int main() {
  std::cin >> N >> M;

  rep( i, M ) {
    std::cin >> X[i] >> Y[i] >> Z[i];
    qs[X[i]].emplace_back(Y[i], Z[i]);
  }

  dp[0] = 1;

  rep( bit, 1ll<<N ) rep( i, N ) if( !(bit>>i&1) ) {
    ll nbit = bit | 1ll<<i;

    ll x = __builtin_popcountll(nbit);

    bool fl = true;

    for( auto [y, z] : qs[x] ) {
      ll z2 = __builtin_popcountll(nbit&((1ll<<y)-1));

      fl &= z2 <= z;
    }

    if( fl ) {
      dp[nbit] += dp[bit];
    }
  }

  std::cout << dp[(1ll<<N)-1] << endl;

  return 0;
}