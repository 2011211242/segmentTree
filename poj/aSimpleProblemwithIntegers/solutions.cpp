#include <cstdio>
using namespace std;

#define MAX_LEN 100000
int num[MAX_LEN + 1];

struct node{
    long long int val;
    long long int add;
    int left, right;
};

node tree[MAX_LEN << 2];

void createTree(int i, int l, int r)
{
    tree[i].left = l;
    tree[i].right = r;
    tree[i].add = 0;
    if(l == r)
    {
        tree[i].val = num[l];
        return;
    }
    int left = i << 1;
    int right = left + 1;
    int mid = (l + r) >> 1;
    createTree(left, l, mid);
    createTree(right, mid + 1, r);
    tree[i].val = tree[left].val + tree[right].val;
}

void update(int i, int l, int r, int val)
{
    if(tree[i].left == l && tree[i].right == r)
    {
        tree[i].add += val;
        return;
    }
    int left = i << 1;
    int right = left + 1;
    int mid = (tree[i].left + tree[i].right) >> 1;
    if(mid >= r)
    {
        update(left, l, r, val);
    }
    else{
        if(mid < l)
        {
            update(right, l, r, val);
        }
        else
        {
            update(left, l, mid, val);
            update(right, mid + 1, r, val);
        }
    }
    tree[i].val = tree[left].val + tree[left].add * (tree[left].right - tree[left].left + 1) +
        tree[right].val + tree[right].add * (tree[right].right - tree[right].left + 1);
}



long long int find(int i, int l, int r)
{
    long long int res = tree[i].add * (r - l + 1);
    if(tree[i].left == l && tree[i].right == r)
    {
        res += tree[i].val;
    }
    else
    {
        int left = i << 1;
        int right = left + 1;
        int mid = (tree[i].left + tree[i].right) >> 1;

        if(mid >= r)
        {
            res += find(left, l, r);
        }
        else{
            if(mid < l)
            {
                res += find(right, l, r);
            }
            else
            {
                res += find(left, l, mid) + find(right, mid + 1, r);
            }
        }
    }
    return res;
}

int main()
{
    int N, Q;
    while(scanf("%d %d", &N, &Q) != EOF)
    {
        for(int i = 1; i <= N; i++)
        {
            scanf("%d", &num[i]);
        }

        createTree(1, 1, N);
        char op[4];
        int l, r, val;
        for(int i = 1; i <= Q; i++)
        {
            scanf("%s", op);
            if(op[0] == 'Q')
            {
                scanf("%d %d", &l, &r);
                printf("%lld\n", find(1, l, r));
            }
            if(op[0] == 'C')
            {
                scanf("%d %d %d", &l, &r, &val);
                update(1, l, r, val);
            }

        }
    }
}
