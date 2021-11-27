#include <NTL/ZZ.h>
#include <NTL/vector.h>
#include <NTL/GF2.h>

#include <climits>

#include "Ding.h"

NTL_CLIENT

ZZ Round(ZZ x) 
{
    x = RModq(x);
    ZZ _x = x * p / q;

    if(IsOdd(x + _x))
    {
        _x++;
    }

    _x = Remove_bias(_x);
    
    return _x;
}
ZZX Round(ZZX _x, int n)
{
    ZZX ans;
    for(int i = 0; i < n; i++)
    {
        SetCoeff(ans, i, Round(coeff(_x, i)));
        // cout<<coeff(_x, i)<<" "<<Recover(Round(coeff(_x, i)))<<" "<<Recover(Round(coeff(_x, i))) - coeff(_x, i)<<endl;
    }

    return ans;
}

ZZ Recover(ZZ _x) 
{
    ZZ __x = _x * q / p;

    if(IsOdd(__x + _x))
    {
        __x++;
    }

    return RModq(__x);
}
ZZX Recover(ZZX _x, int n)
{
    ZZX ans;
    for(int i = 0; i < n; i++)
    {
        SetCoeff(ans, i, Recover(coeff(_x, i)));
    }

    return ans;
}

ZZ Remove_bias(ZZ _x)
{
    for(int i = 0; i < 17; i++)
    {
        if(_x == pos[i])
        {
            _x += rep(random_GF2()) * 2;
            break;
        }
    }

    return _x;
}

ZZX SampleD(I32 n, double sigma, mt19937& gen)
{
    normal_distribution<> d(0, sigma);

    ZZX ans;
    for(int i = 0; i < n; i++)
    {
        int t = int(d(gen));
        while(t > ((q - 1) >> 1) || t < -((q - 1) >> 1))
        {
            t = int(d(gen));
        }
        SetCoeff(ans, i, t);
    }

    Modq(ans, n);

    return ans;
}

ZZ Modq(ZZ a)
{
    return a <= (q - 1) / 2 ? a : a - q;
}
ZZ RModq(ZZ a)
{
    return a >= 0 ? a : a + q;
}
void Modq(ZZX& a, int n)
{
    for(int i = 0; i < n; i++)
    {
        SetCoeff(a, i, Modq(coeff(a, i) % q));
    }
}

I32 Mod2(ZZ x, I32 w)
{
    // cout<<typeid((x + 2 * q + w * ((q - 1) >> 1)) % ZZ(q)).name()<<endl;
    return IsOdd((x + w * (q - 1) / 2) % q);
}

I32 Sig(ZZ x)
{
    return (x >= -(q / 4) && x <= q / 4) ? 1 : 0;
}
