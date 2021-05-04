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
std::string S;
ll Q;
std::vector<P> ps;

int main() {
  std::cin >> N >> S >> Q;

  bool flip = false;

  rep( q, Q ) {
    ll T, A, B;
    std::cin >> T >> A >> B;
    --A; --B;

    if( T == 1 ) {
      ll pad = (flip ? N : 0);
      
      if( A >= N ) {
        A -= pad;
      } else {
        A += pad;
      }

      if( B >= N ) {
        B -= pad;
      } else {
        B += pad;
      }

      ps.emplace_back(A, B);
    } else {
      flip ^= true;
    }
  }

  for( auto [a, b] : ps ) {
    std::swap(S[a], S[b]);
  }

  auto ans = S;

  if( flip ) {
    ans = S.substr(N, N)+S.substr(0, N);
  }

  std::cout << ans << endl;

  return 0;
}