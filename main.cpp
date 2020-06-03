
#include <bits/stdc++.h>
#include "Trans.cpp"
using namespace std;

int main()
{
    Trans s;
    s.input();
    s.firstCheck();
    s.north_west_corner();
    vector<vector<cell>> vv= s.solve(s.second_table);
    for(auto a:vv)
    {
        for(auto b:a)
        {
            if(b.basic)
            cout<<b.val<<"\t";
            else cout<<0<<"\t";
        }
        cout<<endl;
    }
    return 0;
}
