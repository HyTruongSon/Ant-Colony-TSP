// Software: Bitmask Dynamic Programming to solve Travelling Saleman Problem (only small cases N ~ 25)
// Author: Hy Truong Son
// Major: BSc. Computer Science
// Class: 2013 - 2016
// Institution: Eotvos Lorand University
// Email: sonpascal93@gmail.com
// Website: http://people.inf.elte.hu/hytruongson/
// Copyright 2015 (c) Hy Truong Son. All rights reserved. Use for academic purposes only.

#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <algorithm>

#define MaxN 22
#define MaxM 5000000
#define INF 1000000000

using namespace std;

// Input and output file name
const string input_file_name    = "Graph.INP";
const string output_file_name   = "DP.OUT";

// Global variables
int width, height, n, m, res;
int c[MaxN][MaxN];
int dp[MaxN][MaxM];
int bit[MaxN];
struct point {
    int x, y;
};
point p[MaxN];

double FindLen(int x1, int y1, int x2, int y2){
    int dx = (x2 - x1) * (x2 - x1);
    int dy = (y2 - y1) * (y2 - y1);
    return sqrt(dx + dy);
}

int Round(double number){
    if (2 * number < 2 * (int)(number) + 1)
        return (int)(number);
    return (int)(number) + 1;
}

void input(){
    int i, j;
    cin >> width >> height >> n;
    for (i = 0; i < n; i++)
        cin >> p[i].x >> p[i].y;
    memset(c, 0, sizeof(c));
    for (i = 0; i < n; i++)
        for (j = i + 1; j < n; j++){
            c[i][j] = Round(FindLen(p[i].x, p[i].y, p[j].x, p[j].y));
            c[j][i] = c[i][j];
        }
}

void Dynamic_Programming(int s){
    int i, j, v;
    m = 1 << n;
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++) dp[i][j] = INF;
    dp[s][1 << s] = 0;

    for (j = 0; j < m; j++){
        v = j;
        for (i = 0; i < n; i++){
            bit[i] = v % 2;
            v /= 2;
        }
        if (j == m - 1){
            for (i = 0; i < n; i++)
                res = min(res, dp[i][j] + c[i][s]);
            break;
        }
        for (i = 0; i < n; i++)
            if (bit[i] == 1){
                if (dp[i][j] == INF) continue;
                for (v = 0; v < n; v++)
                    if (bit[v] == 0)
                        dp[v][j + (1 << v)] = min(dp[v][j + (1 << v)], dp[i][j] + c[i][v]);
            }
    }
}

void process(){
    res = INF;
    Dynamic_Programming(1);
    cout << res;
}

// +--------------+
// | Main Program |
// +--------------+

int main(int argc, char *argv[]){
    freopen(input_file_name.c_str(), "r", stdin);
    freopen(output_file_name.c_str(), "w", stdout);
    input();
    process();
}
