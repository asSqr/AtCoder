#include <iostream>
#include <string>
#define repi(i,a,b) for(int i=(a);i<(b);++i)
#define rep(i,a) repi(i,0,a)

int N;
std::string S, prv;

int main()
{
    std::cin >> N >> S;
    int cntS = 0;

    rep( i, N )
    {
        if( S[i] == ')' )
        {
            if( cntS == 0 )
                prv += '(';
            else
                --cntS;
        }
        if( S[i] == '(' )
            ++cntS;
    }

    std::cout << prv+S+std::string(cntS, ')') << std::endl;

    return 0;
}