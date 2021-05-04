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
double xf, yf, xh, yh;

const double pi = acos(-1);

int main() {
  std::cin >> N >> xf >> yf >> xh >> yh;

  double vx = xh-xf;
  double vy = yh-yf;

  double theta = -double(N-2)/N*pi/2.0;

  double ax = cos(theta)*vx-sin(theta)*vy;
  double ay = sin(theta)*vx+cos(theta)*vy;

  double phi = 2.0*pi/N;
  double L = sqrt(vx*vx+vy*vy);
  double s = L*sin(phi/2.0);
  ax /= L;
  ay /= L;
  ax *= s;
  ay *= s;

  double x = xf+ax;
  double y = yf+ay;

  printf( "%.12f %.12f\n", x, y );

  return 0;
}