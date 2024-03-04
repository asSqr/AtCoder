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

ll N, L, D;
double xdp[500010], ydp[500010], sydp[500010];
double dsum = 0;

int main() {
    std::cin >> N >> L >> D;

    ll cnt = 0;

    ydp[0] = 1;
    dsum += ydp[0];
    ++cnt;

    repi( i, 1, 200010 ) {
        ydp[i] += dsum / D;

        if ( i < L ) {
            dsum += ydp[i];
        }

        ++cnt;

        if (cnt > D) {
            dsum -= ydp[i-D];
            --cnt;
        }
    }

    rep( i, L ) {
        ydp[i] = 0;
    }

    repi( i, L+D, 200010 ) {
        ydp[i] = 0;
    }

    rep( i, 200010 ) {
        sydp[i+1] = sydp[i] + ydp[i];
    }

    cnt = 0;
    dsum = 0;

    xdp[N] = 1 - ydp[N];
    dsum = xdp[N];
    ++cnt;

    for (ll i = N-1; i >= 0; --i) {
        xdp[i] = std::max(dsum / D, 1 - (sydp[N+1]-sydp[i]));

        dsum += xdp[i];
        ++cnt;

        if (cnt > D) {
            dsum -= xdp[i+D];
            --cnt;
        }
    }

    printf("%.15f\n", xdp[0]);

    return 0;
}