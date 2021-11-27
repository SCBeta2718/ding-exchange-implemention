#pragma once

#include "Ding.h"

#include <random>
#include <NTL/lzz_pX.h>
#include <NTL/ZZX.h>

NTL_CLIENT

mt19937 rng;

struct Line
{
    int n;
    double sigma;
    ZZX a;
    ZZX f;

    ZZX pp;
    char* w;
    bool syned;

    Line(int _n = 512, double _sigma = 4.19): n(_n), sigma(_sigma), syned(false)
    {
        zz_pX _a(Derive_a(_n));
        for(int i = 0; i < _n; i++)
        {
            SetCoeff(a, i, rep(coeff(_a, i)) - (q - 1) / 2);
        }

        SetCoeff(f, _n, 1);
        SetCoeff(f, 0, 1);
        w = (char*)malloc(_n);
    }
};

struct Person
{
// private:
    ZZX pp;
    ZZX ps;
    U8* w;
    U8* sk;
    Line* line;
    ZZX k;

    void Syn(void)
    {
        line->pp = Round(pp, line->n);
        line->syned = true;
    }
    void Ack(void)
    {
        line->pp = Round(pp, line->n);
        memcpy(line->w, w, line->n);
        line->syned = false;
    }

// public:

    Person(Line* _line = nullptr): line(_line)
    {
        int n = _line->n;
        w = (U8*)malloc(n / 8);
        sk = (U8*)malloc(n / 8);

        ps = SampleD(n, _line->sigma, rng);
        ZZX e = SampleD(n, _line->sigma, rng);
        pp = (MulMod(_line->a, ps, _line->f) + e + e) % line->f;
        Modq(pp, n);

        if(!_line->syned) Syn();
    }
    ~Person()
    {
        free(w);
        free(sk);
    }

    void GetAns(void)
    {
        int n = line->n;
        ZZX __pp = Recover(line->pp, n);
        k = MulMod(__pp, ps, line->f);
        Modq(k,n);

        if(!line->syned) 
        {
            memcpy(w, line->w, n / 8);
        }
        else
        {
            for(int i = 0; i < n / 8; i++)
            {
                for(int j = 0; j < 8; j++)
                {
                    w[i] <<= 1;
                    w[i] += Sig(coeff(k, i * 8 + j));
                }
            }
            Ack();
        }

        for(int i = 0; i < n / 8; i++)
        {
            for(int j = 0; j < 8; j++)
            {
                sk[i] <<= 1;
                sk[i] += Mod2(coeff(k, i * 8 + j), (w[i] >> (7 - j)) % 2);
            }
        }
    }

    void Submit(U8* ch)
    {
        memcpy(ch, sk, line->n);
    }
};