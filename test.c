#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "aes.h"
#include "enc.h"
#include "log.h"

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

//////// CBC

    uint8_t   cbc_iv[16]      = {0x99, 0xa6, 0x92, 0xb8, 0x68, 0xbb, 0xec, 0xb7, 0xeb, 0x80, 0x13, 0xee, 0xde, 0x61, 0xa1, 0x02};
    uint8_t cbc_data[12 * 16] = {0x2e, 0xc4, 0x83, 0xc4, 0xcd, 0x88, 0xfa, 0x0d, 0x35, 0xef, 0x1e, 0xe4, 0x2c, 0xee, 0x16, 0x84,
                                 0xc3, 0xdd, 0xb5, 0x93, 0x06, 0x91, 0x91, 0x41, 0xd6, 0x5c, 0x8b, 0x57, 0x5c, 0x35, 0xb1, 0x1c,
                                 0xb2, 0xeb, 0xef, 0xe4, 0xa7, 0xac, 0xa6, 0xfd, 0x5d, 0xf9, 0xdc, 0x25, 0x76, 0xd8, 0xf9, 0x38,
                                 0xfe, 0x0c, 0x90, 0x2b, 0x41, 0x24, 0xad, 0xe0, 0xa2, 0x13, 0x78, 0x04, 0x39, 0x45, 0x4b, 0xe6,
                                 0xe3, 0x0b, 0x0e, 0x08, 0xc7, 0x69, 0x43, 0x30, 0x3d, 0x5f, 0x71, 0x1a, 0x44, 0xa6, 0xb0, 0x1a,
                                 0x17, 0x2d, 0x93, 0xb2, 0x91, 0xb6, 0xfc, 0x26, 0xc3, 0x84, 0xbd, 0x9b, 0x06, 0x54, 0xa1, 0x4f,
                                 0x13, 0x8a, 0xd4, 0x61, 0x27, 0x39, 0x26, 0xa5, 0x06, 0xdc, 0x0c, 0xdd, 0x1c, 0x44, 0x74, 0x65,
                                 0xa9, 0x48, 0xb8, 0x9e, 0xc8, 0xe5, 0x7c, 0x83, 0xb8, 0x27, 0xb2, 0x5c, 0x9c, 0x4a, 0x93, 0x4a,
                                 0x59, 0x6e, 0xfb, 0xe2, 0xd2, 0xa5, 0xd1, 0x32, 0x97, 0xc0, 0xad, 0xbf, 0x2c, 0x42, 0x3a, 0x2d,
                                 0x3c, 0xae, 0x26, 0x9c, 0x80, 0x97, 0xb1, 0x87, 0x7b, 0x4c, 0xd7, 0x32, 0xbc, 0xfb, 0x56, 0xa4,
                                 0x29, 0x70, 0x62, 0xa6, 0x56, 0x0d, 0x9f, 0x26, 0x13, 0xb3, 0x8b, 0x58, 0x4e, 0xbb, 0x43, 0x62,
                                 0x9d, 0xfd, 0xe2, 0xc8, 0x88, 0x9e, 0xdf, 0x0d, 0x1a, 0xa7, 0xc2, 0xa6, 0x53, 0xf0, 0xfd, 0xb5
                                };
    uint8_t cbc_key[16]       = {0xad, 0x5f, 0x51, 0xd7, 0x8f, 0xf7, 0x0a, 0x45, 0x24, 0xf1, 0xba, 0x57, 0x9e, 0xd9, 0xf7, 0x54};

    const
    uint8_t  cbc_exp[12 * 16] = {0x3f, 0x7a, 0x41, 0x17, 0x29, 0xfc, 0x13, 0xda, 0xd4, 0xb7, 0xd9, 0x88, 0x6c, 0xd5, 0xc0, 0xfd,
                                 0x13, 0xd8, 0x7d, 0xd8, 0x5b, 0x88, 0x72, 0x1b, 0xa0, 0x34, 0x18, 0x88, 0x70, 0x7f, 0xbb, 0x28,
                                 0x43, 0x28, 0xa5, 0xe0, 0x76, 0xd8, 0xbc, 0x59, 0xb6, 0x32, 0x65, 0x4e, 0xf3, 0x56, 0x12, 0x74,
                                 0x41, 0xf8, 0x86, 0x54, 0x9c, 0xea, 0x79, 0x8a, 0x6b, 0x0e, 0xdf, 0xc6, 0xf4, 0x5f, 0xb4, 0x6d,
                                 0x6f, 0xa3, 0x3d, 0xfe, 0xa4, 0x74, 0x31, 0xd8, 0x44, 0xec, 0xf6, 0x08, 0xac, 0xd8, 0xa1, 0x96,
                                 0x42, 0x04, 0x8e, 0x6c, 0x84, 0x55, 0xdb, 0xdc, 0x60, 0x06, 0xf8, 0x13, 0x15, 0x90, 0x58, 0x04,
                                 0x5e, 0xfd, 0xce, 0xa7, 0xc2, 0x38, 0x78, 0x37, 0x6f, 0x90, 0x97, 0x6f, 0xdf, 0x28, 0xcd, 0xe8,
                                 0xd2, 0x4a, 0x1d, 0x36, 0x67, 0x2d, 0xa0, 0xd1, 0x81, 0xb8, 0xa6, 0xeb, 0x1b, 0x1b, 0x73, 0x32,
                                 0x97, 0xe8, 0x9e, 0xdd, 0xd1, 0x05, 0xfb, 0xc0, 0x80, 0xa1, 0xd6, 0x5e, 0xc0, 0x2b, 0x83, 0x4b,
                                 0x49, 0xb8, 0x07, 0xf5, 0x43, 0xc9, 0x00, 0x46, 0xcb, 0x2e, 0xc7, 0xfb, 0x75, 0x0d, 0xb9, 0xec,
                                 0xfc, 0xf0, 0x2c, 0x6e, 0xba, 0x02, 0x5f, 0x2b, 0xd9, 0x84, 0x19, 0x7d, 0xff, 0x80, 0x04, 0x43,
                                 0xa4, 0x98, 0x0a, 0x1b, 0x12, 0x47, 0x4c, 0xf6, 0x6e, 0x6d, 0xe2, 0xee, 0xc6, 0x24, 0x7f, 0x78
                                };

    uint8_t * out_big = malloc(1024);
    ret = aes_encrypt(AES_MODE_CBC, cbc_data, out_big, 1024, cbc_key, cbc_iv);
    // print_blocks(out_big, 12, 0);

    printf("CBC CHECK: ");
    if (ret == 0)
    {
        if (memcmp(out_big, cbc_exp, sizeof(cbc_exp)) == 0)
        {
            puts("OK");
        }
        else
        {
            puts("FAILURE");
        }
    }
    else
    {
        puts("FAILURE");
    }
    free (out_big);

    return failure;
}