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

std::string s, t;
ll dp[3010][3010];
char prv[3010][3010];
ll type[3010][3010];

int main() {
  std::cin >> s >> t;

  ll n = s.size(), m = t.size();

  rep( i, n ) rep( j, m ) {
    if( chmax( dp[i+1][j+1], dp[i][j]+(s[i]==t[j]) ) )
      prv[i+1][j+1] = s[i], type[i+1][j+1] = s[i]==t[j];

    if( chmax( dp[i+1][j+1], dp[i+1][j] ) )
      prv[i+1][j+1] = s[i], type[i+1][j+1] = 2;
    
    if( chmax( dp[i+1][j+1], dp[i][j+1] ) )
      prv[i+1][j+1] = t[j], type[i+1][j+1] = 3;
  }

  ll p = n, q = m;
  std::string ans;

  while( p && q ) {
    if( type[p][q] == 1 )
      ans += prv[p][q];

    switch( type[p][q] ) {
      case 0:
      case 1:
        --p, --q;
        break;
      case 2:
        --q;
        break;
      case 3:
        --p;
        break;
    }
  }

  std::reverse( all(ans) );

  std::cout << ans << endl;

  return 0;
}