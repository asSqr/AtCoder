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

ll T;

ll p = 0;
std::vector<ll> a;

int main() {
  std::cin >> T;

  rep( t, T ) {
    ll n;
    std::cin >> n;

    ll dummy;
    std::cin >> dummy;

    a.assign(n-1, 0);
    for( auto &x : a )
      std::cin >> x;

    ll prv = -1;
    ll cnt = 0;
    std::deque<ll> que;

    for( auto x : a ) {
      if( prv >= x ) {
        que.push_back( cnt );
        cnt = 1;
      } else {
        ++cnt;
      }

      prv = x;
    }

    que.push_back( cnt );

    ll ans = 1;

    while( !que.empty() ) {
      ll tim = que.front(); que.pop_front();

      if( !tim )
        break;

      ll sum = 0;

      rep( i, tim ) {
        if( que.empty() )
          goto end;

        sum += que.front();
        que.pop_front();

        if( !i )
          ++ans;
      }

      que.push_front(sum);
    }
end:;

    std::cout << ans << endl;
  }

  return 0;
}