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

std::string S[3];
std::set<ll> st;
std::vector<ll> vs;

int main() {
  rep( i, 3 ) {
    std::cin >> S[i];

    rep( j, S[i].size() )
      st.emplace(S[i][j]-'a');
  }

  for( auto ch : st )
    vs.emplace_back(ch);

  if( vs.size() > 10 ) {
    std::cout << "UNSOLVABLE" << endl;
    
    return 0;
  }

  ll x = vs.size();

  rep( i, 10-x )
    vs.emplace_back(10000+i);

  std::sort(all(vs));

  do {
    std::vector<ll> us;

    rep( i, 3 ) {
      ll q = 0;

      rep( j, S[i].size() ) {
        q *= 10;

        ll p = 0;
        
        rep( k, 10 ) if( vs[k] == (S[i][j]-'a') )
          p = k;

        if( !j && !p ) {
          goto end;
        }

        q += p;
      }

      us.emplace_back(q);
    }

    if( us[0]+us[1] == us[2] ) {
      rep( i, 3 )
        std::cout << us[i] << endl;

      return 0;
    }

end:;
  } while( std::next_permutation(all(vs)) );

  std::cout << "UNSOLVABLE" << endl;

  return 0;
}