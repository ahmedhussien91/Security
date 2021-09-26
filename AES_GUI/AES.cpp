#include <iostream>
#include <iomanip>
#include <vector>
#include "AES.h"

using namespace std;
#define _DEBUG
#define PAD_RFC5652
//key exapnsion constants
static unsigned char RCON [256] = {
    0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a,
    0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39,
    0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a,
    0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8,
    0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef,
    0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc,
    0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b,
    0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3,
    0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94,
    0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20,
    0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35,
    0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f,
    0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04,
    0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63,
    0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd,
    0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d
};
//sub byte transformation
unsigned char subBye_transform[256] = {
    0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
    0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
    0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
    0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
    0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
    0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
    0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
    0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
    0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
    0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
    0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
    0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
    0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
    0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
    0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
    0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
};
unsigned char invSubBye_transform[256] = {
    0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38,
    0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
    0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87,
    0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
    0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d,
    0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
    0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2,
    0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
    0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16,
    0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
    0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda,
    0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
    0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a,
    0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
    0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02,
    0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
    0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea,
    0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
    0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85,
    0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
    0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89,
    0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
    0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20,
    0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
    0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31,
    0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
    0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d,
    0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
    0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0,
    0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
    0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26,
    0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d,
    };

static unsigned char xtime(unsigned char x)    // multiply on x
{
    unsigned char mask = 0x80, m = 0x1b;
    unsigned char high_bit = x & mask;
    x = x << 1;
    if (high_bit) {
        x = x ^ m;
    }
    return x;
}


static unsigned char mulBin(unsigned char x , unsigned char y)
{
    unsigned char c = 0, mask = 1, bit, d;
    int i, j;
    for (i = 0; i < 8; i++)
    {
        bit = y & mask;
        if (bit)
        {
            d = x;
            for (j = 0; j < i; j++)
            {    // multiply on x^i
                d = xtime(d);
            }
            c = c ^ d;    // xor to result
        }
        y = y >> 1;
    }
    return c;
}

static void  mixColumns(unsigned char* buf)
{
    // make it larger to avoid over flow of multiplication
    unsigned char temp_state[16];
    //matrix multiplication with
    // 02 03 01 01
    // 01 02 03 01
    // 01 01 02 03
    // 03 01 01 02
    temp_state[0] = mulBin(buf[0],2) ^ mulBin(buf[1],3) ^ buf[2] ^ buf[3];
    temp_state[1] = buf[0] ^ mulBin(buf[1],2) ^ mulBin(buf[2],3) ^ buf[3];
    temp_state[2] = buf[0] ^ buf[1] ^ mulBin(buf[2],2) ^ mulBin(buf[3],3);
    temp_state[3] = mulBin(buf[0],3) ^ buf[1] ^ buf[2] ^ mulBin(buf[3],2);
    temp_state[4] = mulBin(buf[4],2) ^ mulBin(buf[5],3) ^ buf[6] ^ buf[7];
    temp_state[5] = buf[4] ^ mulBin(buf[5],2) ^ mulBin(buf[6],3) ^ buf[7];
    temp_state[6] = buf[4] ^ buf[5] ^ mulBin(buf[6],2) ^ mulBin(buf[7],3);
    temp_state[7] = mulBin(buf[4],3) ^ buf[5] ^ buf[6] ^ mulBin(buf[7],2);
    temp_state[8] = mulBin(buf[8],2) ^ mulBin(buf[9],3) ^ buf[10] ^ buf[11];
    temp_state[9] = buf[8] ^ mulBin(buf[9],2) ^ mulBin(buf[10],3) ^ buf[11];
    temp_state[10] =buf[8] ^ buf[9] ^ mulBin(buf[10],2) ^ mulBin(buf[11],3);
    temp_state[11] = mulBin(buf[8],3) ^ buf[9] ^ buf[10] ^ mulBin(buf[11],2);
    temp_state[12] = mulBin(buf[12],2) ^ mulBin(buf[13],3)^ buf[14] ^ buf[15];
    temp_state[13] =buf[12] ^ mulBin(buf[13],2) ^ mulBin(buf[14],3) ^ buf[15];
    temp_state[14] =buf[12] ^ buf[13] ^ mulBin(buf[14],2) ^ mulBin(buf[15],3);
    temp_state[15] = mulBin(buf[12],3) ^ buf[13] ^ buf[14] ^ mulBin(buf[15],2);

    for (int i = 0; i < 16; i++) {
        buf[i] = temp_state[i];
    }
#ifdef _DEBUG
    cout<<__FUNCTION__<<endl;
    for(int i = 0 ; i < 16 ; i++)
    {
        cout<< std::hex<<setfill('0') << setw(2)<<(int)buf[i]<<" ";
    }
    cout<<endl;
#endif /*_DEBUG*/
}
static void  mixColumns_dec(unsigned char* buf)
{
    // make it larger to avoid over flow of multiplication
    unsigned char temp_state[16];
    temp_state[0] = mulBin(buf[0],14) ^ mulBin(buf[1],11) ^ mulBin(buf[2],13) ^ mulBin(buf[3],9);
    temp_state[1] = mulBin(buf[0],9) ^ mulBin(buf[1],14) ^ mulBin(buf[2],11) ^ mulBin(buf[3],13);
    temp_state[2] = mulBin(buf[0],13) ^ mulBin(buf[1],9) ^ mulBin(buf[2],14) ^ mulBin(buf[3],11);
    temp_state[3] = mulBin(buf[0],11) ^ mulBin(buf[1],13) ^ mulBin(buf[2],9) ^ mulBin(buf[3],14);
    temp_state[4] = mulBin(buf[4],14) ^ mulBin(buf[5],11) ^ mulBin(buf[6],13) ^ mulBin(buf[7],9);
    temp_state[5] = mulBin(buf[4],9) ^ mulBin(buf[5],14) ^ mulBin(buf[6],11) ^ mulBin(buf[7],13);
    temp_state[6] = mulBin(buf[4],13) ^ mulBin(buf[5],9) ^ mulBin(buf[6],14) ^ mulBin(buf[7],11);
    temp_state[7] = mulBin(buf[4],11) ^ mulBin(buf[5],13) ^ mulBin(buf[6],9) ^ mulBin(buf[7],14);
    temp_state[8] = mulBin(buf[8],14) ^ mulBin(buf[9],11) ^ mulBin(buf[10],13) ^ mulBin(buf[11],9);
    temp_state[9] = mulBin(buf[8],9) ^ mulBin(buf[9],14) ^ mulBin(buf[10],11) ^ mulBin(buf[11],13);
    temp_state[10]= mulBin(buf[8],13) ^ mulBin(buf[9],9) ^ mulBin(buf[10],14) ^ mulBin(buf[11],11);
    temp_state[11] = mulBin(buf[8],11) ^ mulBin(buf[9],13) ^ mulBin(buf[10],9) ^ mulBin(buf[11],14);
    temp_state[12] = mulBin(buf[12],14) ^ mulBin(buf[13],11)^ mulBin(buf[14],13) ^ mulBin(buf[15],9);
    temp_state[13] = mulBin(buf[12],9) ^ mulBin(buf[13],14) ^ mulBin(buf[14],11) ^ mulBin(buf[15],13);
    temp_state[14] = mulBin(buf[12],13) ^ mulBin(buf[13],9) ^ mulBin(buf[14],14) ^ mulBin(buf[15],11);
    temp_state[15] = mulBin(buf[12],11) ^ mulBin(buf[13],13) ^ mulBin(buf[14],9) ^ mulBin(buf[15],14);

    for (int i = 0; i < 16; i++) {
        buf[i] = temp_state[i];
    }
#ifdef _DEBUG
    cout<<__FUNCTION__<<endl;
    for(int i = 0 ; i < 16 ; i++)
    {
        cout<< std::hex<<setfill('0') << setw(2)<<(int)buf[i]<<" ";
    }
    cout<<endl;
#endif /*_DEBUG*/

}
static void  byteSub(unsigned char* buf,int len)
{
    for(int i = 0 ; i < len ; i++)
    {
        buf[i] = subBye_transform[buf[i]];
    }
#ifdef _DEBUG
    cout<<__FUNCTION__<<endl;
    for(int i = 0 ; i < 16 ; i++)
    {
        cout<< std::hex<<setfill('0') << setw(2)<<(int)buf[i]<<" ";
    }
    cout<<endl;
#endif /*_DEBUG*/
}
static void  byteSub_dec(unsigned char* buf,int len)
{
    for(int i = 0 ; i < len ; i++)
    {
        buf[i] = invSubBye_transform[buf[i]];
    }
#ifdef _DEBUG
    cout<<__FUNCTION__<<endl;
    for(int i = 0 ; i < 16 ; i++)
    {
        cout<< std::hex<<setfill('0') << setw(2)<<(int)buf[i]<<" ";
    }
    cout<<endl;
#endif /*_DEBUG*/
}
static void  rotByte(unsigned char* buf)
{
    //data is arrangend col by col not row by row
    unsigned char temp_state[16];
    temp_state[0] = buf[0];
    temp_state[1] = buf[5];
    temp_state[2] = buf[10];
    temp_state[3] = buf[15];
    temp_state[4] = buf[4];
    temp_state[5] = buf[9];
    temp_state[6] = buf[14];
    temp_state[7] = buf[3];
    temp_state[8] = buf[8];
    temp_state[9] = buf[13];
    temp_state[10] = buf[2];
    temp_state[11] = buf[7];
    temp_state[12] = buf[12];
    temp_state[13] = buf[1];
    temp_state[14] = buf[6];
    temp_state[15] = buf[11];
    for (int i = 0; i < 16; i++) {
        buf[i] = temp_state[i];
    }
#ifdef _DEBUG
    cout<<__FUNCTION__<<endl;
    for(int i = 0 ; i < 16 ; i++)
    {
        cout<< std::hex<<setfill('0') << setw(2)<<(int)buf[i]<<" ";
    }
    cout<<endl;
#endif /*_DEBUG*/
}
static void  rotByte_dec(unsigned char* buf)
{
    //data is arrangend col by col not row by row
    unsigned char temp_state[16];
    temp_state[0] = buf[0];
    temp_state[1] = buf[13];
    temp_state[2] = buf[10];
    temp_state[3] = buf[7];
    temp_state[4] = buf[4];
    temp_state[5] = buf[1];
    temp_state[6] = buf[14];
    temp_state[7] = buf[11];
    temp_state[8] = buf[8];
    temp_state[9] = buf[5];
    temp_state[10] = buf[2];
    temp_state[11] = buf[15];
    temp_state[12] = buf[12];
    temp_state[13] = buf[9];
    temp_state[14] = buf[6];
    temp_state[15] = buf[3];
    for (int i = 0; i < 16; i++) {
        buf[i] = temp_state[i];
    }
#ifdef _DEBUG
    cout<<__FUNCTION__<<endl;
    for(int i = 0 ; i < 16 ; i++)
    {
        cout<< std::hex<<setfill('0') << setw(2)<<(int)buf[i]<<" ";
    }
    cout<<endl;
#endif /*_DEBUG*/
}
static void addRoundKey(unsigned char* buf,vector<unsigned char>::iterator key_start)
{
    for(int i =  0 ; i < 16 ;i++){
        buf[i] = buf[i]^(*(key_start));
        key_start++;
    }
#ifdef _DEBUG
    cout<<__FUNCTION__<<endl;
    for(int i = 0 ; i < 16 ; i++)
    {
        cout<< std::hex<<setfill('0') << setw(2)<<(int)buf[i]<<" ";
    }
    cout<<endl;
#endif /*_DEBUG*/
}
static void expandKey(vector<unsigned char>& key, uint8_t Nk, uint8_t Nr)
{
    unsigned char temp[4];
    unsigned char temp2;

    //first copy are already here
    //loop for number of words
    uint16_t i = Nk;
    while (i < (4 * (Nr+1))){
        uint16_t index = (i-Nk)*4 + Nk*4;
        temp[0] = key[(index-4)];
        temp[1] = key[(index-4)+1];
        temp[2] = key[(index-4)+2];
        temp[3] = key[(index-4)+3];

        if (i%Nk == 0){
            //rot sub
            temp2 = temp[0];
            temp[0] = subBye_transform[temp[1]]^RCON[i/Nk];
            temp[1] = subBye_transform[temp[2]];
            temp[2] = subBye_transform[temp[3]];
            temp[3] = subBye_transform[temp2];
        }
        else if (Nk > 6 && i%Nk == 4){
            temp[0] = subBye_transform[temp[0]];
            temp[1] = subBye_transform[temp[1]];
            temp[2] = subBye_transform[temp[2]];
            temp[3] = subBye_transform[temp[3]];
        }
        key[index]   = key[(index-Nk*4)]^temp[0];
        key[index+1] = key[(index-Nk*4)+1]^temp[1];
        key[index+2] = key[(index-Nk*4)+2]^temp[2];
        key[index+3] = key[(index-Nk*4)+3]^temp[3];
        i = i + 1;
    }
#ifdef _DEBUG
    cout<<__FUNCTION__<<endl;
    for(int i = 0 ; i < key.size() ; i++)
    {
        if(i%16 == 0) cout<<endl;
        cout<< std::hex<<setfill('0') << setw(2)<<(int)key[i]<<" ";
    }
    cout<<endl;
#endif /*_DEBUG*/
}
static void intialRound(unsigned char* buf,vector<unsigned char>::iterator key_start)
{
    for (int i = 0; i < 16; i++)
    {
        buf[i] ^= *(key_start+i);
    }
#ifdef _DEBUG
    cout<<__FUNCTION__<<endl;
    for(int i = 0 ; i < 16 ; i++)
    {
        cout<< std::hex<<setfill('0') << setw(2)<<(int)buf[i]<<" ";
    }
    cout<<endl;
#endif /*_DEBUG*/
}
static void Block_Encrypt(vector<unsigned char>::iterator buf_start,vector<unsigned char> &key, uint8_t Nr)
{
    unsigned char state[16];
    for(int i = 0 ; i < 16 ; i++)
    {
        state[i] = *(buf_start+i);
    }
    //intial round
    intialRound(state,key.begin());
    for(int i = 1 ; i <= Nr-1 ; i++)
    {
#ifdef _DEBUG
        cout<<"Round "<<i<<endl;
#endif /*_DEBUG*/
        byteSub(state,16);
        rotByte(state);
        mixColumns(state);
        addRoundKey(state,key.begin()+(16*i));
    }

    byteSub(state,16);
    rotByte(state);
    addRoundKey(state,key.begin()+(Nr*16));

    for(int i = 0 ; i < 16 ; i++)
    {
       *(buf_start+i) = state[i] ;
    }
}
static void Block_Decrypt(vector<unsigned char>::iterator buf_start,vector<unsigned char> &key, uint8_t Nr )
{
    unsigned char state[16];
    for(int i = 0 ; i < 16 ; i++)
    {
        state[i] = *(buf_start+i);
    }
    //intial round
    addRoundKey(state,key.begin()+(Nr*16));
    rotByte_dec(state);
    byteSub_dec(state,16);
    for(int i = Nr-1 ; i >= 1 ; i--)
    {
#ifdef _DEBUG
        cout<<"Round "<<i<<endl;
#endif /*_DEBUG*/
        addRoundKey(state,key.begin()+(16*i));
        mixColumns_dec(state);
        rotByte_dec(state);
        byteSub_dec(state,16);
    }
    addRoundKey(state,key.begin());

    for(int i = 0 ; i < 16 ; i++)
    {
        *(buf_start+i) = state[i] ;
    }
}
AES_ERROR AES_Encrypt(vector<unsigned char> key, vector<unsigned char> Buf, vector<unsigned char>& BufEncrypt,AES_MODE mode,AES_TYPE type)
{
    freopen( "encrypt.debug", "w", stdout);
    uint8_t Nk, Nr;
    //TODO: buf should be padded
    //Split the block based on the type of the encryption

    if(mode== AES128){
        Nr = 10;
        Nk = 4;
    }
    else if(mode== AES192){
        Nr = 12;
        Nk = 6;
    }
    else if (mode== AES256){
        Nr = 14;
        Nk = 8;
    }
    else {
        return INVALID_KEY;
    }

    //16 * (number of rounds =10 +1) = 176 bytes =44 words
    key.resize(4*4*(Nr+1));
    expandKey(key, Nk, Nr);

    //Pad the size to be multiple of 16 bytes
//#ifdef PAD_RFC5652
    if(type == RFC5652)
    {
        int pad_size = 16-(Buf.size()%16);
        Buf.resize(Buf.size()+pad_size);
        for(int i = Buf.size()-1 ; i >=Buf.size()-pad_size;i--)
        {
            Buf[i] = pad_size;
        }
    }
    else
    {
//#else
        Buf.resize(((Buf.size()+15)/16)*16);
//#endif /*PAD_RFC5652*/
    }

    BufEncrypt.resize(Buf.size());
    BufEncrypt = Buf;
    //for each block if 16 bytes
    for(int i = 0 ; i  < Buf.size() ; i+=16)
    {
        Block_Encrypt(BufEncrypt.begin()+i,key, Nr);
    }
    cout<<"Encrypted Message\n";
    for(int i = 0 ; i < BufEncrypt.size() ; i++ )
    {
        if((i%16) == 0)
            cout<<endl;
        cout<< std::hex<<setfill('0') << setw(2)<<(int)BufEncrypt[i]<<" ";

    }
    cout<<endl;

}
AES_ERROR AES_Decrypt(vector<unsigned char> key, vector<unsigned char> Buf, vector<unsigned char>& BufDecrypt,AES_MODE mode,AES_TYPE type)
{
    freopen( "decrypt.debug", "w", stdout);
    uint8_t Nk, Nr;

    if(mode== AES128){
        Nr = 10;
        Nk = 4;
    }
    else if(mode== AES192){
        Nr = 12;
        Nk = 6;
    }
    else if (mode== AES256){
        Nr = 14;
        Nk = 8;
    }
    else {
        return INVALID_KEY;
    }


    key.resize(4*4*(Nr+1));
    expandKey(key, Nk, Nr);

    //Buf.resize(((Buf.size()+15)/16)*16);
    BufDecrypt.resize(Buf.size());
    BufDecrypt = Buf;
    for(int i = 0 ; i  < Buf.size() ; i+=16)
    {
        Block_Decrypt(BufDecrypt.begin()+i,key, Nr);
    }
//#ifdef PAD_RFC5652
    if(type == RFC5652)
    {
        int pad_size = BufDecrypt[BufDecrypt.size()-1];
        BufDecrypt.resize(BufDecrypt.size()-pad_size);
    }
//#endif /*PAD_RFC5652*/
    //
    cout<<"Decrypted Message\n";
    for(int i = 0 ; i < BufDecrypt.size() ; i++ )
    {
        if((i%16) == 0)
            cout<<endl;
        cout<< std::hex<<setfill('0') << setw(2)<<(int)BufDecrypt[i]<<" ";
    }
    cout<<endl;
}
