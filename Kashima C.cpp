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
using Pr = std::pair<ll, ll>;

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
ll P[200010], ip[200010];
bool used[200010];
std::vector<ll> ans;

int main() {
  std::cin >> N;

  rep( i, N )
    std::cin >> P[i], --P[i], ip[P[i]] = i;

  ll pre = N-1;
  ll i = N-1;

  while( i > 0 ) {
    ll idx = ip[i];

    if( P[i] == i )
    { --i; continue; }

    ll lb = idx;

    repi( j, lb, pre ) {
      std::swap(ip[P[j]], ip[P[j+1]]);
      std::swap(P[j], P[j+1]);
      ans.emplace_back(j);
    }

    repi( j, lb+1, pre+1 ) {
      if( P[j] != j ) {
        std::cout << "-1" << endl;

        return 0;
      }
    }

    if( !i ) {
      if( P[0] ) {
        std::cout << "-1" << endl;

        return 0;
      }

      break;
    }

    pre = lb;
    i = lb;
  }

  for( auto x : ans )
    std::cout << x+1 << endl;

  return 0;
}