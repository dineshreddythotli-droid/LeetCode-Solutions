char* digitSum(char* s, int k) {
    int len = strlen(s);

    while (len > k) {
        char temp[1001];
        int index = 0;

        for (int i = 0; i < len; i += k) {
            int sum = 0;

            for (int j = i; j < i + k && j < len; j++) {
                sum += s[j] - '0';
            }

            char buffer[10];
            int count = 0;

            do {
                buffer[count++] = (sum % 10) + '0';
                sum /= 10;
            } while (sum > 0);

            while (count > 0) {
                temp[index++] = buffer[--count];
            }
        }

        temp[index] = '\0';

        strcpy(s, temp);
        len = strlen(s);
    }

    return s;
}