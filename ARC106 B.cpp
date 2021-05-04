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

ll N, M;
ll a[200010], b[200010];
std::vector<ll> G[200010];

int main() {
  std::cin >> N >> M;

  rep( i, N ) 
    std::cin >> a[i];
  rep( i, N )
    std::cin >> b[i];

  atcoder::dsu uf( N );

  rep( i, M ) {
    ll c, d;
    std::cin >> c >> d;
    --c; --d;

    G[c].emplace_back( d );
    G[d].emplace_back( c );
    
    uf.merge( c, d );
  }

  auto gs = uf.groups();

  bool fl = true;

  for( auto vs : gs ) {
    ll sumA = 0, sumB = 0;

    for( auto v : vs )
      sumA += a[v], sumB += b[v];

    fl &= sumA == sumB;
  }  

  std::cout << (fl ? "Yes" : "No") << endl;

  return 0;
}