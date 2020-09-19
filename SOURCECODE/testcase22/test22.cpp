#include <iostream>
#include <stdio.h>
#include <string.h>
#include <map>
#include <mutex>
#include <stdlib.h>
#include <pthread.h>
#include <bits/stdc++.h>
#include<ctime>
using namespace std;

bool keyfound = false;
//std::mutex m;
std::map<unsigned long, unsigned long> KeyOneMiddleCipher;
struct param_struct
{
    unsigned short from;
    unsigned short upto;
};

void encode(unsigned short *v, unsigned short *k)
{
    unsigned short n = 32, y = v[0], z = v[1], sum = 0,
                   delta = 0x9e37; /* a key schedule constant */
    while (n-- > 0)
    {
        sum += delta;
        y += ((z << 2) + k[0]) ^ (z + sum) ^ ((z >> 3) + k[1]);
        z += ((y << 2) + k[0]) ^ (y + sum) ^ ((y >> 3) + k[1]);
    }
    v[0] = y;
    v[1] = z;
}

void decode(unsigned short *v, unsigned short *k)
{
    unsigned short n = 32, sum, y = v[0], z = v[1],
                   delta = 0x9e37;
    sum = delta << 5;
    while (n-- > 0)
    {
        z -= ((y << 2) + k[0]) ^ (y + sum) ^ ((y >> 3) + k[1]);
        y -= ((z << 2) + k[0]) ^ (z + sum) ^ ((z >> 3) + k[1]);
        sum -= delta;
    }
    v[0] = y;
    v[1] = z;
}

void *searchTheKey(void *args)
{
	time_t tt;
	struct tm * ti;
    struct param_struct *params = (struct param_struct *)args;
    unsigned short from = params->from;
    unsigned short upto = params->upto;

    std::map<unsigned long, unsigned long>::iterator it;
    unsigned long searchthis;
    char tempCipher[9];
    unsigned short i, j, c[2], tempKey2[2], key1[2];
    for (i = from; i < upto; i++)
    {
        for (j = 0x0000; j < 0xffff; j++)
        {
            if (!keyfound)
            {
                tempKey2[0] = i;
                tempKey2[1] = j;
                c[0] = 0x18b1;
                c[1] = 0xb6ae;
                decode(c, tempKey2);
                snprintf(tempCipher, sizeof(tempCipher), "%04x%04x", c[0], c[1]);
                searchthis = (unsigned long)strtoul(tempCipher, nullptr, 16);
                it = KeyOneMiddleCipher.find(searchthis);
                if (it != KeyOneMiddleCipher.end())
                {

                    key1[0] = (unsigned short)((it->second) >> 16);
                    key1[1] = (unsigned short)(it->second);
                    unsigned short p2[2], p3[2], p4[2];
                    p2[0] = 0x1234;
                    p2[1] = 0x5678;
                    encode(p2, key1);
                    encode(p2, tempKey2);
                    if ((p2[0] == 0x4ad4) && (p2[1] == 0x423d))
                    {
                        p3[0] = 0x6789;
                        p3[1] = 0xdabc;
                        encode(p3, key1);
                        encode(p3, tempKey2);
                        if ((p3[0] == 0xde10) && (p3[1] == 0x1250))
                        {
                            p4[0] = 0x9abc;
                            p4[1] = 0xdeff;
                            encode(p4, key1);
                            encode(p4, tempKey2);
                            if ((p4[0] == 0x0b4e) && (p4[1] == 0x111d))
                            {
                                printf("KEY FOUND: \n");
                                printf("KEY 1 IS %04x %04x \n", key1[0], key1[1]);
                                printf("KEY 2 IS %04x %04x \n", tempKey2[0], tempKey2[1]);
								time (&tt);
                                ti = localtime(&tt);
								cout << "KEY FOUND AT at:   = " << asctime(ti)<<endl;
                                keyfound = true;
                                break;
                            }
                        }
                    }
                }
            }
			else
			{
				break;
			}
        }
		if(keyfound)
			break;
    }
	if(!keyfound)
	{
		cout<<"COULD NOT FIND THE KEY IN THIS THREAD!"<<endl;
	}
}

int main()
{
	pthread_t t1, t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13;
    map<unsigned long, unsigned long>::iterator itr;
    char tempCipher[9], tempKey[9];
    unsigned short plainText[2], tempKey1[2];
    unsigned short i, j;
    unsigned long savedcipher, savedkey;
	time_t tt;
	struct tm * ti;
	time (&tt);
    ti = localtime(&tt);
	cout << "Execution started at:   = " << asctime(ti)<<endl;
    for (i = 0xf618; i < 0xffff; i++)
    {
        for (j = 0x0000; j < 0xffff; j++)
        {
            plainText[0] = 0x0001;
            plainText[1] = 0x0002;
            tempKey1[0] = i;
            tempKey1[1] = j;
            encode(plainText, tempKey1);
            snprintf(tempCipher, sizeof(tempCipher), "%04x%04x", plainText[0], plainText[1]);
            snprintf(tempKey, sizeof(tempKey), "%04x%04x", i, j);
            savedcipher = (unsigned long)strtoul(tempCipher, nullptr, 16);
            savedkey = (unsigned long)strtoul(tempKey, nullptr, 16);
            KeyOneMiddleCipher.insert(pair<unsigned long, unsigned long>(savedcipher, savedkey));
        }
    }

    //for (itr=KeyOneMiddleCipher.begin();itr!=KeyOneMiddleCipher.end();itr++) {
    //printf("%08lx    %08lx \n",itr->first,itr->second);
    cout << "Insertion was successful, size of the map is  " << KeyOneMiddleCipher.size() << endl;

    struct param_struct arg1 = {0x0000, 0x1388};
    struct param_struct arg2 = {0x1388, 0x2710};
    struct param_struct arg3 = {0x2710, 0x3a98};
    struct param_struct arg4 = {0x3a98, 0x4e20};
    struct param_struct arg5 = {0x4e20, 0x61a8};
    struct param_struct arg6 = {0x61a8, 0x7530};
    struct param_struct arg7 = {0x7530, 0x88b8};
    struct param_struct arg8 = {0x88b8, 0x9c40};
    struct param_struct arg9 = {0x9c40, 0xafc8};
    struct param_struct arg10 = {0xafc8, 0xc350};
    struct param_struct arg11 = {0xc350, 0xd6d8};
    struct param_struct arg12 = {0xd6d8, 0xea60};
    struct param_struct arg13= {0xea60, 0xffff};

    pthread_create(&t1, NULL, searchTheKey, (void *)&arg1);
    pthread_create(&t2, NULL, searchTheKey, (void *)&arg2);
    pthread_create(&t3, NULL, searchTheKey, (void *)&arg3);
    pthread_create(&t4, NULL, searchTheKey, (void *)&arg4);
    pthread_create(&t5, NULL, searchTheKey, (void *)&arg5);
    pthread_create(&t6, NULL, searchTheKey, (void *)&arg6);
    pthread_create(&t7, NULL, searchTheKey, (void *)&arg7);
    pthread_create(&t8, NULL, searchTheKey, (void *)&arg8);
    pthread_create(&t9, NULL, searchTheKey, (void *)&arg9);
    pthread_create(&t10, NULL, searchTheKey, (void *)&arg10);
    pthread_create(&t11, NULL, searchTheKey, (void *)&arg11);
    pthread_create(&t12, NULL, searchTheKey, (void *)&arg12);
    pthread_create(&t13, NULL, searchTheKey, (void *)&arg13);


    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    pthread_join(t5, NULL);
    pthread_join(t6, NULL);
    pthread_join(t7, NULL);
    pthread_join(t8, NULL);
    pthread_join(t9, NULL);
    pthread_join(t10, NULL);
    pthread_join(t11, NULL);
    pthread_join(t12, NULL);
    pthread_join(t13, NULL);
	time (&tt);
    ti = localtime(&tt);
	cout << "Execution finished at:   = " << asctime(ti)<<endl;
}
