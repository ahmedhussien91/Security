#ifndef _AES_H_
#define _AES_H_
#include <vector>
//mode differ in key extension length and number of rounds
enum AES_MODE {AES128,AES192,AES256};
enum AES_TYPE {AES_CBC,AES_ECB};

enum AES_ERROR {INVALID_KEY};
//key are not sent as refernce as they should't be modified during key expanison
AES_ERROR AES_Encrypt(std::vector<unsigned char> Key, std::vector<unsigned char> Buf, std::vector<unsigned char>& BufEncrypt,AES_MODE mode,AES_TYPE type = AES_ECB);
AES_ERROR AES_Decrypt(std::vector<unsigned char> Key, std::vector<unsigned char> Buf, std::vector<unsigned char>& BufDncrypt,AES_MODE mode);

#endif /*_AES_H_*/
