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
std::string T;

bool check( const std::string &s ) {
  bool fl = true;

  if( s.size()%3 )
    return false;
  
  for( ll i = 0; i < s.size(); ++i ) {
    if( i+2 >= s.size() )
      break;

    fl &= s.substr(i,3) == "110";
    i += 2;
  }

  return fl;
}

int main() {
  std::cin >> N >> T;

  if( N == 1 ) {
    if( T[0] == '0' ) {
      std::cout << 10000000000ll << endl;
    } else {
      std::cout << 20000000000ll << endl;
    }

    return 0;
  }

  bool fl = true;

  fl &= check(T);

  if( fl ) {
    std::cout << 10000000000ll-(N/3-1) << endl;

    return 0;
  }

  fl = false;

  ll x = 0, y = 0;

  fl |= T[0] == '0' || T.substr(0,2) == "10";

  if( T[0] == '0' || T.substr(0,2) == "10" ) {
    x = T[0]=='0'?1:2;
  }

  fl |= T.back() == '1' || T.substr(N-2,2) == "11";

  if( T.back() == '1' || T.substr(N-2,2) == "11") {
    y = T.substr(N-2,2)=="11"?2:1;
  }

  if( !fl ) {
    std::cout << 0 << endl;

    return 0;
  }
  
  if( N-x-y > 0 )
    fl &= check(T.substr(x, N-x-y));

  if( !fl ) {
    std::cout << 0 << endl;

    return 0;
  }

  ll X = N;

  if( x )
    X += 3-x;
  if( y )
    X += 3-y;

  std::cout << 10000000000ll-(X/3-1) << endl;
  
  return 0;
}