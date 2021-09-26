#include <stdlib.h>
#include <time.h>
#include <bits/stdc++.h>
#include <algorithm>
#include "RSA.h"
// ~10-6 error for jacobi function
#define RSA_K   (10)
//#define DEBUG

using namespace  std;
ll expMod(ll base, ll exp,ll mod)
{
    if( exp == (0))
        return (1);
    ll sq = expMod(base, exp/2,mod)%mod;
    sq = (sq*sq)%mod;
    if (exp%2 == 1)
        sq = (sq*base)%mod;
    return sq%mod;
}

ll jacobi(ll r, ll p)
{
    if(r == 0) return 0;
    if(r == 1) return 1;
    if(r%2 == 0) return jacobi(r/2,p)*pow(-1.0,(p*p-1)/8);
    else return jacobi(p%r,r)*pow(-1.0,((r-1)*(p-1))/4);
}

bool isProbablePrime(ll p)
{
    for (int i = 0; i < RSA_K; i++)
    {
        // Generate a random number a
        ll r = rand() % (p - 1) + 1;
        if(__gcd(r,p) != 1) return false;
        volatile ll jacobian = (p + jacobi(r, p)) % p;
        ll mod = expMod(r, (p - 1) / 2, p);
#ifdef DEBUG
        std::cout<<__FUNCTION__<<" r "<<r<<" mod "<<mod<<" jacobian "<<jacobian<<endl;
#endif /*DEBUG*/
        if (mod != jacobian)
            return false;
    }
    return true;
}
ll isPrime(ll x)
{
    for(ll i = 2 ; i*i < x; i++)
    {
        if(x%i == 0)return false;
    }
    return true;
}
ll  generatePrime(ll l , ll r)
{
    ll cp = 1;
    do
    {
       cp =  rand() % r + l;
       if(cp%2 == 0) cp++;
#ifdef DEBUG
       std::cout<<__FUNCTION__<<" Generated "<<cp<<endl;
#endif /*DEBUG*/
    }while(!isProbablePrime(cp));
    return cp;
}
ll generateKeys(ll &e, ll &d)
{
    ll p =  generatePrime(2,10e18);
    ll q =  generatePrime(2,10e18);
    ll n = p*q ;
    ll t = (p-1)*(q-1) ;
    ll k=1;
    e = 2;
    while(__gcd(e,t) != 1) e++;
    //e*d = 1 mod (t)

    while (true)
    {
        k = k + t;
        if ( k % e == 0)
        {
            d = (k / e);
            break;
        }
    }
#ifdef DEBUG
#endif /*DEBUG*/
    return n ;
}

void encrypt(std::string in,vector<ll>& out,ll e,ll n)
{
    out.resize(in.size());
    for(int i = 0 ; i < in.size() ; i++)
    {
        ll x= expMod(in[i],e,n);
        out[i]  = x;
    }
}
void decrypt(vector<ll> in ,std::string& out ,ll d, ll n)
{
    out.resize(in.size());

    for(int i = 0 ; i < in.size() ; i++)
    {
        ll x= expMod(in[i],d,n);
        out[i]  = x;
    }
    cout<<endl;
}
