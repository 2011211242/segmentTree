

    #include <cstdio>
    using namespace std;

    #define MAX_LEN 100000

    struct node{
        unsigned int board;
        int left, right;
    };

    node tree[MAX_LEN << 2];

    void createTree(int i, int l, int r)
    {
        tree[i].left = l;
        tree[i].right = r;
        if(l < r)
        {
            int mid = (l + r) >> 1;
            int left = i << 1;

            createTree(left, l, mid);
            createTree(left + 1, mid + 1, r);
        }
    }

    void initTree()
    {
        tree[1].board = 0x01;
    }

    int bitCount(unsigned int board)
    {
        int c = 0;
        while(board)
        {
            board &= (board - 1);
            c++;
        }
        return c;
    }

    void update(int i, int l, int r, int c)
    {
        if(tree[i].board == (0x01 << (c - 1)))
            return;

        if(tree[i].left == l && tree[i].right == r)
        {
             tree[i].board = (0x01 << (c - 1));
             return;
        }

        int mid = (tree[i].left + tree[i].right) >> 1;
        int left = i << 1;
        int right = left + 1;
        if((tree[i].board & (tree[i].board - 1)) == 0)
        {
            tree[left].board = tree[right].board = tree[i].board;
        }

        if(r <= mid)
        {
            update(left, l, r, c);
        }
        else
        {
            if(l > mid)
            {
                update(right, l, r, c);
            }
            else
            {
                update(left, l, mid, c);
                update(right, mid + 1, r, c);
            }
        }
        tree[i].board = tree[left].board | tree[right].board;
    }

    unsigned int find(int i, int l, int r)
    {
        if((tree[i].left == l && tree[i].right == r) || (tree[i].board & (tree[i].board - 1) == 0))
        {
            return tree[i].board;
        }
        int mid = (tree[i].left + tree[i].right) >> 1;
        int left = i << 1;
        int right = left + 1;
        unsigned int board = 0;
        if(r <= mid)
        {
            board = find(left, l, r);
        }
        else {
            if(l > mid)
            {
                board = find(right, l, r);
            }
            else{
                board = find(left, l, mid);
                board |= find(right, mid + 1, r);
            }
        }
        return board;
    }

    int main()
    {
        int L, T, O;
        while(scanf("%d %d %d", &L, &T, &O) != EOF)
        {
            createTree(1, 1, L);
            initTree();
            char op[5];
            int l, r, c;
            for(int i = 0; i < O; i++)
            {
                scanf("%s", op);
                if(op[0] == 'C')
                {
                    scanf("%d %d %d", &l, &r, &c);
                    if(l > r)
                    {
                        update(1, r, l, c);
                    }
                    else
                    {
                        update(1, l, r, c);
                    }
                }
                if(op[0] == 'P')
                {
                    scanf("%d %d", &l, &r);
                    if(l > r)
                    {
                        printf("%d\n", bitCount(find(1, r, l)));
                    }
                    else
                    {
                        printf("%d\n", bitCount(find(1, l, r)));
                    }
                 }
             }
         }
    }


