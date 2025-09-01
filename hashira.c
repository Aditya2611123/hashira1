#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long base_to_decimal(const char *s, int base) {
    long long n = 0;
    while (*s) {
        char c = *s++;
        int d = c >= '0' && c <= '9' ? c - '0' : c >= 'a' ? c - 'a' + 10 : c - 'A' + 10;
        n = n * base + d;
    }
    return n;
}

void solve_test_case(int test_case_num, int n, int k, char* roots[], int bases[]) {
    printf("\n=== TEST CASE %d ===\n", test_case_num);
    
    long long *decimals = malloc(n * sizeof(long long));
    for (int i = 0; i < n; i++) {
        decimals[i] = base_to_decimal(roots[i], bases[i]);
        printf("Root %d (base %d): %s -> %lld\n", i+1, bases[i], roots[i], decimals[i]);
    }
    
    long long *selected = malloc(k * sizeof(long long));
    for (int i = 0; i < k; i++) selected[i] = decimals[i];
    
    long long *dp = calloc(k+1, sizeof(long long));
    dp[0] = 1;
    for (int i = 0; i < k; i++) {
        for (int j = k; j >= 1; j--) {
            dp[j] += dp[j-1] * selected[i];
        }
    }
    
    printf("\nCoefficients:\n");
    for (int i = 0; i <= k; i++) {
        long long coeff = (i % 2) ? -dp[i] : dp[i];
        printf("x^%d: %lld\n", k-i, coeff);
    }
    
    free(decimals); free(selected); free(dp);
}

int main() {
    // TEST CASE 1
    int n1 = 4, k1 = 3;
    char* roots1[] = {"4", "111", "12", "213"};
    int bases1[] = {10, 2, 10, 4};
    solve_test_case(1, n1, k1, roots1, bases1);

    // TEST CASE 2
    int n2 = 10, k2 = 7;
    char* roots2[] = {
        "13444211440455345511", "aed7015a346d635", "6aeeb69631c227c",
        "e1b5e05623d881f", "316034514573652620673",
        "2122212201122002221120200210011020220200",
        "20120221122211000100210021102001201112121",
        "20220554335330240002224253", "45153788322a1255483",
        "1101613130313526312514143"
    };
    int bases2[] = {6, 15, 15, 16, 8, 3, 3, 6, 12, 7};
    solve_test_case(2, n2, k2, roots2, bases2);

    return 0;
}