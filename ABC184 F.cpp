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

ll N, T;
ll A[50];
std::set<ll> S;

int main() {
  std::cin >> N >> T;

  rep( i, N )
    std::cin >> A[i];

  ll M = N/2;

  rep( bit, 1ll<<M ) {
    ll sum = 0;

    rep( j, M ) if( bit>>j&1 )
      sum += A[j];

    S.emplace(-sum);
  }

  ll L = N-M;
  ll ans = 0;

  rep( bit, 1ll<<L ) {
    ll sum = 0;

    rep( j, L ) if( bit>>j&1 )
      sum += A[M+j];

    auto it = S.lower_bound(sum-T);

    if( it != S.end() ) {
      chmax( ans, sum-(*it) );
    }
  }

  std::cout << ans << endl;

  return 0;
}