#include <cstdio>
using namespace std;

#define MAX_N  200001

struct node{
    int left;
    int right;
    int max;
};

int num[MAX_N];
node tree[MAX_N<<2];

void createTree(int i, int l, int r)
{
    if(l == r)
    {
        tree[i].max = num[l];
        tree[i].left = tree[i].right = l;
        return;
    }

    tree[i].left = l;
    tree[i].right = r;
    int mid = (l + r) >> 1;
    int left = i << 1;
    int right = left + 1;

    createTree(left, l, mid);
    createTree(right, mid + 1, r);
    tree[i].max = tree[left].max > tree[right].max ? tree[left].max : tree[right].max;
}

void update(int i, int val)
{
    int nd = 1;
    while(tree[nd].left != tree[nd].right)
    {
        int mid = (tree[nd].left + tree[nd].right) >> 1;
        if(i <= mid)
        {
            nd = nd << 1;
        }
        else
        {
           nd = (nd << 1) + 1;
        }
    }
    tree[nd].max = val;

    nd >>= 1;
    while(nd > 0)
    {
        int left = nd << 1;
        int right = left + 1;
        if(tree[left].max > tree[right].max)
        {
            tree[nd].max = tree[left].max;
        }
        else
        {
            tree[nd].max = tree[right].max;
        }
        nd >>= 1;
    }
}

int find(int s, int to, int i)
{
    if(tree[i].left == s && tree[i].right == to)
        return tree[i].max;
    int mid = (tree[i].left + tree[i].right) >> 1;
    if(to <= mid)
    {
        return find(s, to, i << 1);
    }
    if(s > mid)
    {
        return find(s, to, (i << 1) + 1);
    }

    int lm = find(s, mid, i << 1);
    int rm = find(mid + 1, to, (i << 1) + 1);
    if (lm > rm) return lm;
    else    return rm;
}

int main()
{
    int N, M;

    while(scanf("%d %d", &N, &M) != EOF)
    {
        for(int i = 1; i <= N; i++)
        {
            scanf("%d", &num[i]);
        }

        createTree(1, 1, N);
        char op[10];
        int s, e;
        for(int i = 0; i < M; i++)
        {
            scanf("%s %d %d", op, &s, &e);
            if(op[0] == 'Q')
            {
                int res = find(s, e, 1);
                printf("%d\n", res);
            }
            if(op[0] == 'U')
            {
                update(s, e);
            }
        }
    }
}
