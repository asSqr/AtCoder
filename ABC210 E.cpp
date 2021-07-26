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
ll A[100010], C[100010];
std::vector<P> ps;

ll gcd( ll a, ll b )
{ return b ? gcd(b, a%b) : a; }

int main() {
  std::cin >> N >> M;

  rep( i, M )
    std::cin >> A[i] >> C[i], ps.emplace_back( C[i], A[i] );

  std::sort(all(ps));

  ll m = N;

  ll ans = 0;

  rep( i, M ) {
    ll c = ps[i].first;
    ll a = ps[i].second;

    ll g = gcd(a, m);

    while( i < M && ps[i].first == c ) {
      if( chmin(g, gcd( ps[i].second, m) ) ) {
        a = ps[i].second;
      }

      ++i;
    }

    --i;

    if( m == 1 )
      continue;

    if( g < m ) {
      ans += c*(m-g);
      m = g;
    }
  }

  std::cout << (m==1 ? ans : -1) << endl;

  return 0;
}