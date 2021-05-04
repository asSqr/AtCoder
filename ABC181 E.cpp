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
ll H[200010], W[200010];
std::map<ll, ll> mp;
ll S[200010], cS[200010];
std::set<ll> ls, rs;

int main() {
  std::cin >> N >> M;

  rep( i, N )
    std::cin >> H[i];
  rep( i, M )
    std::cin >> W[i];

  std::sort(H, H+N);

  std::vector<ll> ds, rs;

  ll sum = 0;
  for( ll i = 0; i < N; i += 2 ) {
    ds.emplace_back(sum);
    sum += llabs(H[i+1]-H[i]);
  }
  ds.emplace_back(sum);

  sum = 0;
  for( ll i = N-1; i > 0; i -= 2 ) {
    rs.emplace_back(sum);
    sum += llabs(H[i]-H[i-1]);
  }
  rs.emplace_back(sum);

  ll ans = INF;

  rep( i, M ) {
    ll idx = std::lower_bound(H, H+N, W[i])-H;

    ll tmp;

    if( idx&1 )
      tmp = ds[idx/2]+rs[(N-idx)/2]+llabs(H[idx-1]-W[i]);
    else
      tmp = ds[idx/2]+rs[(N-idx)/2]+llabs(H[idx]-W[i]);

    chmin( ans, tmp );

    //std::cout << "tmp: " << tmp << endl;
  }

  std::cout << ans << endl;

  return 0;
} 