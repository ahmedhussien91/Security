#include <iostream>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include "RSA.h"

using namespace std;
ll pub,priv;
int main()
{
    string test_vector = "Hello all this is RSA Code for NU Course";
    string dec;
    vector<ll> enc;
    enc.resize(test_vector.size());
    dec.resize(test_vector.size());

    srand (time(NULL));
    ll n = generateKeys(pub,priv);
    cout<<"Keys are pub "<<pub<<" priv "<<priv<<" n "<<n<<endl;
    encrypt(test_vector,enc,pub,n);
    cout<<"Encrypted Message "<<(int)enc[0]<<endl;
    decrypt(enc,dec,priv,n);
    cout<<"Decrypted Message "<<dec<<endl;
    return 0;
}
