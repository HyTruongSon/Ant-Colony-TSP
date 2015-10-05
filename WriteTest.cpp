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

#define MaxN 1111

using namespace std;

const string file_name = "Graph.INP";

int main(int argc, char *argv[]){
    srand(time(0));
    freopen(file_name.c_str(), "w", stdout);
    int n, width, height;

    while (true){
        n = rand() % MaxN + 1;
        if (n >= 5) break;
    }

    width = atoi(argv[1]);
    height = atoi(argv[2]);
    n = atoi(argv[3]);
    cout << width << " " << height << " " << n << "\n";

    for (int i = 1; i <= n; i++)
        cout << rand() % width << " " << rand() % height << "\n";
}
