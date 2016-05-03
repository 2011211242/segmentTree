#include <cstdio>
#include <climits>
using namespace std;
#define MAX_L 5000

struct node{
    int left,right,sum;
};

int num[MAX_L + 1];
node tree[MAX_L << 2];

void buildTree(int i, int l, int r)
{
    tree[i].left = l;
    tree[i].right = r;
    tree[i].sum = 0;
    if(l < r)
    {
        int mid = (l + r) >> 1;
        int left = i << 1;
        int right = left + 1;
        buildTree(left, l, mid);
        buildTree(right, mid + 1, r);
    }
}

void update(int i, int data)
{
    tree[i].sum += 1;
    int mid = (tree[i].left + tree[i].right) >> 1;
    int left = i << 1;
    int right = left + 1;

    if(tree[i].left == tree[i].right)
        return;

    if(data <= mid)
        update(left, data);
    else
        update(right, data);
}

int find(int i, int data)
{
    if(data == tree[i].left) return tree[i].sum;

    int mid = (tree[i].left + tree[i].right) >> 1;
    int left = i << 1;
    int right = left + 1;

    if(data <= mid)
    {
        return tree[right].sum + find(left, data);
    }
    else
    {
        return find(right, data);
    }
}

int main(){
    int n;
    int tmp;
    while(scanf("%d", &n) != EOF)
    {
        buildTree(1, 1, n);
        tmp = 0;

        for(int i = 1; i <= n; i++)
        {
            scanf("%d", &num[i]);
            num[i]+= 1;
            tmp += find(1, num[i]);
            update(1, num[i]);
        }
        int min = tmp;
        for(int i = 1; i < n; i++)
        {
            tmp += n + 1 - (num[i] << 1);
            min = tmp < min ? tmp : min;
        }
        printf("%d\n", min);
    }
}
