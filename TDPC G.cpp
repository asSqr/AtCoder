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

constexpr ll INF = 1e18+1;

template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return 1; } return 0; }

template<class S, class T>
std::ostream& operator<< ( std::ostream& out, const std::pair<S,T>& a )
{ std::cout << '(' << a.first << ", " << a.second << ')'; return out; }

template<class T>
std::ostream &operator<< ( std::ostream& out, const std::vector<T>& a )
{ std::cout << '['; rep( i, a.size() ){ std::cout << a[i]; if( i != a.size()-1 ) std::cout << ", "; } std::cout << ']'; return out; }

std::string s;
ll K;
ll nxt[1000010][30], dp[1000010];

int main() {
  std::cin >> s >> K;

  ll n = s.size();

  std::vector<ll> ns(26, n);

  repd( i, n ) {
    ns[s[i]-'a'] = i;

    rep( ch, 26 )
      nxt[i][ch] = ns[ch];
  }

  repd( i, n ) {
    dp[i] = 1;

    rep( j, 26 ) {
      dp[i] += dp[nxt[i+1][j]];
      chmin( dp[i], INF );
    }
  }

  ll p = 0;
  std::string ans;

  while( K > 0 ) {
    rep( ch, 26 ) {
      if( dp[nxt[p][ch]] < K ) {
        K -= dp[nxt[p][ch]];
      } else {
        --K;
        p = nxt[p][ch]+1;

        ans += char(ch+'a');

        goto end;
      }
    }

    puts("Eel");

    return 0;

end:;
  }

  std::cout << ans << endl;

  return 0;
}