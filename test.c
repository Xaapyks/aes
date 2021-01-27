#include <stdio.h>
#include <string.h>
#include "aes.h"

int main()
{
    int failure = 1;
    int ret;
    uint8_t out[16];

#define KEY_COUNT 2
    uint8_t data[2][16]      = {
        {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff},
        {0xc6, 0x1e, 0x67, 0x65, 0xbb, 0x60, 0x8f, 0xc4, 0x26, 0xed, 0xb3, 0xdf, 0x87, 0x8b, 0x94, 0x03}
    };
    uint8_t key[2][16]       = {
        {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f},
        {0xaf, 0x93, 0x37, 0x67, 0x58, 0xed, 0xdc, 0x61, 0x7d, 0xf8, 0xe4, 0xd1, 0xd0, 0xc3, 0xb1, 0x97}
    };
    uint8_t expected[2][16]  = {
        {0x69, 0xc4, 0xe0, 0xd8, 0x6a, 0x7b, 0x04, 0x30, 0xd8, 0xcd, 0xb7, 0x80, 0x70, 0xb4, 0xc5, 0x5a},
        {0x61, 0x5f, 0x47, 0xf2, 0x2c, 0x4d, 0xd8, 0xd1, 0x78, 0x4b, 0x67, 0x78, 0x6a, 0xfb, 0xa6, 0x5d}
    };

    ret = aes_init();
    if (ret != 0)
    {
        printf("ERROR: l%d\n", __LINE__);
    }

    for (int i = 0; i < KEY_COUNT; ++i)
    {
        aes_encrypt_block(key[i], data[i], out);
        failure = memcmp(expected[i], out, 16);
        printf("TEST %d:", i);
        if (failure != 0)
        {
            puts("FAILURE");

        }
        else
        {
            puts("OK");
        }
    }


    ret = aes_free();
    if (ret != 0)
    {
        printf("ERROR: l%d\n", __LINE__);
    }



    return failure;
}