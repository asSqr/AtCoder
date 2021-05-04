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

const ll mod = 1000000007;
struct mint {
  ll x; // typedef long long ll;
  mint(ll x=0):x((x%mod+mod)%mod){}
  mint operator-() const { return mint(-x);}
  mint& operator+=(const mint a) {
    if ((x += a.x) >= mod) x -= mod;
    return *this;
  }
  mint& operator-=(const mint a) {
    if ((x += mod-a.x) >= mod) x -= mod;
    return *this;
  }
  mint& operator*=(const mint a) { (x *= a.x) %= mod; return *this;}
  mint operator+(const mint a) const { return mint(*this) += a;}
  mint operator-(const mint a) const { return mint(*this) -= a;}
  mint operator*(const mint a) const { return mint(*this) *= a;}
  mint pow(ll t) const {
    if (!t) return 1;
    mint a = pow(t>>1);
    a *= a;
    if (t&1) a *= *this;
    return a;
  }

  // for prime mod
  mint inv() const { return pow(mod-2);}
  mint& operator/=(const mint a) { return *this *= a.inv();}
  mint operator/(const mint a) const { return mint(*this) /= a;}
};
std::istream& operator>>(std::istream& is, mint& a) { return is >> a.x;}
std::ostream& operator<<(std::ostream& os, const mint& a) { return os << a.x;}

struct combination {
  std::vector<mint> fact, ifact;
  combination(int n):fact(n+1),ifact(n+1) {
    assert(n < mod);
    fact[0] = 1;
    for (int i = 1; i <= n; ++i) fact[i] = fact[i-1]*i;
    ifact[n] = fact[n].inv();
    for (int i = n; i >= 1; --i) ifact[i-1] = ifact[i]*i;
  }
  mint operator()(int n, int k) {
    if (k < 0 || k > n) return 0;
    return fact[n]*ifact[k]*ifact[n-k];
  }
};

ll N;
ll A[10];
ll c[10];
mint ans = 0;
std::vector<ll> arr;

mint g( const std::vector<std::vector<ll>> &ids ) {
  ll L = ids.size();

  std::vector<ll> ub( L+10, INF );
  
  rep( i, ids.size() ) {
    for( auto j : ids[i] )
      chmin( ub[i], A[j] );
  }

  ll M = arr.size()-1;

  std::vector<std::vector<mint>> dp( N+10, std::vector<mint>( M+10, 0 ) );
  dp[0][0] = 1;

  rep( i, L ) {
    rep( j, M ) {
      mint num = 1;
      mint w = arr[j+1]-arr[j];
      mint prod = 1;

      for( ll pi = i; pi >= 0; --pi ) {
        if( arr[j] >= ub[pi]+1 || arr[j+1] <= 1 )
          break;

        // comb(w,num)
        prod /= num;
        prod *= w;
        num += 1;
        w -= 1;

        rep( pj, j ) {
          dp[i+1][j] += dp[pi][pj]*prod;
        }
      }

      //printf( "dp[%lld][%lld] = %lld\n", i, j, dp[i][j].x );
    }
  }

  mint ret = 0;

  rep( j, M )
    ret += dp[L][j];//, printf( "dp[%lld][%lld] = %lld\n", L, j, dp[L][j].x );

  return ret;
}

void f() {
  ll ma = 0;

  rep( i, N )
    chmax( ma, c[i] );

  std::vector<std::vector<ll>> ids( ma+1 );

  rep( i, N )
    ids[c[i]].emplace_back( i );

  do {
    std::vector<ll> vs( N );
    std::vector<ll> dp( N );

    rep( i, ma+1 ) {
      for( ll j : ids[i] ) {
        vs[j] = i;
      }
    }

    rep( i, N ) {
      dp[i] = 1;

      rep( j, i ) if( vs[j] < vs[i] )
        chmax( dp[i], dp[j]+1 );
    }

    ll len = 0;

    rep( i, N )
      chmax( len, dp[i] );

    //std::cout << vs << ' ' << len << ' ' << g(ids) << endl; 

    ans += g(ids)*len;
  } while( std::next_permutation(all(ids)) );

  return;
}

void rec( ll i, ll ma ) {
  if( i == N ) {
    f();

    return;
  }

  rep( j, ma+1 ) {
    c[i] = j;
    rec( i+1, j==ma?ma+1:ma );
  }
}

int main() {
  std::cin >> N;

  mint den = 1;
  ll ma = 0;

  arr.emplace_back(-1);
  arr.emplace_back(1);

  rep( i, N ) {
    std::cin >> A[i];
    
    den *= A[i];
    arr.emplace_back(A[i]+1);

    chmax( ma, A[i] );
  }

  std::sort(all(arr));
  arr.erase(std::unique(all(arr)), arr.end());

  rec( 0, 0 );

  std::cout << ans/den << endl;

  return 0;
}