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

std::string S;

ll mk( ll x, ll y, ll z ) {
  return x*100+y*10+z;
}

using Tup = std::tuple<ll, ll, ll>;

ll cntW[12];

int main() {
  std::cin >> S;

  std::vector<ll> vs;

  rep( i, S.size() ) {
    ++cntW[S[i]-'0'];
  }

  if( S.size() == 1 ) {
    if( S[0] == '8' )
      std::cout << "Yes" << endl;
    else
      std::cout << "No" << endl;

    return 0;
  } else if( S.size() == 2 ) {
    ll x = S[0]-'0', y = S[1]-'0';

    if( mk(0,x,y)%8 == 0 || mk(0,y,x)%8 == 0 )
      std::cout << "Yes" << endl;
    else
      std::cout << "No" << endl;

    return 0;
  }

  std::set<Tup> st;

  repi( i, 1, 10 ) repi( j, 1, 10 ) repi( k, 1, 10 ) {
    ll x = i, y = j, z = k;

    if( mk(i,j,k) % 8 == 0 )
      st.emplace(i,j,k);
  }

  for( auto [x,y,z] : st ) {
    ll cnt[12] = {0};
    ++cnt[x];
    ++cnt[y];
    ++cnt[z];

    bool fl = true;

    rep( i, 10 )
      fl &= cnt[i] <= cntW[i];

    if( fl ) {
      std::cout << "Yes" << endl;

      return 0;
    }
  }

  std::cout << "No" << endl;

  return 0;
}