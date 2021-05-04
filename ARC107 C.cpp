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
ll a[60][60];
mint fact[60];

mint solve() {
  atcoder::dsu d(N);

  rep( i, N ) rep( j, i ) {
    bool fl = true;
    
    rep( k, N ) {
      fl &= a[i][k]+a[j][k] <= K;
    }

    if( fl )
      d.merge( i, j );
  }

  auto vss = d.groups();

  mint ret = 1;

  for( auto vs : vss )
    ret *= fact[vs.size()];

  return ret;
}

void transpose() {
  ll b[60][60] = { 0 };

  rep( i, N ) rep( j, N )
    b[i][j] = a[j][i];

  rep( i, N ) rep( j, N )
    a[i][j] = b[i][j];

  return;
}

int main() {
  std::cin >> N >> K;

  rep( i, N ) rep( j, N )
    std::cin >> a[i][j];

  fact[0] = 1;

  rep( i, N )
    fact[i+1] = fact[i]*(i+1);

  mint ans = solve();

  transpose();

  ans *= solve();

  std::cout << ans.val() << endl;

  return 0;
}