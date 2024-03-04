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

constexpr ll INF = 1ll<<60;

template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return 1; } return 0; }

template<class S, class T>
std::ostream& operator<< ( std::ostream& out, const std::pair<S,T>& a )
{ std::cout << '(' << a.first << ", " << a.second << ')'; return out; }

template<class T>
std::ostream &operator<< ( std::ostream& out, const std::vector<T>& a )
{ std::cout << '['; rep( i, a.size() ){ std::cout << a[i]; if( i != a.size()-1 ) std::cout << ", "; } std::cout << ']'; return out; }

struct Edge {
    ll l, d, k, c;

    bool operator< (const Edge &rhs) const {
        return std::make_pair(std::make_pair(l, d), std::make_pair(k, c)) < std::make_pair(std::make_pair(rhs.l, rhs.d), std::make_pair(rhs.k, rhs.c));
    }
};

using P = std::pair<ll, Edge>;
using PP = std::pair<ll, ll>;

ll N, M;
std::vector<P> G[200010];
std::vector<ll> dist(200010);
std::priority_queue<PP, std::vector<PP>, std::greater<PP>> pque;

int main() {
    std::cin >> N >> M;

    rep( i, M ) {
        ll l, d, k, c, A, B;
        std::cin >> l >> d >> k >> c >> A >> B;

        --A; --B;

        G[B].push_back({A, {l, d, k, c}});
    }

    rep( t, N )
        dist[t] = INF;

    dist[N-1] = -INF;

    pque.emplace( dist[N-1], N-1 );

    while( !pque.empty() ) {
        PP p = pque.top(); pque.pop();
        ll d = p.first, v = p.second;

        if( d > dist[v] )
            continue;

        for( auto u : G[v] ) {
            Edge e = u.second;
            ll timeLimit = -(d + e.c);

            if (timeLimit < e.l) {
                continue;
            }

            ll nd = -(std::min((timeLimit - e.l) / e.d, e.k - 1) * e.d + e.l);

            if( chmin( dist[u.first], nd ) )
                pque.emplace( dist[u.first], u.first );
        }
    }

    rep( i, N-1 ) {
        if (dist[i] == INF) {
            std::cout << "Unreachable" << endl;
        } else {
            std::cout << -dist[i] << endl;
        }
    }

    return 0;
}