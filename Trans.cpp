#include <bits/stdc++.h>
#define inf 100000000
using namespace std;
struct cell
{
    int transval;
    int val;
    bool basic;
};
class Trans
{
public:
    int fact, sup;
    int n, m;
    int cnt = 0;
    vector<vector<int>> main_table;
    vector<int> factories_max;
    vector<int> sup_max;
    vector<vector<cell>> second_table;
    void firstCheck()
    {
        int f = 0, s = 0;
        for (auto a : factories_max)
        {
            f += a;
        }
        for (auto a : sup_max)
        {
            s += a;
        }
        if (s == f)
            return;
        else
        {
            int tmp = abs(f - s);
            if (f > s)
            {
                for (int i = 0; i < fact; i++)
                {
                    main_table[i].push_back(0);
                }
                sup_max.push_back(tmp);
                sup++;
            }
            else
            {
                vector<int> d;
                for (int i = 0; i < sup; i++)
                    d.push_back(0);
                main_table.push_back(d);
                factories_max.push_back(tmp);
                fact++;
            }
        }
        n = fact;
        m = sup;
    }
    void input()
    {
        cout << " enter number of factories  " << endl;
        cin >> fact;
        cout << "enter number of suppliers " << endl;
        cin >> sup;
        main_table.resize(fact);
        for (int i = 0; i < fact; i++)
        {
            main_table[i].resize(sup);
        }
        int x;
        for (int i = 0; i < fact; i++)
        {
            cout << "enter max products of factory " << i + 1 << endl;
            cin >> x;
            factories_max.push_back(x);
        }
        for (int i = 0; i < sup; i++)
        {
            cout << "enter max products of supplier " << i + 1 << endl;
            cin >> x;
            sup_max.push_back(x);
        }

        for (int i = 0; i < fact; i++)
        {
            for (int ii = 0; ii < sup; ii++)
            {
                cout << "enter the value of tranportation from factory " << i + 1 << " to supplier" << ii + 1 << endl;
                cin >> x;
                main_table[i][ii] = x;
            }
        }

        /*  for (int i = 0; i < fact; i++)
        {
            for (int ii = 0; ii < sup; ii++)
            {
                cout << main_table[i][ii] << " ";
            }
            cout << endl;
        }*/
    }
    void printvec()
    {
        cout << "////////////////////////////" << endl;
        for (int i = 0; i < fact; i++)
        {
            for (int ii = 0; ii < sup; ii++)
            {
                cout << second_table[i][ii].val << " ";
            }
            cout << endl;
        }
    }
    void north_west_corner()
    {
        vector<int> ff;
        vector<int> ss;
        for (int i = 0; i < fact; i++)
        {
            ff.push_back(factories_max[i]);
        }
        for (auto s : sup_max)
        {
            ss.push_back(s);
        }
        second_table.resize(fact);
        cell c;
        for (int i = 0; i < fact; i++)
        {
            for (int ii = 0; ii < sup; ii++)
            {
                c.transval = main_table[i][ii];
                c.val = NULL;
                c.basic = 0;
                second_table[i].push_back(c);
            }
        }

        int x = 0, y = 0;
        while (x < sup && y < fact)
        {
            int tmpx = ss[x];
            int tmpy = ff[y];
            if (tmpy < tmpx)
            {
                second_table[y][x].val = tmpy;
                second_table[y][x].basic = 1;
                ss[x] -= tmpy;
                ff[y] -= tmpy;
                y++;
            }
            else
            {
                second_table[y][x].val = tmpx;
                second_table[y][x].basic = 1;
                ss[x] -= tmpx;
                ff[y] -= tmpx;
                x++;
            }
        }
        // printvec();
    }

    bool finish(vector<vector<cell>> se)
    {
        for (int i = 0; i < fact; i++)
        {
            for (int ii = 0; ii < sup; ii++)
            {
                if (se[i][ii].val < 0)
                    return 0;
            }
        }
        cout<<"--------------result is--------------------- "<<endl;
        return 1;
    }
    pair<int, int> select(vector<vector<cell>> se)
    {
        int r = 0, c = 0;
        vector<int> rr, cc;
        for (int i = 0; i < fact; i++)
        {
            int tmp = 0;
            for (int ii = 0; ii < sup; ii++)
            {
                if (se[i][ii].basic == 1)
                    tmp++;
            }
            rr.push_back(tmp);
            r = max(r, tmp);
        }
        for (int i = 0; i < sup; i++)
        {
            int tmp = 0;
            for (int ii = 0; ii < fact; ii++)
            {
                if (se[ii][i].basic == 1)
                    tmp++;
            }
            cc.push_back(tmp);
            c = max(c, tmp);
        }
        if (r > c)
        {
            for (int i = 0; i < fact; i++)
            {
                if (rr[i] == r)
                {
                    return {i, 0};
                }
            }
        }
        else
        {
            for (int i = 0; i < sup; i++)
            {
                if (cc[i] == c)
                {
                    return {i, 1};
                }
            }
        }
    }

    void update_U_V(vector<int> &U, vector<int> &V, vector<vector<cell>> se, pair<int, int> tmp, int val)
    {
        // cout<<val<<endl;
        if (tmp.second == 0)
        {
            if (U[tmp.first] != inf)
                return;
            U[tmp.first] = val;
            for (int i = 0; i < sup; i++)
            {
                if (se[tmp.first][i].basic == 1)
                {
                    int tt = se[tmp.first][i].transval - val;
                    update_U_V(U, V, se, {i, 1}, tt);
                }
            }
        }
        else
        {
            if (V[tmp.first] != inf)
                return;
            V[tmp.first] = val;
            for (int i = 0; i < fact; i++)
            {
                if (se[i][tmp.first].basic == 1)
                {
                    int tt = se[i][tmp.first].transval - val;
                    update_U_V(U, V, se, {i, 0}, tt);
                }
            }
        }
    }
    vector<pair<int, int>> findloop(vector<vector<cell>> se, int dir, set<pair<int, int>> vis, pair<int, int> start, pair<int, int> cur, int ccc)
    {
        // cout<<cur.first<<" "<<cur.second<<" "<<dir<<endl;

        if (cur.first == start.first && cur.second == start.second && ccc >= 4 && ccc % 2 == 0)
        {
            vector<pair<int, int>> vec;
            // cout<<"5od ya"<<endl;
            vec.push_back({-1, -1});
            return vec;
        }
        else
        {
            if (vis.find({cur.first, cur.second}) != vis.end())
            {
                vector<pair<int, int>> v;
               // cout<<"7a7a"<<cur.first<<" "<<cur.second<<endl;
                return v;
            }
            vis.insert({cur.first, cur.second});
            if (dir == -1)
            {
                for (int i = 0; i < sup; i++)
                {
                    if (se[cur.first][i].basic == 1 || (start.first == cur.first && start.second == i))
                    {

                        vector<pair<int, int>> v = findloop(se, 1, vis, start, {cur.first, i}, ccc + 1);
                        if (v.size() > 0)
                        {
                            v.push_back(cur);
                            return v;
                        }

                    }
                }
                for (int i = 0; i < fact; i++)
                {
                    if (se[i][cur.second].basic == 1 || (start.first == i && start.second == cur.second))
                    {
                        vector<pair<int, int>> v = findloop(se, 2, vis, start, {i, cur.second}, ccc + 1);
                        if (v.size() > 0)
                        {
                            v.push_back(cur);
                            return v;
                        }
                    }
                }
            }
            else if (dir == 1)
            {
                for (int i = 0; i < fact; i++)
                {
                    if (se[i][cur.second].basic == 1 || (start.first == i && start.second == cur.second))
                    {
                        vector<pair<int, int>> v = findloop(se, 2, vis, start, {i, cur.second}, ccc + 1);
                        if (v.size() > 0)
                        {
                            v.push_back(cur);
                            return v;
                        }
                    }
                }
            }
            else
            {
                for (int i = 0; i < sup; i++)
                {
                    if (se[cur.first][i].basic == 1 || (start.first == cur.first && start.second == i))
                    {
                        vector<pair<int, int>> v = findloop(se, 1, vis, start, {cur.first, i}, ccc + 1);
                        if (v.size() > 0)
                        {
                            v.push_back(cur);
                            return v;
                        }
                    }
                }
            }
            vector<pair<int,int>>v;
            return v;
        }
    }
    vector<vector<cell>> solve(vector<vector<cell>> se)
    {
        vector<int> U(fact, inf);
        vector<int> V(sup, inf);
        pair<int, int> tmp = select(se);
        update_U_V(U, V, se, tmp, 0);
        //cout<<"U";
        //for(auto u:U)cout<<u<<" ";
        //cout<<endl;
       // cout<<"v";
       // for(auto v:V)cout<<v<<" ";
       // cout<<endl;
       // cout << tmp.first << " " << tmp.second << endl;
        for (int i = 0; i < fact; i++)
        {
            for (int ii = 0; ii < sup; ii++)
            {
                if (se[i][ii].basic == 0)
                {
                    se[i][ii].val = se[i][ii].transval - U[i] - V[ii];
                }
            }
        }
      /* for(int i=0;i<fact;i++)
       {
           for(int ii=0;ii<sup;ii++)
           {
               cout<<se[i][ii].val<<" ";
           }
           cout<<endl;
       }
       cout<<endl;*/
        if (finish(se))
        {
            return se;
        }
        else
        {
            int x, y;
            int mini = inf;
            for (int i = 0; i < fact; i++)
            {
                for (int ii = 0; ii < sup; ii++)
                {
                    if (mini > se[i][ii].val)
                    {
                        mini = se[i][ii].val;
                        x = ii;
                        y = i;
                    }
                    //cout<<se[i][ii].val<<" ";
                }
                // cout<<endl;
            }
           // cout<<"hhh"<<endl;
            set<pair<int, int>> ss;
           // cout<<y<<" "<<x<<endl;
            vector<pair<int, int>> res = findloop(se, -1, ss, {y, x}, {y, x}, 0);
            res.erase(res.begin());
            mini = inf;
            y=0;x=0;
           /* for(auto r:res)
            {
                cout<<r.first<<" "<<r.second<<endl;
            }*/
            for (int i = 0; i < res.size(); i += 2)
            {
                if (se[res[i].first][res[i].second].val < mini)
                {
                    mini = se[res[i].first][res[i].second].val;
                    y = res[i].first;
                    x = res[i].second;
                }
            }
            //cout<<"hhhh"<<endl;
            for (int i = 0; i < res.size(); i += 2)
            {
                se[res[i].first][res[i].second].val -= mini;
            }
            for (int i = 1; i < res.size(); i += 2)
            {
                se[res[i].first][res[i].second].val += mini;
            }
            //cout<<"hhhhh"<<endl;
            se[y][x].basic = 0;
            se[res[res.size()-1].first][res[res.size()-1].second].basic = 1;
            se[res[res.size()-1].first][res[res.size()-1].second].val = mini;
            return solve(se);
        }
        return se;
    }
};
/*
3 4 
12 17 11 
10 10 10 10
50 75 30 45 65 80 40 60 40 70 50 55
*/