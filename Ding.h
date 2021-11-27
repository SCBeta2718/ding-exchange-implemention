#pragma once

#include <NTL/tools.h>
#include <NTL/ZZX.h>

#include <random>

#define Derive_a(n) (random_zz_pX(n))

NTL_CLIENT

typedef unsigned char U8;
typedef int I32;
typedef unsigned int U32;
typedef long long I64;
typedef unsigned long long U64;

const ZZ p(7551), q(120833);
const int pos[17] = {0, 445, 888, 1333, 1776, 2221, 2666, 3109, 3554, 3997, 4442, 4885, 5330, 5775, 6218, 6663, 7106};

ZZ Round(ZZ x);
ZZX Round(ZZX _x, int n);

ZZ Recover(ZZ _x);
ZZX Recover(ZZX _x, int n);

ZZ Remove_bias(ZZ _x);

ZZX SampleD(I32 n, double sigma, mt19937& gen);

ZZ Modq(ZZ a);
ZZ RModq(ZZ a);
void Modq(ZZX& a, int n);

I32 Mod2(ZZ x, I32 w);
I32 Sig(ZZ x);