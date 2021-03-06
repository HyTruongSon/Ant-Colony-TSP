// Software: Ant Colony algorithm to solve Travelling Saleman Problem
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
#include <time.h>

#define MaxN 111
#define nAnt 20
#define Iteration 2000
#define INF 1000000000

using namespace std;

// Input and output file name
const string input_file_name    = "Graph.INP";
const string output_file_name   = "AntColony.OUT";

// Constants for Ant Colony algorithm
double InitialPheromone = 0.8;
double anfa = -0.2;
double beta = 2.0;
double P = 0.8;
double Q = 0.1;

// Global variables
int n, width, height, Best;
int c[MaxN][MaxN];
struct point {
    int x, y;
};
point p[MaxN];
int StartPoint[nAnt];
double Pheromone[MaxN][MaxN];
int Path[MaxN];
int OldPath[MaxN];
int BestPath[MaxN];
double Delta[MaxN][MaxN];
bool Visited[MaxN];

double Visibility(int i, int j){
    return 1.0 / (double)(c[i][j]);
}

double Probability(double Pheromone, double anfa, double Visibility, double beta){
    return pow(Pheromone, anfa) * pow(Visibility, beta);
}

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

void init(){
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            Pheromone[i][j] = InitialPheromone;

    for (i = 0; i < nAnt; i++)
        StartPoint[i] = rand() % n;
}

void Mutation(int Path[], int &Current){
    int i, j, x, y, u, v, t, h;
    bool stop;

    while (true){
        stop = true;

        for (i = 0; i < n; i++)
            for (j = i + 2; j < n; j++){
                x = Path[i];
                y = Path[(i + 1) % n];
                u = Path[j];
                v = Path[(j + 1) % n];

                if (c[x][u] + c[y][v] < c[x][y] + c[u][v]){
                    stop = false;

                    for (t = 0; t < n; t++) OldPath[t] = Path[t];

                    t = i;
                    h = j;
                    while (true){
                        t = (t + 1) % n;
                        Path[t] = OldPath[h];
                        if (h == i + 1) break;
                        h = (h - 1 + n) % n;
                    }

                    h = (j + 1) % n;
                    while (true){
                        if (h == 0) break;
                        t = (t + 1) % n;
                        Path[t] = OldPath[h];
                        h = (h + 1) % n;
                    }

                    Current += c[x][u] + c[y][v] - c[x][y] - c[u][v];
                }
            }

        if (stop) break;
    }
}

void FindPath(int s){
    int i, u, v, Current;
    double MaxProb, Prob;

    memset(Visited, false, sizeof(Visited));
    Path[0] = s;
    Visited[Path[0]] = true;

    for (i = 1; i < n; i++){
        u = Path[i - 1];
        MaxProb = - 0.01;

        for (v = 0; v < n; v++)
            if (!Visited[v]){
                Prob = Probability(Pheromone[u][v], anfa, Visibility(u, v), beta);
                if (Prob > MaxProb){
                    MaxProb = Prob;
                    Path[i] = v;
                }
            }

        Visited[Path[i]] = true;
    }

    Current = 0;
    for (i = 0; i < n; i++){
        u = Path[i];
        v = Path[(i + 1) % n];
        Current += c[u][v];
    }

    Mutation(Path, Current);

    for (i = 0; i < n; i++){
        u = Path[i];
        v = Path[(i + 1) % n];
        Delta[u][v] += Q / Current;
    }

    if (Current < Best){
        Best = Current;
        for (i = 0; i < n; i++)
            BestPath[i] = Path[i];
    }
}

void AntColony(){
    int Time, i, j;

    Best = INF;

    for (Time = 1; Time <= Iteration; Time++){
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++) Delta[i][j] = 0.0;

        for (i = 0; i < nAnt; i++) FindPath(StartPoint[i]);

        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                Pheromone[i][j] = P * Pheromone[i][j] + Delta[i][j];
    }
}

void output(){
    int i;
    cout << Best << "\n";
    for (i = 0; i < n; i++) cout << BestPath[i] << " ";
}

// +--------------+
// | Main Program |
// +--------------+

int main(int argc, char *argv[]){
    freopen(input_file_name.c_str(), "r", stdin);
    freopen(output_file_name.c_str(), "w", stdout);
    input();
    init();
    AntColony();
    output();
}
