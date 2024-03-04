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
std::string S[30];
std::set<std::string> T;
ll cost[30][30];
ll dp[1ll<<20][25];

int main() {
    std::cin >> N;

    rep( i, N ) {
        std::cin >> S[i];
    }

    rep( i, N ) rep( j, N ) {
        if (i == j)
            continue;

        if (S[i].find(S[j]) != -1) {
            if (S[i].size() > S[j].size()) {
                T.emplace(S[i]);
            } else {
                T.emplace(S[j]);
            }
        }
    }

    N = T.size();

    ll ptr = 0;
    for (auto str : T) {
        S[ptr] = str;
        ++ptr;
    }

    rep( i, N ) rep( j, N ) {
        if (i == j)
            continue;

        rep( k, std::min(S[i].size(), S[j].size())) {
            if (S[i][S.size()-1-k] != S[j][k])
                break;

            ++cost[i][j];
        }
    }

    rep( S, 1ll<<N ) rep( v, N ) {
        if (!(S>>v&1))
            continue;

        rep( u, N ) {
            if (u == v)
                continue;

            if (S>>u&1)
                continue;

            chmax(dp[S|1ll<<u][u], dp[S][v] + cost[v][u]);
        }
    }

    ll ma = 0;

    rep( v, N )
        chmax( ma, dp[(1ll<<N)-1][v] );

    ll ans = 0;
    
    rep( i, N )
        ans += S[i].size();

    ans -= ma;

    std::cout << ans << endl;

    return 0;
}