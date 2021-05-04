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

ll N, K;
ll A[20];
const ll ub = 4000010;
std::vector<ll> masks;

bool C( ll D ) {
  std::vector<ll> f( (1ll<<N)+10 );

  rep( i, D )
    ++f[masks[i]];

  rep( i, N ) rep( bit, 1ll<<N ) if( !(bit>>i&1) ) {
    f[bit] += f[bit|1ll<<i];
  }

  bool fl = true;

  rep( bit, 1ll<<N ) {
    fl &= D-f[bit] >= K*__builtin_popcountll(bit);
  }

  return fl;
}

int main() {
  std::cin >> N >> K;

  rep( i, N )
    std::cin >> A[i];

  rep( i, ub+2 ) {
    ll S = 0;

    rep( j, N ) {
      ll b = ((i/A[j])&1);
      S |= b<<j;
    }

    masks.emplace_back(S);
  }

  ll ng = 0, ok = 2*N*K+1;

  while( ok-ng > 1 ) {
    ll mid = (ng+ok)>>1;

    (C(mid) ? ok : ng) = mid;
  }

  std::cout << ok << endl;

  return 0;
}