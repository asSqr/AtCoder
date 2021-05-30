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

struct Tup {
  ll first, second;
  ll idx;

  Tup(ll f, ll s, ll i)
  : first(f), second(s), idx(i)
  {}

  bool operator< ( Tup t ) const {
    return P(first, second) < P(t.first, t.second);
  }
};

ll N;
std::vector<ll> x, y;
std::vector<Tup> ps, qs;

ll dist( Tup p, Tup q ) {
  return std::max(llabs(p.first-q.first), llabs(p.second-q.second));
}

bool eqPr( P p, P q ) {
  std::vector<ll> ps = {p.first, p.second};
  std::vector<ll> qs = {q.first, q.second};

  std::sort(all(ps));
  std::sort(all(qs));

  return ps[0] == qs[0] && ps[1] == qs[1];
}

int main() {
  std::cin >> N;

  x.resize(N);
  y.resize(N);

  rep( i, N )
    std::cin >> x[i] >> y[i], ps.emplace_back(x[i], y[i], i), qs.emplace_back(y[i], x[i], i); 

  std::sort(all(ps));
  std::sort(all(qs));

  P pr;

  if( ps[N-1].first-ps[0].first > qs[N-1].first-qs[0].first ) {
    pr = P( ps[N-1].idx, ps[0].idx );
  } else {
    pr = P( qs[N-1].idx, qs[0].idx );
  }

  ll s = 0, t = N-1;
  ll ans = std::min(ps[N-1].first-ps[0].first, qs[N-1].first-qs[0].first);

  while( t-s >= 2 ) {
    std::vector<ll> ds;
    std::vector<P> bs;

    if( s+1 < t && !eqPr(pr, P(ps[t].idx, ps[s+1].idx)) )
      ds.emplace_back(dist(ps[t], ps[s+1])), bs.emplace_back(s+1, t);
      
    if( s < t-1 && !eqPr(pr, P(ps[t-1].idx, ps[s].idx)) )
      ds.emplace_back(dist(ps[t-1], ps[s])), bs.emplace_back(s,t-1);

    if( !ds.empty() ) {
      ll idx = std::max_element(all(ds))-ds.begin();
      chmax( ans, ds[idx] );
      s = bs[idx].first;
      t = bs[idx].second;

      break;
    } else {
      break;
    }
  }

  while( t-s >= 2 ) {
    std::vector<ll> ds;
    std::vector<P> bs;

    if( s+1 < t && !eqPr(pr, P(qs[t].idx, qs[s+1].idx)) )
      ds.emplace_back(dist(qs[t], qs[s+1])), bs.emplace_back(s+1, t);
      
    if( s < t-1 && !eqPr(pr, P(qs[t-1].idx, qs[s].idx) ) )
      ds.emplace_back(dist(qs[t-1], qs[s])), bs.emplace_back(s,t-1);

    if( !ds.empty() ) {
      ll idx = std::max_element(all(ds))-ds.begin();
      chmax( ans, ds[idx] );
      s = bs[idx].first;
      t = bs[idx].second;

      break;
    } else {
      break;
    }
  }

  std::cout << ans << endl;

  return 0;
}