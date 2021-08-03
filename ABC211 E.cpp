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

using ull = unsigned long long;

const ll dx[4] = { 1, 0, -1, 0 }, dy[4] = { 0, 1, 0, -1 };

ll N, K;
std::string S[20];
ll dist[20][20];
std::set<ull> ans;

struct St {
  ll i, j; 
  ull bit;
};

bool safe( ll i, ll j ) {
  return i >= 0 && i < N && j >= 0 && j < N;
}

using vi = std::set<ull>;

vi dfs( ll i, ll j, ull used = 0 ) {
  used |= 1ull<<(i*N+j);

  vi ret = { 1ull<<(i*N+j) };

  rep( d, 4 ) {
    ll ni = i+dy[d], nj = j+dx[d];

    if( !safe(ni, nj) )
      continue;
    if( S[ni][nj] == '#' )
      continue;
    if( (used>>(ni*N+nj))&1 )
      continue;
    if( __builtin_popcount(used) > K )
      continue;

    auto cs = dfs( ni, nj, used );

    vi nret = ret;

    for( auto b : ret ) for( auto c : cs ) {
      ll nbit = b | c;

      if( __builtin_popcountll(nbit) > K )
        continue;

      nret.emplace(nbit);
    }

    std::swap(ret, nret);
  }

  // std::cout << P(i,j) << ' ' << __builtin_popcountll(used) << endl;

  return ret;
}

int main() {
  std::cin >> N >> K;

  rep( i, N )
    std::cin >> S[i];

  rep( i, N ) rep( j, N ) {
    if( S[i][j] == '#' )
      continue;

    auto res = dfs( i, j );

    for( auto r : res ) {
      if( __builtin_popcountll(r) != K )
        continue;
      
      ans.emplace(r);
    }
  }

  /*for( auto x : ans ) {
    std::cout << x << ' ' << __builtin_popcount(x) << endl;
  }*/

  std::cout << ans.size() << endl;

  return 0;
}