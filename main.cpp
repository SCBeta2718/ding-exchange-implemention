#include "main.hpp"

#include <cstdio>
#include <cstdlib>

NTL_CLIENT

int main(int argc, char** argv)
{
    zz_p::init(120833);

    int n = atoi(argv[1]);
    float sigma = atof(argv[2]);

    Line l(n, sigma);
    U8 *cha = (U8*)malloc(n), *chb = (U8*)malloc(n);

    for(int T = 0; T < 100; T++)
    {
        Person Alice(&l), Bob(&l);
        Bob.GetAns();
        Alice.GetAns();

        Alice.Submit(cha);
        Bob.Submit(chb);

        for(int i = 0; i < n / 8; i++)
        {
            if(cha[i] != chb[i])
            {
                printf("%d %02x %02x\n", i, cha[i], chb[i]);
            }
        }
    }

    // for(int i = 0; i < n / 8; i++)
    // {
    //     printf("%02x ", cha[i]);
    // }
    // printf("\n");
    // for(int i = 0; i < n / 8; i++)
    // {
    //     printf("%02x ", chb[i]);
    // }
    // printf("\n");

    // for(int i = 0; i < n / 8; i++)
    // {
    //     if(cha[i] != chb[i])
    //     {
    //         printf("%d %02x %02x\n", i, cha[i], chb[i]);
    //     }
    // }
    return 0;
}