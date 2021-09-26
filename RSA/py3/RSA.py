# -*- coding: utf-8 -*-
"""
Created on Thu Nov 28 11:28:44 2019

@author: msaleh1
"""
import sys
import math
import random
from timeit import default_timer as timer
from datetime import timedelta

KeyGen = 1
RSA_K = 5
keySize = 50
LEN = pow(2,keySize)


def expMod(base , exp , mod):
    if(exp == 0):
        return 1
    sq = expMod(base,exp // 2,mod)%mod
    sq = (sq*sq)%mod
    if(exp%2 == 1):
        sq = (sq*base)%mod
    return sq

def jacobi( r,  p):
    if(r == 0): return 0;
    if(r == 1): return 1;
    if(r%2 == 0):
        return jacobi(int(r/2),p)*pow(-1.0,int((p*p-1)/8))
    else:
        return jacobi(p%r,r)*pow(-1.0,int(((r-1)*(p-1))/4))

def isProbablePrime(p):
    for i in range(RSA_K):            
        r =random.randint(1,p-1)
        r = int(r)
        if(int(math.gcd(r,p)) != 1):  return False
        jacobian = (p + jacobi(r, p)) % p
        mod = expMod(r, int((p - 1) / 2), p)
        if (mod != jacobian):
            return False
    return True
def isPrime(p):
    i = 2
    while((i*i)<p):
        if(p%i == 0):
            return False
        i+=1
    return True        
def  generatePrime( l ,  r):
    cp = 1
    while(True):
       cp = random.randrange(l,r) 
       if(cp%2 == 0):
           cp+=1
       if(isProbablePrime(cp)):
           break
    return cp

def findModInverse(a, m):
    if math.gcd(a, m) != 1:
        return None
    u1, u2, u3 = 1, 0, a
    v1, v2, v3 = 0, 1, m
    
    while v3 != 0:
        q = u3 // v3
        v1, v2, v3, u1, u2, u3 = (u1 - q * v1), (u2 - q * v2), (u3 - q * v3), v1, v2, v3
    return u1 % m
def generateKeys():
    p =  generatePrime(2,LEN);
    print("p = " + str(p))
    q =  generatePrime(2,LEN);
    print("q = " + str(q))

    n = p*q ;
    t = (p-1)*(q-1) ;
    k=1;
    while True:
        e = random.randrange(2 ** (keySize - 1), 2 ** (keySize))
        if math.gcd(e, t) == 1:
            break
    d = findModInverse(e,t)
    return n,e,d,t

'''
    while (True):
        k = k + t;
        if (k % e == 0):
            d = int(k / e)
    break
'''
    
def encryptNum(pin, e, n):
    pout = pow(pin,e,n)
    return pout 

def encrypt(pin, e, n): 
    lin = list(pin)
    pout = lin
    for i in range(len(pin)):
        pout[i] = expMod(ord(lin[i]),e,n)
    return pout

def decryptNum(pin, d, n):
    pout = pow(pin,d,n)
    return pout 

def decrypt(pin, d, n):
    pout = ""
    for char in pin:
    	pout += (chr(expMod(char,d,n)))
    return pout

start = timer()


print ("Welcome to RSA")
if(KeyGen):
    n,e,d,t = generateKeys()
    print("n " + str(n))
    print("e " + str(e))
    print("d " + str(d))
    print("t " + str(t))
    test = (e*d)%t
    print("RSA Test " + str(test) )
else: 
    n = 0xc5062b58d8539c765e1e5dbaf14cf75dd56c2e13105fecfd1a930bbb5948ff328f126abe779359ca59bca752c308d281573bc6178b6c0fef7dc445e4f826430437b9f9d790581de5749c2cb9cb26d42b2fee15b6b26f09c99670336423b86bc5bec71113157be2d944d7ff3eebffb28413143ea36755db0ae62ff5b724eecb3d316b6bac67e89cacd8171937e2ab19bd353a89acea8c36f81c89a620d5fd2effea896601c7f9daca7f033f635a3a943331d1b1b4f5288790b53af352f1121ca1bef205f40dc012c412b40bdd27585b946466d75f7ee0a7f9d549b4bece6f43ac3ee65fe7fd37123359d9f1a850ad450aaf5c94eb11dea3fc0fc6e9856b1805ef
    e = 0x0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000086c94f
    d = 0x49e5786bb4d332f94586327bde088875379b75d128488f08e574ab4715302a87eea52d4c4a23d8b97af7944804337c5f55e16ba9ffafc0c9fd9b88eca443f39b7967170ddb8ce7ddb93c6087c8066c4a95538a441b9dc80dc9f7810054fd1e5c9d0250c978bb2d748abe1e9465d71a8165d3126dce5db2adacc003e9062ba37a54b63e5f49a4eafebd7e4bf5b0a796c2b3a950fa09c798d3fa3e86c4b62c33ba9365eda054e5fe74a41f21b595026acf1093c90a8c71722f91af1ed29a41a2449a320fc7ba3120e3e8c3e4240c04925cc698ecd66c7c906bdf240adad972b4dff4869d400b5d13e33eeba38e075e872b0ed3e91cc9c283867a4ffc3901d2069f
    print("n " + str(n))
    print("e " + str(e))
    print("d " + str(d))

#text = int(math.sqrt(e))
text = "Hello all, this is NU security Class"
print("text " + str(text))
enc = encrypt(text,d,n)  
print("enc " + str(enc))
dec = decrypt(enc,e,n)  
print("dec "+ str(dec))
end = timer()
print(timedelta(seconds=end-start))

