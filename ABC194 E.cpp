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
ll A[1500010];
//std::priority_queue<ll, std::vector<ll>, std::greater<ll> > pque;
ll mp[2000010];
std::set<ll> S;

int main() {
  std::cin >> N >> M;

  rep( i, N )
    std::cin >> A[i];

  ll mex = 0;
  repi( i, 1, N+1 )
    S.emplace(i);

  ll ans = INF;

  rep( i, N ) {
    if( i >= M ) {
      --mp[A[i-M]];

      if( !mp[A[i-M]] && A[i-M] < mex ) {
        S.emplace(mex);
        mex = A[i-M];
      }
    }

    if( S.count(A[i]) ) {
      S.erase(S.lower_bound(A[i]));
    }

    if( mex == A[i] ) {
      mex = *S.begin();
      S.erase(S.begin());
    }

    ++mp[A[i]];

    if( i >= M-1 )
      chmin( ans, mex );
  }

  std::cout << ans << endl;

  return 0;
}