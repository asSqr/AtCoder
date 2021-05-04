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

template<typename T>
struct MP {
  int n;
  T t;
  std::vector<int> a;
  MP() {}
  MP(const T& t): t(t) {
    n = t.size();
    a = std::vector<int>(n+1);
    a[0] = -1;
    int j = -1;
    for (int i = 0; i < n; ++i) {
      while (j != -1 && t[j] != t[i]) j = a[j];
      j++;
      a[i+1] = j;
    }
  }
  int operator[](int i) { return a[i];}
  std::vector<int> findAll(const T& s) {
    std::vector<int> res;
    int j = 0;
    for (int i = 0; i < s.size(); ++i) {
      while (j != -1 && t[j] != s[i]) j = a[j];
      j++;
      if (j == n) {
        res.push_back(i-j+1);
        j = a[j];
      }
    }
    return res;
  }
};

ll N;
std::vector<ll> a, b, c, d;

int main() {
  std::cin >> N;

  a.resize(N);

  rep( i, N )
    std::cin >> a[i];
  
  b.resize(N);

  rep( i, N )
    std::cin >> b[i];

  c.resize(N);
  d.resize(N);

  rep( i, N ) {
    c[i] = a[i]^a[(i+1)%N];
    d[i] = b[i]^b[(i+1)%N];
  }

  MP<std::vector<ll>> mp(d);

  std::vector<ll> c2;

  rep( j, 2 ) rep( i, N )
    c2.emplace_back(c[i]);

  c2.pop_back();

  auto vs = mp.findAll(c2);

  for( auto k : vs ) {
    ll x = b[0]^a[k%N];

    std::cout << k << ' ' << x << endl;
  }

  return 0;
}