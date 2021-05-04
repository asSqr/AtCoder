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
ll A[100010], B[100010];
ll ans;

void f( ll &a, ll &b ) {
  if( a <= b ) {
    b -= a;
    ans += a;
    a = 0;
  } else {
    a -= b;
    ans += b;
    b = 0;
  }

  return;
}

void solve( ll s, ll N ) {
  if( N <= 0 )
    return;

  f(A[s],B[s]);

  if( B[s] > 0 ) {
    f(A[s+1],B[s]);
  }

  f(A[s+N],B[s+N-1]);
  
  if( B[s+N-1] > 0 ) {
    f(A[s+N-1],B[s+N-1]);
  }

  solve( s+1, N-2 );
}

int main() {
  std::cin >> N;

  rep( i, N+1 )
    std::cin >> A[i];
  rep( i, N )
    std::cin >> B[i];

  solve( 0, N );

  std::cout << ans << endl;

  return 0;
}