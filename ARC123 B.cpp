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
std::vector<ll> A, B, C;
ll lbi = -1, lci = -1;

int main() {
  std::cin >> N;

  A.resize(N);
  B.resize(N);
  C.resize(N);

  rep( i, N )
    std::cin >> A[i];
  rep( i, N )
    std::cin >> B[i];
  rep( i, N )
    std::cin >> C[i];

  std::sort(all(A));
  std::sort(all(B));
  std::sort(all(C));

  ll ans = 0;

  rep( i, N ) {
    ll a = A[i];

    ll bi = std::upper_bound(all(B), a)-B.begin();

    if( bi <= lbi )
      bi = lbi+1;

    if( bi == B.size() )
      continue;
    
    ll b = B[bi];

    ll ci = std::upper_bound(all(C), b)-C.begin();

    if( ci <= lci )
      ci = lci+1;

    if( ci == C.size() )
      continue;
    
    ll c = C[ci];

    ++ans;

    lbi = bi;
    lci = ci;
  }

  std::cout << ans << endl;

  return 0;
}