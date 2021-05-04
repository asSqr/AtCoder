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

template<typename T>
struct BIT {
  int n;
  std::vector<T> d;
  BIT(int n=0):n(n),d(n+1) {}
  void add(int i, T x=1) {
    for (i++; i <= n; i += i&-i) {
      d[i] += x;
    }
  }
  T sum(int i) {
    T x = 0;
    for (i++; i; i -= i&-i) {
      x += d[i];
    }
    return x;
  }
  T sum(int l, int r) {
    return sum(r-1) - sum(l-1);
  }
};

std::string S;
std::vector<ll> cs[26], ts[26];
std::vector<P> as, bs, fs;
ll cnt;
ll ptr[26];

ll calcInv( const std::vector<ll> &p ) {
  BIT<ll> bit( p.size()+1 );

  ll ret = 0;

  rep( i, p.size() ) {
    ret += i-bit.sum( p[i] );

    bit.add( p[i], 1 );
  }

  return ret;
}

int main() {
  std::cin >> S;

  ll N = S.size();

  rep( i, N ) 
    cs[S[i]-'a'].emplace_back( i );

  ll ans = 0;

  std::vector<ll> xp( N );

  rep( c, 26 ) {
    rep( i, (cs[c].size()+1)/2 ) {
      if( (cs[c].size()&1) && i == (cs[c].size()+1)/2-1 ) {
        ++cnt;

        if( cnt > 1 ) {
          puts("-1");

          return 0;
        }

        bs.emplace_back( cs[c][i], c );
        xp[cs[c][i]] = N/2;
      } else {
        as.emplace_back( cs[c][i], c );
        fs.emplace_back( cs[c][cs[c].size()-1-i], c );
      }
    }
  }

  std::sort( all(as) );
  std::sort( all(fs) );

  rep( i, as.size() ) {
    xp[as[i].first] = i;
    ts[as[i].second].emplace_back( N-1-i );
  }

  rep( c, 26 ) {
    std::sort(all(ts[c]));
  }

  std::vector<ll> p(fs.size());

  rep( i, fs.size() ) {
    xp[fs[i].first] = (N+1)/2+i;
    ll c = fs[i].second;

    p[i] = ts[c][ptr[c]++]-(N+1)/2;
  }

  ans += calcInv(xp);

  ans += calcInv(p);

  std::cout << ans << endl;

  return 0;
}