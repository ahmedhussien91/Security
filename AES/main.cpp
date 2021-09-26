#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include "AES.h"

using namespace std;

int main()
{
    /***************** Parse Test Data *********************************/
    //intial work for hardcoded array for testing purpose
    vector<unsigned char> cipher =  {0x3a,0xd7,0x7b,0xb4,0x0d,0x7a,0x36,0x60,0xa8,0x9e,0xca,0xf3,0x24,0x66,0xef,0x97};
    vector<unsigned char> plain=  {0x6b,0xc1,0xbe,0xe2,0x2e,0x40,0x9f,0x96,0xe9,0x3d,0x7e,0x11,0x73,0x93,0x17,0x2a,0x3a,0xd7,0x7b,0xb4,0x0d,0x7a,0x36,0x60,0xa8,0x9e,0xca,0xf3,0x24,0x66,0xef};

    //read from file
    string fileName = "main.cpp";
    string outName = "out.txt";

    //vector<unsigned char> key = {0x2b,0x7e,0x15,0x16,0x28,0xAE,0xD2,0xA6,0xAB,0xF7,0x15,0x88,0x09,0xCF,0x4F,0x3C};
    //vector<unsigned char> key = {0x8e, 0x73, 0xb0, 0xf7, 0xda, 0x0e, 0x64, 0x52, 0xc8, 0x10, 0xf3, 0x2b,
    //                            0x80, 0x90, 0x79, 0xe5, 0x62, 0xf8, 0xea, 0xd2, 0x52, 0x2c, 0x6b, 0x7b};
    vector<unsigned char> key = {0x60, 0x3d, 0xeb, 0x10, 0x15, 0xca, 0x71, 0xbe, 0x2b, 0x73, 0xae, 0xf0, 0x85, 0x7d, 0x77, 0x81,
                                 0x1f, 0x35, 0x2c, 0x07, 0x3b, 0x61, 0x08, 0xd7, 0x2d, 0x98, 0x10, 0xa3, 0x09, 0x14, 0xdf, 0xf4};
    //  ifstream stream(fileName, std::ios::in | std::ios::binary);
   // vector<unsigned char> plain((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());



    vector<unsigned char> encrypt;
    vector<unsigned char> decrypt;
    encrypt.resize(plain.size());
    decrypt.resize(plain.size());

    /************************* Encrypt Data *******************************/
    AES_Encrypt(key,plain,encrypt,AES128);
    /**************************Decrypt Data *******************************/
    AES_Decrypt(key,encrypt,decrypt,AES128);

    //Remove extra bits
    decrypt.resize(plain.size());
    /*************************** Compare ************************************/
    cout<<"Text\n";
    for(int i = 0 ;i<  plain.size();i++)
        cout<< std::hex<<(int)plain[i]<<" ";
    cout<<endl;
    cout<<"Key\n";
    for(int i = 0 ;i<  key.size();i++)
        cout<< std::hex<<(int)key[i]<<" ";
    cout<<endl;
    cout<<"Decrypted\n";
    for(int i = 0 ; i < decrypt.size();i++)
        cout<< std::hex<<(int)decrypt[i]<<" ";
    cout<<endl;

    /********************* Write to file ****************************/
   // ofstream fout(outName, ios::out | ios::binary);
   // fout.write((char*)&decrypt[0], decrypt.size());
   // fout.close();
    return  0;
}
