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
ll A[18*17/2+10], B[18*17/2+10];
std::vector<ll> G[20];
ll mat[20][20];
ll dp[(1ll<<18)+10];
bool check[(1ll<<18)+10];

int main() {
  std::cin >> N >> M;

  rep( i, M ) {
    std::cin >> A[i] >> B[i];
    --A[i]; --B[i];

    G[A[i]].emplace_back(B[i]);
    G[B[i]].emplace_back(A[i]);

    mat[A[i]][B[i]] = mat[B[i]][A[i]] = 1;
  }

  rep( bit, 1ll<<N )
    dp[bit] = INF;

  dp[0] = 0;

  rep( bit, 1ll<<N ) {
    std::vector<ll> us;

    check[bit] = true;

    rep( i, N ) if( bit>>i&1 )
      us.emplace_back(i);

    ll m = us.size();

    rep( i, m ) rep( j, i ) {
      check[bit] &= mat[us[i]][us[j]];
    }
  }

  rep( bit, 1ll<<N ) {
    std::vector<ll> vs;

    rep( i, N ) if( bit>>i&1 )
      vs.emplace_back(i);

    ll n = vs.size();
    ll mask = 0;

    rep( i, n )
      mask |= 1ll<<vs[i];

    for( ll bit2 = mask; bit2; bit2 = (bit2-1)&mask) {
      if( check[bit2] )
        chmin( dp[bit], dp[bit^bit2]+1 );
    }
  }

  std::cout << dp[(1ll<<N)-1] << endl;

  return 0;
}