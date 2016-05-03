#include <cstdio>
using namespace std;
#define MAX 10000000

struct node {
    int left, right;
    int color;
};

node tree[MAX * 2];
bool same[10001];
int res;

void buildTree(int i, int l, int r)
{
    tree[i].left = l;
    tree[i].right = r;
    if(l < r)
    {
        int mid = (l + r) >> 1;
        int left = i << 1;
        int right = left + 1;
        buildTree(left, l, mid);
        buildTree(right, mid + 1, r);
    }
}

void update(int i, int l, int r, int color)
{
    if(tree[i].left == l && tree[i].right == r)
    {
        tree[i].color = color;
    }
    else
    {
        int mid = (tree[i].left + tree[i].right) >> 1;
        int left = i << 1;
        int right = left + 1;

        if(tree[i].color != 0)
        {
            tree[left].color = tree[i].color;
            tree[right].color = tree[i].color;
            tree[i].color = 0;
        }

        if(mid >= r)
        {
            update(left, l, r, color);
        }
        else
        {
            if(mid < l)
                update(right, l, r, color);
            else
            {
                update(left, l, mid, color);
                update(right, mid + 1, r, color);
            }
        }
    }
}

void find(int i, int l, int r)
{
    if(tree[i].color == -1) return;
    if(tree[i].color != 0)
    {
        if(same[tree[i].color] == false)
        {
            res += 1;
            same[tree[i].color] = true;
        }
    }
    else
    {
        int mid = (tree[i].left + tree[i].right) >> 1;
        int left = i << 1;
        int right = left + 1;
        if(mid >= r)
        {
            find(left, l, r);
        }
        else
        {
            if(mid < l)
            {
                find(right, l, r);
            }
            else
            {
                find(left, l, mid);
                find(right, mid + 1, r);
            }
        }
    }
}

int main(){
    int T;
    int n;

    scanf("%d", &T);
    for(int k = 0; k < T; k++)
    {
        scanf("%d", &n);
        buildTree(1, 1, MAX);
        tree[1].color = -1;
        for(int i = 1; i <= n; i++)
        {
            int l, r;
            scanf("%d %d", &l, &r);
            update(1, l, r, i);
            same[i] == false;
        }
        res = 0;
        find(1, 1, MAX);
        printf("%d\n", res);
    }
}
