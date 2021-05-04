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
ll S[200010], dS[200010];
std::vector<ll> G[200010];
ll deg[200010];
ll ans[200010], idx[200010];
ll p;
std::set<Pr> st;

bool add_edge( ll u, ll v ) {
  if( st.count(Pr(u,v)) )
    return false;

  G[u].emplace_back(v);

  return true;
}

int main() {
  std::cin >> N;

  rep( i, N )
    std::cin >> P[i], --P[i], ip[P[i]] = i;

  rep( i, N ) {
    ll x = ip[i];
    ll y = i;

    if( x < y ) {
      ++S[x];
      --S[y-1];

      if( x-1 >= 0 && x < N-1 && add_edge(x, x-1) )
        ++deg[x-1], st.emplace(x, x-1);
      if( y-1 >= 0 && y < N-1 && add_edge(y, y-1) )
        ++deg[y-1], st.emplace(y, y-1);
    } else if( y < x ) {
      ++dS[y];
      --dS[x-1];

      if( y-1 >= 0 && y < N-1 && add_edge(y-1, y) )
        ++deg[y], st.emplace(y-1, y);
      if( x-1 >= 0 && x < N-1 && add_edge(x-1, x) )
        ++deg[x], st.emplace(x-1, x);
    } else {
      std::cout << -1 << endl;

      return 0;
    }
  }

  rep( i, N ) {
    S[i+1] += S[i];
    dS[i+1] += dS[i];
  }

  /*rep( i, N ) {
    printf( "S[%lld] = %lld\n", i, S[i] );
  }

  rep( i, N ) {
    printf( "dS[%lld] = %lld\n", i, dS[i] );
  }*/

  rep( i, N-1 ) {
    if( S[i] > 0 && add_edge(i, i+1) ) {
      st.emplace(i, i+1);
      ++deg[i+1];
    }
    
    if( dS[i] > 0 && add_edge(i+1, i) ) {
      st.emplace(i+1, i);
      ++deg[i];
    }
  }

  //rep( i, N-1 ) for( auto u : G[i] )
    //printf( "%lld -> %lld\n", i, u );

  std::queue<ll> que;

  rep( i, N-1 ) if( !deg[i] )
    que.emplace(i);

  rep( i, N-1 )
    ans[i] = -1;

  while( !que.empty() ) {
    ll v = que.front(); que.pop();

    ans[v] = p++;

    for( auto u : G[v] ) {
      --deg[u];

      if( !deg[u] )
        que.emplace(u);
    }
  }

  rep( i, N-1 ) {
    //printf( "ans[%lld] = %lld\n", i, ans[i] );

    if( ans[i] == -1 ) {
      std::cout << -1 << endl;

      return 0;
    }

    idx[ans[i]] = i;
  }

  rep( i, N-1 )
    std::cout << idx[i]+1 << endl;

  return 0;
}