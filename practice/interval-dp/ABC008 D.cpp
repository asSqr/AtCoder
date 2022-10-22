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

ll W, H;
ll N;
std::vector<ll> xs, ys;
std::vector<P> ps;
ll dp[64][64][64][64];

int main() {
    std::cin >> W >> H;

    std::cin >> N;

    xs.emplace_back(0);
    ys.emplace_back(0);
    xs.emplace_back(W+1);
    ys.emplace_back(H+1);

    rep( i, N ) {
        ll X, Y;

        std::cin >> X >> Y;

        xs.emplace_back(X);
        ys.emplace_back(Y);
        ps.emplace_back(X, Y);
    }

    std::sort(all(xs));
    std::sort(all(ys));

    xs.erase(std::unique(all(xs)), xs.end());
    ys.erase(std::unique(all(ys)), ys.end());

    ll w = xs.size();
    ll h = ys.size();

    repi( h1, 1, h+1 ) repi( w1, 1, w+1 ) rep( i1, h ) rep( j1, w ) {
        ll i2 = i1 + h1;
        ll j2 = j1 + w1;

        if (i2 >= h || j2 >= w)
            continue;

        rep( i, N ) {
            ll x = ps[i].first;
            ll y = ps[i].second;

            ll idxX = std::lower_bound(all(xs), x)-xs.begin();
            ll idxY = std::lower_bound(all(ys), y)-ys.begin();

            if( !(xs[j1] < x && x < xs[j2] && ys[i1] < y && y < ys[i2]) )
                continue;

            chmax(dp[i1][j1][i2][j2],
                dp[i1][j1][idxY][idxX]
                + dp[i1][idxX][idxY][j2]
                + dp[idxY][j1][i2][idxX]
                + dp[idxY][idxX][i2][j2]
                + ys[i2]-ys[i1]-1 + xs[j2]-xs[j1]-1 - 1);
        }
    }

    std::cout << dp[0][0][h-1][w-1] << endl;

    return 0;
}