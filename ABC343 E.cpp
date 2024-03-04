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

ll V[3];

int main() {
    rep( i, 3 )
        std::cin >> V[i];

    auto ds = divisors(V[2]);

    for (auto d1 : ds) {
        ll dx = V[2] / d1;

        auto dds = divisors(dx);

        for (auto d2 : dds) {
            ll d3 = dx / d2;

            if (d1 > 7 || d2 > 7 || d3 > 7)
                continue;

            ll y = (7-d1) * d2 * d3 + d1 * (7-d2) * d3 + d1 * d2 * (7-d3);

            if (V[1] <= y && 3*7*7*7 == V[0] + 2 * V[1] + 3 * V[2] ) {
                puts("Yes");

                ll diff = y-V[1];
                std::vector<ll> es = {7-d1, 7-d2, 7-d3};

                for (auto &e : es) {
                    if (diff > 0) {
                        diff -= std::min(e, diff);
                        e = std::min(e, diff);
                    }
                }

                // 7-d1 x d2(+) x d3(+)
                // d1(-) x 7-d2 x d3(-)
                // d1(+) x d2(-) x 7-d3
                printf("%lld %lld %lld %lld %lld %lld %lld %lld %lld\n", d1-7, d2+es[1]-7, 0ll, d1+es[0]-7, 0ll, d3-7, 0ll, d2-7, d3+es[2]-7);

                return 0;
            }
        }
    }

    puts("No");

    return 0;
}