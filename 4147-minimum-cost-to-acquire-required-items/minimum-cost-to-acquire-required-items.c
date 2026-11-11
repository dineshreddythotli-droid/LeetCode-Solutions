
    long long minimumCost(int cost1, int cost2, int costBoth, int need1, int need2) {

    long long ans = 0;

    int mn = (need1 < need2) ? need1 : need2;

    int pairCost = (cost1 + cost2 < costBoth)
                   ? cost1 + cost2 : costBoth;

    ans = (long long)mn * pairCost;

    if (need1 > need2) {
        int extraCost = (cost1 < costBoth) ? cost1 : costBoth;
        ans += (long long)(need1 - need2) * extraCost;
    }
    else {
        int extraCost = (cost2 < costBoth) ? cost2 : costBoth;
        ans += (long long)(need2 - need1) * extraCost;
    }

    return ans;
}