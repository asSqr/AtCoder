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
ll A[400010], B[400010];
ll cnt[400010];
std::vector<ll> as[400010], bs[400010];
std::set<ll> cs[400010];
ll ans[400010];
std::map<ll, ll> cntA, cntB;

ll getAny( std::map<ll, ll> &mp, ll x ) {
  itr( it, mp ) if( it->first != x ) {
    return it->first;
  }
}

int main() {
  std::cin >> N;

  rep( i, N ) {
    std::cin >> A[i], ++cnt[A[i]], ++cntA[A[i]];

    as[A[i]].emplace_back(i);
  }
  
  rep( i, N ) {
    std::cin >> B[i], ++cnt[B[i]], ++cntB[B[i]];

    bs[B[i]].emplace_back(i);
  }

  repi( i, 1, N+1 ) if( cnt[i] ) {
    cs[cnt[i]].emplace(i);

    if( cnt[i] > N ) {
      puts("No");

      return 0;
    }
  }

  for( ll i = N; i >= 1; --i ) {
    auto vs = cs[i];

    ll x = 0, y = 0;

    if( vs.empty() ) {
      x = getAny(cntA, -1);
      y = getAny(cntB, x);
    } else if( vs.size() == 1 ) {
      x = *vs.begin();
      
      if( as[x].empty() ) { // from b
        y = x;
        x = getAny(cntA, y);
      } else { // from a
        y = getAny(cntB, x);
      }
    } else if( vs.size() == 2 ) {
      x = *vs.begin();
      y = *(++vs.begin());

      if( as[x].empty() )
        std::swap(x,y);
    }

    ans[as[x].back()] = y;
    as[x].pop_back();

    auto updateCnt = [&]( std::map<ll, ll> &mp, ll x ) {
      --mp[x];

      if( !mp[x] )
        mp.erase(x);
    };

    auto updateCs = [&]( ll x ) {
      cs[cnt[x]].erase(x);
      --cnt[x];
      cs[cnt[x]].emplace(x);
    };

    updateCnt( cntA, x );
    updateCnt( cntB, y );
    updateCs( x );
    updateCs( y );
  }

  puts("Yes");

  rep( i, N )
    std::cout << ans[i] << (i==N-1 ? '\n': ' ');

  return 0;
}