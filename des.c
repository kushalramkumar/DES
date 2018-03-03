#include <stdio.h>
#include <stdint.h>

const uint32_t PC_1[56] = {57, 49, 41, 33, 25, 17, 9,
                    1, 58, 50, 42, 34, 26, 18,
                    10, 2, 59, 51, 43, 35, 27,
                    19, 11, 3, 60, 52, 44, 36,
                    63, 55, 47, 39, 31, 23, 15,
                    7, 62, 54, 46, 39, 30, 22,
                    14, 6, 61, 53, 45, 37, 29,
                    21, 13, 5, 28, 20, 12, 4};

const uint32_t PC_2[48] = {14, 17, 11, 24, 1, 5,
                            3, 28, 15, 6, 21, 10,
                            23, 19, 12, 4, 26, 8,
                            16, 7, 27, 20, 13, 2,
                            41, 52, 31, 37, 47, 55,
                            30, 40, 51, 45, 33, 48,
                            44, 49, 39, 56, 34, 53,
                            46, 42, 50, 36, 29, 32};

typedef struct{
    uint32_t Ci:28;
    uint32_t Di:28;
    uint64_t Ti:56;
    uint64_t Ki:48;
}RoundKey;

#define GET_BIT(x, pos) (((x) >> (64-pos)) & (1))
#define GET_BIT_56(x, pos) (((x) >> (56-pos)) & (1))
#define ROTATE_LEFT_28(x,n) ((x << n) | (x >> (28-n)))

void DES_GenerateRoundKeys(uint64_t xDesKey)
{
    RoundKey R1;
    R1.Ci = 0; R1.Di = 0; R1.Ki = 0;
    for(uint32_t i = 0; i < 28; i++)
    {
        R1.Ci |= GET_BIT(xDesKey, PC_1[i]) << (27-i);
        R1.Di |= GET_BIT(xDesKey, PC_1[28+i]) << (27-i);
    }
    for(uint32_t i = 1; i <= 16; i++)
    {
        R1.Ti = 0;
        R1.Ki = 0;
        if((1 == i) || (2 == i) || (9 == i) || (16 == i))
        {
            R1.Ci = ROTATE_LEFT_28(R1.Ci, 1);
            R1.Di = ROTATE_LEFT_28(R1.Di, 1);
        }
        else
        {
            R1.Ci = ROTATE_LEFT_28(R1.Ci, 2);
            R1.Di = ROTATE_LEFT_28(R1.Di, 2);
        }
        R1.Ti = R1.Ci;
        R1.Ti = (R1.Ti << 28) | R1.Di;
        for(uint32_t j = 0; j < 24; j++)
        {
            R1.Ki |= GET_BIT_56(R1.Ti, PC_2[j]) << (47-j);
            R1.Ki |= GET_BIT_56(R1.Ti, PC_2[24+j]) << (23-j);
        }
        printf("K[%d]: %x\n", i, R1.Ki);
    }
}

int main(int argc, char** argv)
{
    uint64_t desKey = 0x011F011F010E010E;
    printf("DES KEY: %llx\n", desKey);
    DES_GenerateRoundKeys(desKey);
    printf("\n");

    desKey = 0x1F011F010E010E01;
    printf("DES KEY: %llx\n", desKey);
    DES_GenerateRoundKeys(desKey);
    return 0;
}