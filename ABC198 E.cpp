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
ll C[100010];
std::vector<ll> G[100010];
std::map<ll, ll> used;
std::vector<ll> ans;

void dfs( ll v, ll p = -1 ) {
  if( !used[C[v]] ) {
    ans.emplace_back(v);
  }

  ++used[C[v]];
  
  for( auto u : G[v] ) if( u != p ) {
    dfs( u, v );
  }

  --used[C[v]];
}

int main() {
  std::cin >> N;

  rep( i, N ) {
    std::cin >> C[i];
  }

  rep( i, N-1 ) {
    ll A, B;
    std::cin >> A >> B;
    --A; --B;

    G[A].emplace_back(B);
    G[B].emplace_back(A);
  }

  dfs( 0 );

  std::sort(all(ans));

  for( auto v : ans )
    std::cout << v+1 << endl;

  return 0;
}