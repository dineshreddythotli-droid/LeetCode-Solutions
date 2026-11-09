/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
typedef struct {
    int time;
    int server;
} Pair;

void swap(Pair *a, Pair *b) {
    Pair t = *a;
    *a = *b;
    *b = t;
}

void push(Pair *heap, int *size, Pair x) {
    int i = (*size)++;
    heap[i] = x;

    while (i > 0) {
        int p = (i - 1) / 2;
        if (heap[p].time <= heap[i].time)
            break;

        swap(&heap[p], &heap[i]);
        i = p;
    }
}

Pair pop(Pair *heap, int *size) {
    Pair result = heap[0];
    heap[0] = heap[--(*size)];

    int i = 0;

    while (1) {
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        int s = i;

        if (l < *size && heap[l].time < heap[s].time)
            s = l;

        if (r < *size && heap[r].time < heap[s].time)
            s = r;

        if (s == i)
            break;

        swap(&heap[i], &heap[s]);
        i = s;
    }

    return result;
}

// Segment tree
int tree[400005];

void build(int node, int l, int r) {
    tree[node] = r - l + 1;

    if (l == r)
        return;

    int mid = (l + r) / 2;

    build(node * 2, l, mid);
    build(node * 2 + 1, mid + 1, r);
}

void update(int node, int l, int r, int pos, int val) {
    if (l == r) {
        tree[node] = val;
        return;
    }

    int mid = (l + r) / 2;

    if (pos <= mid)
        update(node * 2, l, mid, pos, val);
    else
        update(node * 2 + 1, mid + 1, r, pos, val);

    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

// Find first available server >= target
int findFirst(int node, int l, int r, int target) {
    if (r < target || tree[node] == 0)
        return -1;

    if (l == r)
        return l;

    int mid = (l + r) / 2;

    int res = findFirst(node * 2, l, mid, target);

    if (res != -1)
        return res;

    return findFirst(node * 2 + 1, mid + 1, r, target);
}

int* busiestServers(int k, int* arrival, int arrivalSize,
                    int* load, int loadSize, int* returnSize) {

    int *count = calloc(k, sizeof(int));
    int *ans = malloc(k * sizeof(int));

    Pair *heap = malloc((arrivalSize + 1) * sizeof(Pair));
    int heapSize = 0;

    build(1, 0, k - 1);

    for (int i = 0; i < arrivalSize; i++) {

        // Free completed servers
        while (heapSize > 0 && heap[0].time <= arrival[i]) {
            Pair p = pop(heap, &heapSize);
            update(1, 0, k - 1, p.server, 1);
        }

        int target = i % k;

        int server = findFirst(1, 0, k - 1, target);

        if (server == -1)
            server = findFirst(1, 0, k - 1, 0);

        if (server == -1)
            continue;

        count[server]++;

        update(1, 0, k - 1, server, 0);

        Pair p;
        p.time = arrival[i] + load[i];
        p.server = server;

        push(heap, &heapSize, p);
    }

    int maxCount = 0;

    for (int i = 0; i < k; i++) {
        if (count[i] > maxCount)
            maxCount = count[i];
    }

    *returnSize = 0;

    for (int i = 0; i < k; i++) {
        if (count[i] == maxCount)
            ans[(*returnSize)++] = i;
    }

    free(count);
    free(heap);

    return ans;
}