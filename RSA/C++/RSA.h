#ifndef RSA_H
#define RSA_H
#include <string>
#include <vector>
#include "BigInt.h"

typedef   long long  ll;

ll generateKeys(ll&,ll&) ;
ll expMod(ll , ll ,ll );
void encrypt(std::string ,std::vector<ll>& ,ll,ll);
void decrypt(std::vector<ll>,std::string&,ll,ll);

#endif // RSA_H
