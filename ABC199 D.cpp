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
std::vector<ll> G[30];
bool used[30];
std::deque<ll> vs;
std::map<ll, ll> ip;
bool adj[30][30];

void dfs( ll v ) {
  used[v] = true;

  vs.emplace_back(v);
  ip[v] = vs.size()-1;

  for( auto u : G[v] ) if( !used[u] ) {
    dfs(u);
  }
}

ll rec( ll i, std::deque<ll> &qs ) {
  std::set<ll> st;

  if( i == vs.size() ) {
    rep( i, qs.size() ) rep( j, i ) {
      ll u = vs[i], v = vs[j];
      ll cu = qs[i], cv = qs[j];

      if( adj[u][v] && cu == cv ) {
        return 0;
      }
    }

    return 1;
  }

  for( auto u : G[vs[i]] ) if( ip[u] < i ) {
    st.emplace(qs[ip[u]]);
  }

  ll ret = 0;

  rep( col, 3 ) if( !st.count(col) ) {
    qs.emplace_back( col );

    ret += rec( i+1, qs );

    qs.pop_back();
  }

  return ret;
}

int main() {
  std::cin >> N >> M;

  rep( i, M ) {
    ll A, B;
    std::cin >> A >> B;
    --A; --B;

    G[A].emplace_back(B);
    G[B].emplace_back(A);
    adj[A][B] = adj[B][A] = true;
  }

  ll prod = 1;

  rep( i, N ) if( !used[i] ) {
    vs.clear();
    ip.clear();

    dfs(i);

    ll L = vs.size();

    ll sum = 0;

    rep( col, 3 ) {
      std::deque<ll> qs{ col };
      sum += rec( 1, qs );
    }

    prod *= sum;
  }

  std::cout << prod << endl;

  return 0;
}