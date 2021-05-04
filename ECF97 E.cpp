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

ll n, k;
ll a[500010], b[500010];

int main() {
  std::cin >> n >> k;

  rep( i, n )
    std::cin >> a[i];

  rep( i, k )
    std::cin >> b[i];

  ll prv = -1;

  std::vector<P> vs;

  rep( i, k ) {
    if( prv >= a[b[i]] ) {
      std::cout << -1 << endl;

      return 0;
    }

    prv = a[b[i]];
  }

  ll bprv = -1;

  rep( i, k ) {
    if( b[i]-bprv == 1 ) {

    } else {
      ll diff = b[i]-bprv;

      if( a[b[i]]-a[bprv] < diff ) {
        std::cout << -1 << endl;
        
      }
    }
  }

  return 0;
}