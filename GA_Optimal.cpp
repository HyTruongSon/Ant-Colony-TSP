// Software: Genetic Algorithm to solve Travelling Saleman Problem
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

#define MaxN 444
#define nPop 20000
#define MaxTime 20000
#define INF 1000000000

using namespace std;

// Input and output file name
const string input_file_name    = "Graph.INP";
const string output_file_name   = "GA.OUT";

// Global variables
int width, height, n, m;
int c[MaxN][MaxN];
int Prefer[MaxN][MaxN];

// +-------------------+
// | A gene definition |
// +-------------------+

struct Gene {
    int Length;
    int Path[MaxN];

    bool operator == (const Gene &A) const{
        if (Length != A.Length) return false;
        for (int i = 0; i < n; i++)
            if (Path[i] != A.Path[i]) return false;
        return true;
    }

    bool operator < (const Gene &A) const{
        if (Length < A.Length) return true;
        return false;
    }

    bool operator > (const Gene &A) const{
        if (Length > A.Length) return true;
        return false;
    }
};

Gene Pop[nPop];
Gene BestGene;
Gene Current;

bool fr[MaxN];
int Path[MaxN];

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

void visit(int i){
    int u, v, MinC, next;
    bool same;

    if (i == n){
        same = false;
        for (v = 0; v < m; v++)
            if (Pop[v] == Current){
                same = true;
                break;
            }
        if (!same){
            u = Current.Path[n - 1];
            v = Current.Path[0];
            Current.Length += c[u][v];

            Pop[m] = Current;
            m++;
            if (Pop[m - 1] < BestGene) BestGene = Pop[m - 1];

            Current.Length -= c[u][v];
        }
        return;
    }

    u = Current.Path[i - 1];

    for (v = 0; v < n; v++){
        next = Prefer[u][v];
        if (!fr[next]) continue;

        fr[next] = false;
        Current.Path[i] = next;
        Current.Length += c[u][next];

        visit(i + 1);

        Current.Length -= c[u][next];
        fr[next] = true;

        if (m == nPop) break;
    }
}

void Init_Population(){
    int i, u, v;

    for (i = 0; i < n; i++){
        for (u = 0; u < n; u++) Prefer[i][u] = u;
        for (u = 0; u < n; u++)
            for (v = u + 1; v < n; v++)
                if (c[i][Prefer[i][u]] > c[i][Prefer[i][v]])
                    swap(Prefer[i][u], Prefer[i][v]);
    }

    m = 0;
    Current.Length = 0;
    BestGene.Length = INF;

    memset(fr, true, sizeof(fr));
    fr[0] = false;

    visit(1);
}

void Choose_Parent(Gene &First, Gene &Second, int time){
    int i, j;
    if (time % 2 == 1){
        First.Length = INF;
        Second.Length = INF;
        for (i = 0; i < m; i++)
            if (Pop[i] < First){
                Second = First;
                First = Pop[i];
            }else
                if (Pop[i] < Second)
                    Second = Pop[i];
    }else{
        while (true){
            i = rand() % m;
            j = rand() % m;
            if (i != j){
                First = Pop[i];
                Second = Pop[j];
                break;
            }
        }
    }
}

void ReCalLength(Gene &Child){
    int i, j, v;
    Child.Length = 0;
    for (v = 0; v < n; v++){
        i = Child.Path[v];
        j = Child.Path[(v + 1) % n];
        Child.Length += c[i][j];
    }
}

void Crossover(Gene First, Gene Second, Gene &Child){
    int i, j, v, Pos1, Pos2;

    memset(fr, true, sizeof(fr));
    for (i = 0; i < n; i++) Child.Path[i] = -1;

    Pos1 = rand() % n;
    j = First.Path[Pos1];
    for (i = 0; i < n; i++)
        if (Second.Path[i] == j){
            Pos2 = i;
            break;
        }

    fr[j] = false;
    i = Pos1;
    Child.Path[i] = j;

    Pos1--;
    Pos2++;
    j = 0;
    while (true){
        j++;
        if (i - j < 0) break;
        if (i + j >= n) break;
        if (Pos1 < 0) break;
        if (Pos2 >= n) break;

        while (Pos1 >= 0){
            v = First.Path[Pos1];
            Pos1--;
            if (fr[v]){
                Child.Path[i - j] = v;
                fr[v] = false;
                break;
            }
        }

        while (Pos2 < n){
            v = Second.Path[Pos2];
            Pos2++;
            if (fr[v]){
                Child.Path[i + j] = v;
                fr[v] = false;
                break;
            }
        }
    }

    for (v = 0; v < n; v++)
        if (Child.Path[v] == -1)
            for (i = 0; i < n; i++)
                if (fr[i]){
                    Child.Path[v] = i;
                    fr[i] = false;
                    break;
                }

    ReCalLength(Child);
}

void Mutation(Gene &Child){
    int time, i, j, v, t, a, b, x, y;
    bool found;

    while (true){
        found = false;
        for (i = 0; i < n; i++)
            for (j = i + 1; j < n; j++){
                a = Child.Path[i];
                b = Child.Path[(i + 1) % n];
                x = Child.Path[j];
                y = Child.Path[(j + 1) % n];

                if (a == y) continue;
                if (b == x) continue;

                if (c[a][b] + c[x][y] > c[a][x] + c[b][y]){
                    found = true;
                    for (v = 0; v < n; v++) Path[v] = Child.Path[v];
                    Child.Path[0] = a;
                    v = 0;

                    t = j;
                    while (true){
                        v++;
                        Child.Path[v] = Path[t];
                        if (Path[t] == b) break;
                        t = (t - 1 + n) % n;
                    }

                    t = (j + 1) % n;
                    while (true){
                        v++;
                        Child.Path[v] = Path[t];
                        t = (t + 1) % n;
                        if (Path[t] == a) break;
                    }

                    ReCalLength(Child);
                }
            }
        if (!found) break;
    }
}

void Genetic_Algorithm(){
    int i, j, time, MaxLength;
    Gene First, Second;
    Gene Child;

    for (i = 0; i < m; i++){
        Mutation(Pop[i]);
        if (Pop[i] < BestGene){
            BestGene = Pop[i];
            cout << "Current best gene length: " << BestGene.Length << "\n";
        }
    }

    for (time = 1; time <= MaxTime; time++){
        Choose_Parent(First, Second, time);
        Crossover(First, Second, Child);
        Mutation(Child);

        if (Child < BestGene) BestGene = Child;

        MaxLength = -INF;
        for (i = 0; i < m; i++)
            if (MaxLength < Pop[i].Length){
                MaxLength = Pop[i].Length;
                j = i;
            }
        Pop[j] = Child;

        cout << "Current best gene length: " << BestGene.Length << "\n";
    }
}

void output(){
    freopen(output_file_name.c_str(), "w", stdout);
    cout << BestGene.Length << "\n";
    for (int i = 0; i < n; i++)
        cout << BestGene.Path[i] << " ";
}

// +--------------+
// | Main Program |
// +--------------+

int main(int argc, char *argv[]){
    freopen(input_file_name.c_str(), "r", stdin);

    input();
    Init_Population();
    Genetic_Algorithm();
    output();
}
