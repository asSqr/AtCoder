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

// SP(P(最初の文字の0/1, 最後の文字の0/1), いい文字列かどうか)
using FP = std::pair<short, short>;
using SP = std::pair<FP, bool>;

SP e() {
    return SP(FP(-1, -1), true);
}

SP op(SP a, SP b) {
    if (a == e()) {
        return b;
    } else if (b == e()) {
        return a;
    }

    return SP(FP(a.first.first, b.first.second), a.second && b.second && (a.first.second == -1 || b.first.first == -1 || a.first.second != b.first.first));
}

FP flip(FP x) {
    if (x == FP(-1, -1)) {
        return x;
    }

    return FP(x.first ^ 1, x.second ^ 1);
}

SP mapping(bool f, SP x) {
    if (f) {
        return SP(flip(x.first), x.second);
    } else {
        return x;
    }
}

bool composition(bool f, bool g) {
    return f ^ g;
}

bool id() {
    return false;
}

atcoder::lazy_segtree<SP, op, e, bool, mapping, composition, id> seg(500010);
ll N, Q;
std::string S;

int main() {
    std::cin >> N >> Q >> S;

    rep( i, N ) {
        bool fl = bool(S[i]-'0');

        seg.set(i, SP(FP(fl, fl), true));
    }

    rep( q, Q ) {
        ll t, L, R;

        std::cin >> t >> L >> R;
        --L;

        if (t == 1) {
            seg.apply(L, R, true);
        } else {
            std::cout << (seg.prod(L, R).second ? "Yes" : "No") << endl;
        }
    }

    return 0;
}