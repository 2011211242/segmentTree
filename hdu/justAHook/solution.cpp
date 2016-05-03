#include <cstdio>
#include <algorithm>
using namespace std;

#define MAX_N 100000

struct node{
    int left;
    int right;
    int data;
    int sum;
};

node hook[MAX_N << 2];

void createTree(int i, int l, int r)
{
    hook[i].left = l;
    hook[i].right = r;
    hook[i].sum = r - l + 1;
    hook[i].data = 1;
    int mid = (l + r) >> 1;
    int left = i << 1;

    if(l < r)
    {
        createTree(left, l, mid);
        createTree(left + 1, mid + 1, r);
    }
}

void update(int i, int l, int r, int c)
{
    if(hook[i].left == l && hook[i].right == r)
    {
        hook[i].data = c;
        hook[i].sum = (r - l + 1) * c;
    }
    else
    {
        int left = i << 1;
        int right = left + 1;
        if(hook[i].data > 0)
        {
            hook[left].sum = hook[i].data * (hook[left].right - hook[left].left + 1);
            hook[right].sum = hook[i].data * (hook[right].right - hook[right].left + 1);
            hook[left].data = hook[i].data;
            hook[right].data = hook[i].data;
            hook[i].data = 0;
        }

        int mid = (hook[i].left + hook[i].right) >> 1;
        if(l <= mid)
        {
            int r1 = mid;
            if(r1 > r) r1 = r;
            update(left, l, r1, c);
        }

        if(r > mid)
        {
            int l2 = mid + 1;
            if (l2 < l) l2 = l;
            update(right, l2, r, c);
        }
        hook[i].sum = hook[left].sum + hook[right].sum;
    }
}

int main(){
    int T;
    scanf("%d", &T);
    for(int i = 1; i <= T; i++)
    {
        int N;
        scanf("%d", &N);
        int Q;
        scanf("%d", &Q);

        createTree(1, 1, N);
        for(int j = 0; j < Q; j++)
        {
            int s, e, k;
            scanf("%d %d %d", &s, &e, &k);
            update(1, s, e, k);
        }
        printf("Case %d: The total value of the hook is %d.\n", i, hook[1].sum);
    }
    return 0;
}
