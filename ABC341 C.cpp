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

const ll dx[4] = {0, 1, 0, -1}, dy[4] = {-1, 0, 1, 0};
const std::string URDL = "URDL";

ll H, W, N;
std::string T;
std::string S[510];

bool check( ll i, ll j ) {
    if (S[i][j] == '#') {
        return false;
    }

    rep( t, N ) {
        ll dir = URDL.find(T[t]);

        ll ni = i + dy[dir];
        ll nj = j + dx[dir];

        if (ni < 0 || ni >= H || nj < 0 || nj >= W) {
            continue;
        }

        if (S[ni][nj] == '#') {
            return false;
        }

        i = ni;
        j = nj;
    }

    return true;
}

int main() {
    std::cin >> H >> W >> N;

    std::cin >> T;

    rep( i, H ) {
        std::cin >> S[i];
    }

    ll ans = 0;

    rep( i, H ) rep( j, W ) {
        if (check(i, j)) {
            ++ans;
        }
    }

    std::cout << ans << endl;

    return 0;
}