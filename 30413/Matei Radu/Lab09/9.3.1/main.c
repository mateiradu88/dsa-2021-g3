#include <stdio.h>
#include <stdlib.h>

#define INT_MIN -2147483648

int max(int a, int b)
{
    if(a>b)
        return a;
    return b;
}

int max_t(int a, int b, int c)
{
    return max(max(a, b), c);
}

int maxCrSum(int arr[], int l, int m, int r)
{
    int sum = 0;
    int l_sum = INT_MIN;
    int r_sum = INT_MIN;
    for (int i = m; i >= l; i--)
    {
        sum = sum + arr[i];
        if (sum > l_sum)
            l_sum = sum;
    }

    sum = 0;
    for (int i = m + 1; i <= r; i++)
    {
        sum = sum + arr[i];
        if (sum > r_sum)
            r_sum = sum;
    }
    return max_t(l_sum + r_sum, l_sum, r_sum);
}

int maxSum(int arr[], int l, int r)
{
    if (l == r)
        return arr[l];
    int m = (l + r) / 2;
    return max_t(maxSum(arr, l, m),
                 maxSum(arr, m + 1, r),
                 maxCrSum(arr, l, m, r));
}

int main()
{
    int n;
    int arr[100];
    scanf("%d", &n);
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    int max_sum = maxSum(arr, 0, n - 1);
    printf("Maximum sum is %d", max_sum);
    return 0;
}
