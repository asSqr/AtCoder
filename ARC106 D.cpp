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

using mint = atcoder::modint998244353;

ll N, K;
mint A[200010];

mint fact[310], inv[310];

mint comb( ll n, ll r ) {
  if( n < r )
    return 0;
  if( n < 0 )
    return 0;
  if( r < 0 )
    return 0;

  return fact[n]*inv[r]*inv[n-r];
}

int main() {
  std::cin >> N >> K;
  rep( i, N ) {
    ll a;
    std::cin >> a;
    A[i] = a;
  } 

  fact[0] = 1;
  rep( i, 305 )
    fact[i+1] = fact[i]*(i+1);

  inv[305] = fact[305].inv();
  for( ll i = 304; i >= 0; --i )
    inv[i] = inv[i+1]*(i+1);

  std::vector<mint> B(N,1);
  std::vector<mint> S(K+10, 0);

  rep( e, K+1 ) {
    mint sum = 0;

    rep( i, N ) {
      sum += B[i];
      B[i] *= A[i];
    }

    S[e] = sum;
  }

  repi( X, 1, K+1 ) {
    mint ans = 0;

    rep( e, X+1 ) {
      mint y = S[e]*S[X-e];
      y -= S[X];

      ans += comb(X,e)*y;
    }

    ans /= 2;

    std::cout << ans.val() << endl;
  }

  return 0;
}