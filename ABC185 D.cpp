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
ll A[200010];

int main() {
  std::cin >> N >> M;

  rep( i, M )
    std::cin >> A[i];
  
  std::sort( A, A+M );

  ll ans = INF;
  std::vector<ll> vs;

  ll p = 1;
  rep( i, M ) {
    if( A[i] == p )
    { ++p; continue; }

    chmin( ans, llabs(A[i]-p) );
    vs.emplace_back(llabs(A[i]-p));
    p = A[i]+1;
  }

  if( N+1-p > 0 ) {
    chmin( ans, llabs(N+1-p) );
    vs.emplace_back(N+1-p);
  }

  ll an = 0;

  for( auto v: vs ) {
    an += (v+ans-1)/ans;
  }

  std::cout << an << endl;

  return 0;
}