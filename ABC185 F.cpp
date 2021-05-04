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
#include <atcoder/all>
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

ll N, Q;

using S = ll;
using F = ll;

S op( S a, S b ) {
  return a^b;
}

S e() {
  return 0;
}

S mapping( F f, S x ) {
  return x^f;
}

F composition( F f, F g ) {
  return g^f;
}

F id() {
  return 0;
}

int main() {
  std::cin >> N >> Q;

  std::vector<ll> A(N);

  rep( i, N )
    std::cin >> A[i];

  atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(A);

  rep( q, Q ) {
    ll T, X, Y;
    std::cin >> T >> X >> Y;
    --X;

    if( T == 1 ) {
      seg.apply( X, X+1, Y );
    } else {
      std::cout << seg.prod( X, Y ) << endl;
    }
  }

  return 0;
}