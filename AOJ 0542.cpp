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
using PP = std::pair<ll, P>;

constexpr ll INF = 1ll<<60;

template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return 1; } return 0; }

template<class S, class T>
std::ostream& operator<< ( std::ostream& out, const std::pair<S,T>& a )
{ std::cout << '(' << a.first << ", " << a.second << ')'; return out; }

template<class T>
std::ostream &operator<< ( std::ostream& out, const std::vector<T>& a )
{ std::cout << '['; rep( i, a.size() ){ std::cout << a[i]; if( i != a.size()-1 ) std::cout << ", "; } std::cout << ']'; return out; }

ll R;
ll W[2], H[2], X[2], Y[2];
ll L[2][1000][1000];

const ll dx[4] = { -1, 0, 1, 0 }, dy[4] = { 0, 1, 0, -1 };

ll dist[2][1000][1000];

std::vector<ll> ds[2];

void dijkstra(ll i) {
    std::priority_queue<PP, std::vector<PP>, std::greater<PP>> pque;

    rep( j, W[i] ) rep( k, H[i] )
        dist[i][j][k] = INF;

    dist[i][X[i]][Y[i]] = 1;

    pque.emplace( dist[i][X[i]][Y[i]], P( X[i], Y[i] ) );

    while( !pque.empty() ) {
        PP p = pque.top(); pque.pop();
        ll d = p.first;
        ll x = p.second.first, y = p.second.second;

        if( d > dist[i][x][y] )
            continue;

        rep( dir, 4 ) {
            ll nx = x + dx[dir], ny = y + dy[dir];

            if (nx < 0 || nx >= W[i] || ny < 0 || ny >= H[i])
                continue;

            if( chmin( dist[i][nx][ny], std::max(d, L[i][nx][ny]) ) )
                pque.emplace( dist[i][nx][ny], P(nx, ny) );
        }
    }

    return;
}

int main() {
    while( std::cin >> R, R) {
        rep( i, 2 ) {
            std::cin >> W[i] >> H[i] >> X[i] >> Y[i];
            --X[i]; --Y[i];

            rep( j, H[i] ) {
                rep( k, W[i] ) {
                    std::cin >> L[i][k][j];
                }
            }
        }

        dijkstra(0);
        dijkstra(1);

        rep( i, 2 )
            ds[i].clear();

        rep( i, 2 ) rep( j, W[i] ) rep( k, H[i] ) {
            ds[i].emplace_back(dist[i][j][k]);
        }
        
        rep( i, 2 )
            std::sort(all(ds[i]));

        ll ans = INF;

        rep( i, ds[0].size() ) {
            ll l = ds[0][i];

            ll cnt0 = std::upper_bound(all(ds[0]), l) - ds[0].begin();
            
            if (R-cnt0 > 0 && R-cnt0-1 >= ds[1].size()) {
                continue;
            }

            ll l2 = R-cnt0 > 0 ? ds[1][R-cnt0-1] : 0;

            chmin( ans, l + l2 );
        }

        std::cout << ans << endl;
    }

    return 0;
}