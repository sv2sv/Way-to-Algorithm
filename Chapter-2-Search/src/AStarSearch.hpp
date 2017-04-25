#ifndef EIGHT_FIGURE_PUZZLE_HPP
#define EIGHT_FIGURE_PUZZLE_HPP 1

/* 八数码问题 */

#include <algorithm>
#include <deque>
#include <vector>
#include <climits>
#include <cstring>
#include <unordered_map>
#include <unordered_set>
using namespace std;
#ifndef MAX
#define MAX 1024
#endif


/*
将矩阵
0 1 2
3 4 5
6 7 8
表示为char[9]数组
*/

int direction[4] = { -3, 3, -1, 1 };

int ScoreH(string a, string end)
{
    int diff = 0;
    for (int i = 0; i < 9; ++i)
        if (a[i] != b[i])
            ++diff;
    return diff;
}
string OpenPop(deque<string> & open, string end_node, unordered_map<string, int> & score_g)
{
    string res;
    int f = INT_MAX;
    deque<string>::iterator i;
    for (i = open.begin(); i != open.end(); i++) {
        int h = ScoreH(open[i], end_node);
        if (f > h + score_g[ *i ]) {
            f = h + score_g[ *i ];
            res = *i;
        }
    }
    open.erase(i);
    return res;
}
void OpenErase(deque<string> & open, string node)
{
    for (deque<string>::iterator i = open.begin(); i != open.end(); i++) {
        if (node == *i) {
            open.erase(i);
            break;
        }
    }
}

string Neighbor(string node, int dir)
{
    int xpos;
    for (xpos = 0; xpos < 9; xpos++)
        if (node[xpos] == 'x')
            break;

    int npos = xpos + dir;
    if (npos < 0 || npos >= 9)
        return "";

    swap(node[xpos], node[npox]);
    return node;
}

void FindPath(vector<string> & path, unordered_map<string, string> & close, string end_node)
{
    string node = end_node;
    string from = close.end();
    path.push_back(node);

    while (true) {
        from = close[node];
        if (from == close.end())
            break;
        path.push_back(from);
        node = from;
    }
}

vector<string> AStarSearch(string beg, string end)
{
    unordered_map<string, int> score_g;
    deque<string> open;
    unordered_set<string, string> close;
    vector<string> path;

    open.push_back(beg);
    close.insert(make_pair(beg, ""));

    while (!open.empty()) {
        string node = OpenPop(open, end, score_g);

        if (node == end) {
            FindPath(path, close, end);
            return path;
        }

        /* node中'x'与上下左右4个方向的数字交换位置 */
        for (int i = 0; i < 4; i++) {
            string neighbor_node = Neighbor(node, i);
            if (neighbor_node == "") {
                continue;
            }
            // 邻节点的g(x)加1
            score_g[ neighbor_node ] = score_g[node] + 1;

            // 若close中已经存在neighbor_node则跳过该点
            if (close.find(neighbor_node) != close.end())
                continue;
            open.push_back(neighbor_node);
            close.insert(make_pair(neighbor_node, node));
        }
    }

    return path;
}

#endif
