#include <stdio.h>
#include <string.h>

int get_sign(int num)
{
    return (num >> 7) & 1;
}
int get_exp(int num)
{
    return (num >> 3) & 1111;
}
int get_frac(int num)
{
    return num & 0111;
}

int main()
{
    char str1[10],str2[10];
    if(scanf("%8s %8s",str1,str2) != 2)
    {
        return 0;
    }
    
    int x = 0,y = 0;
    for (int i = 0;i < 8;i++)
    {
        x = (x << 1) | (str1[i] - '0');
        y = (y << 1) | (str2[i] - '0');
    }

    int exp_x = get_exp(x);
    int exp_y = get_exp(y);
    int frac_x = get_frac(x);
    int frac_y = get_frac(y);

    int m_x = (1 << 3) | frac_x;
    int m_y = (1 << 3) | frac_y;

    int final_exp = exp_x;
    int target_m_x = m_x;
    int target_m_y = m_y;

    if (exp_x < exp_y)
    {
        final_exp = exp_y;
        int shift = exp_y - exp_x;
        target_m_x = m_x >> shift;
    } else if (exp_y < exp_x) {
        final_exp = exp_x;
        int shift = exp_x - exp_y;
        target_m_y = m_y >> shift;
    }

    int sum_m = target_m_x + target_m_y;

    if ((sum_m >> 4) & 1)
    {
        int lost_bit = sum_m & 1;
        sum_m >>= 1;
        final_exp++;
    }

    int final_frac = sum_m & 0111;

    int result = (final_exp << 3) | final_frac;

    for (int i = 7;i >= 0;i--)
    {
        printf("%d",(result >> i) & 1);
    }
    printf("\n");
    return 0;
}