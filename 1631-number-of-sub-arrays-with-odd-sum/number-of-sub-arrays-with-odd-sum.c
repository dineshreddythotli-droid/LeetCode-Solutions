
int numOfSubarrays(int* arr, int arrSize) {
    int mod = 1000000007;
    long long even = 1, odd = 0;
    long long sum = 0;
    long long ans = 0;

    for (int i = 0; i < arrSize; i++) {
        sum += arr[i];

        if (sum % 2 == 0) {
            ans = (ans + odd) % mod;
            even++;
        } 
        else {
            ans = (ans + even) % mod;
            odd++;
        }
    }

    return (int)ans;
}
