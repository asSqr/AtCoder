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
std::string s[200010];
std::map<std::string, std::vector<ll>> mp;
std::vector<ll> G[200010];
bool used[200010];
ll res[200010];
std::set<ll> to[200010];
bool draw[200010];

ll dfs( ll v ) {
  used[v] = true;

  bool fl = false, turn = true;
  ll cnt = 0;

  for( auto u : G[v] ) {
    fl |= to[u].count(v);
    
    if( !used[u] ) {
      ll ret = dfs(u);
        
      if( !(ret == 0 && draw[u]) )
        turn &= ret;

      if( (!used[u] && ret == -1) || (used[u] && draw[u]) ) {
        fl |= true;
      }
    }

    ++cnt;
  }

  if( !cnt ) {
    return res[v] = 1;
  }
  
  if( fl ) {
    draw[v] = true;
  }

  return res[v] = !turn;
}

int main() {
  std::cin >> N;

  rep( i, N ) {
    std::cin >> s[i];

    auto t = s[i].substr(0,3);

    if( mp.count(t) )
      mp[t].emplace_back(i);
    else
      mp[t] = std::vector<ll>({i});
  }

  rep( i, N ) {
    auto t = s[i].substr(s[i].size()-3, 3);

    for( auto v : mp[t] ) {
      G[i].emplace_back(v);
      to[i].emplace(v);
    }
  }

  rep( i, N ) if( !used[i] )
    dfs(i);

  rep( i, N ) {
    if( res[i] == 0 && draw[i] )
      puts("Draw");
    else if( res[i] == 0 )
      puts("Aoki");
    else
      puts("Takahashi");
  }

  return 0;
}