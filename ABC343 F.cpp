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
#include <atcoder/all>
#define repi(i,a,b) for(ll i=(a);i<(b);++i)
#define rep(i,a) repi(i,0,a)
#define repdi(i,a,b) for(ll i=(a)-1;i>=(b);--i)
#define repd(i,a) repdi(i,a,0)
#define itr(it,a) for( auto it = (a).begin(); it != (a).end(); ++it )
#define ritr(it,a) for( auto it = (a).rbegin(); it != (a).rend(); ++it )
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

// ((1stの数，個数), (2ndの数, 個数))
using SP = std::pair<P, P>;

SP e() {
    return SP(P(-1, 0), P(-1, 0));
}

SP op(SP a, SP b) {
    if (a == e()) {
        return b;
    } else if (b == e()) {
        return a;
    }

    std::map<ll, ll> cnt;
    
    cnt[a.first.first] += a.first.second;
    cnt[a.second.first] += a.second.second;
    cnt[b.first.first] += b.first.second;
    cnt[b.second.first] += b.second.second;

    ll ptr = 0;
    P p[2];

    ritr(it, cnt) {
        p[ptr] = *it;

        ++ptr;

        if (ptr >= 2)
            break;
    }

    return SP(p[0], p[1]);
}

atcoder::segtree<SP, op, e> seg(200010);

ll N, Q;

int main() {
    std::cin >> N >> Q;

    rep( i, N ) {
        ll A;
        std::cin >> A;

        seg.set(i, SP(P(A, 1), P(-1, 0)));
    }

    rep( q, Q ) {
        ll t;
        std::cin >> t;

        if (t == 1) {
            ll p, x;
            std::cin >> p >> x;
            --p;

            seg.set(p, SP(P(x, 1), P(-1, 0)));
        } else {
            ll l, r;
            std::cin >> l >> r;
            --l;

            SP sp = seg.prod(l, r);

            std::cout << sp.second.second << endl;
        }
    }

    return 0;
}