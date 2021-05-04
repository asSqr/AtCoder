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

ll n;
ll s[2010];
std::vector<ll> vs;
std::map<ll, ll> ip, cnt;
ll dp[2010][2010];

int main() {
  std::cin >> n;

  rep( i, n )
    std::cin >> s[i], vs.emplace_back(s[i]), ++cnt[s[i]];

  std::sort(all(vs));
  vs.erase(std::unique(all(vs)), vs.end());

  rep( i, vs.size() )
    ip[vs[i]] = i;

  ll N = vs.size();

  rep( i, N+10 ) rep( j, N+10 )
    dp[i][j] = i==j ? 0 : INF;

  rep( w, N ) rep( s, N ) {
    ll t = s+w;

    if( t >= N )
      continue;

    if( s+1 <= t )
      chmin( dp[s][t], dp[s+1][t]+cnt[vs[s]]*(vs[t]-vs[s]) );
    if( s <= t-1 )
      chmin( dp[s][t], dp[s][t-1]+cnt[vs[t]]*(vs[t]-vs[s]) );
  }

  std::cout << dp[0][N-1] << endl;

  return 0;
}