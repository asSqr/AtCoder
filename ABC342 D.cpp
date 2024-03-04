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
ll A[250010];
ll square[250010];

std::vector<ll> divisors(ll x) {
    std::vector<ll> ret;

    for (ll i = 1; i*i <= x; ++i) {
        if (x%i == 0) {
            ret.emplace_back(i);

            if (i != x/i) {
                ret.emplace_back(x/i);
            }
        }
    }

    return ret;
}

ll maxA;
std::vector<ll> xs;
std::map<ll, ll> cnt;
ll zero;

int main() {
    std::cin >> N;

    rep( i, N ) {
        std::cin >> A[i];

        if (!A[i])
            ++zero;

        chmax(maxA, A[i]);
    }

    for (ll i = 1; i*i <= maxA; ++i) {
        square[i*i] = true;
    }

    rep( i, N ) {
        if (!A[i])
            continue;

        auto ds = divisors(A[i]);

        ll maxSq = 1;

        for ( auto d : ds ) {
            if (!square[d])
                continue;

            chmax(maxSq, d);
        }

        ++cnt[A[i] / maxSq];
    }

    ll ans = zero * (N-1) - zero * (zero - 1) / 2;

    itr (it, cnt) {
        ans += it->second * (it->second-1) / 2;
    }

    std::cout << ans << endl;

    return 0;
}