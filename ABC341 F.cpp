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
using PP = std::pair<P, ll>;

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
std::vector<ll> G[5010];
std::vector<ll> W(5010), A(5010);
ll dp[5010];
ll kdp[5010][5010];

ll rec(ll v) {
    if (dp[v] != -1) {
        return dp[v];
    }

    std::vector<ll> tmpA(N, 0);
    tmpA[v] = 1;

    ll ret = 0;

    --tmpA[v];
    ++ret;

    std::vector<P> ps;
    
    for( auto u : G[v] ) {
        if (W[u] >= W[v]) {
            continue;
        }

        ps.emplace_back(W[u], rec(u));
    }

    rep( i, ps.size() ) {
        rep( j, W[v]+1 ) {
            if (j-ps[i].first >= 0) {
                kdp[i+1][j] = std::max(kdp[i][j], kdp[i][j-ps[i].first] + ps[i].second);
            } else {
                kdp[i+1][j] = kdp[i][j];
            }
        }
    }

    ret += kdp[ps.size()][W[v]-1];

    return dp[v] = ret;
}

int main() {
    std::cin >> N >> M;

    W.resize(N);
    A.resize(N);

    rep( i, M ) {
        ll u, v;

        std::cin >> u >> v;
        --u; --v;

        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }

    rep( i, N )
        std::cin >> W[i];

    rep( i, N )
        std::cin >> A[i];

    rep( i, N ) {
        dp[i] = -1;
    }

    ll ans = 0;

    rep( i, N ) {
        ans += A[i] * rec(i);
    }

    std::cout << ans << endl;

    return 0;
}