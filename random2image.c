#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <assert.h>
#include <stdint.h>
//#include "toBigEndian.h"

#define N 8192

//typedef struct RGBA_fileHeader
//{
//    char magicNumber[4];
//    uint32_t width_in_pixels;
//    uint32_t height_in_pixels;
//} RGBAfileHeader;// ={{, N_bigendian, N_bigendian};

typedef struct PAM_fileHeader
{
    char magicNumber[2 +1]; // = {'P', '7', '\n'};
    //char[6] width_str;// = {'W', 'I', 'D', 'T', 'H', ' '};
    int width_number;
    //char[7] height_str;// = {'H', 'E', 'I', 'G', 'H', 'T', ' '};
    int height_number;
    //char[7] maxval_str;// = {'M', 'A', 'X', 'V', 'A', 'L', ' '};
    int depth_number;
    int maxval_number;
    //char[9] tupltype_str;// = {'T', 'U', 'P', 'L', 'T', 'Y', 'P', 'E', ' '};
    char tupltype_type[9 +1];
    //char[] ={'E', 'N', 'D', 'H', 'D', 'R'}
} PAMfileHeader;

//only variables in struct, and leave the constant string (e.g. "WIDTH") to fprintf. At this time, char[] shouldn't length of srting+1



int main(void)
{
    srand(time(NULL));

    //unsigned int rows =N, cols =N;

    //unsigned int random2image[N][N];
    unsigned int  (*random2image)[N] = calloc(N, sizeof(*random2image));
    assert(random2image != NULL);

//    int random_variable = rand();
//    printf("Random value on [0,%d]: %d\n", RAND_MAX, random_variable);
//    printf("siezof(int): %zuByte, int_max: %d, unsignedint_max %u, RAND_MAX:%llX, sizeof(random2image): %zu\n", \
//        sizeof(int), \
//        (int)((1ULL << (8*sizeof(int)-1ULL))-1ULL), \
//        (unsigned int)((1ULL << 8*sizeof(int))-1ULL), \
//        RAND_MAX, \
//        sizeof(random2image) \
//    );
//
//    printf("INT_WIDTH: %ubit, INT_MAX: %d, UINT_MAX %u, RAND_MAX:%llX, sizeof(random2image): %zu\n", \
//        INT_WIDTH, \
//        //INT_WIDTH need C23 standard
//        INT_MAX, \
//        UINT_MAX, \
//        RAND_MAX, \
//        sizeof(random2image) \
//    );


    for(unsigned int i =0; i <N; i++)
    {
        for (unsigned int j =0; j <N; j++)
        {
            unsigned int temp = rand();

            random2image[i][j] = (temp << 16) | (temp >> (sizeof(int) - 16));
            //random2image[i][j] = temp;
        }
    }

//    uint32_t N_bigendian = to_big_endian32(N);
//    RGBAfileHeader rgbafileheader = {{'R', 'G', 'B', 'A'}, N_bigendian, N_bigendian};
//    rgbafileheader.magicNumber ={'R', 'G', 'B', 'A'};
//    rgbafileheader.width_in_pixels = N_bigendian;
//    rgbafileheader.height_in_pixels =N_bigendian;
    PAMfileHeader pamfileheader = { .magicNumber = "P7", .width_number =N, .height_number=N, .depth_number=4, .maxval_number = 255, .tupltype_type = "RGB_ALPHA"};

//    FILE * rand2image_rgba = fopen("rand2image.rgba", "wb");
//    assert(rand2image_rgba != NULL);
//    fwrite(&rgbafileheader, sizeof(rgbafileheader), 1, rand2image_rgba);
//    fwrite(random2image, sizeof(random2image[0]), sizeof(random2image)/sizeof(random2image[0]), rand2image_rgba);
//    fclose(rand2image_rgba);

//    char t[5] = "test";
//    FILE * test_str_tailing0 = fopen("teststrtailing0", "wb");
//    assert(test_str_tailing0 != NULL);
//    fprintf(test_str_tailing0, "test: %s\n", t);
//    fclose(test_str_tailing0);

    FILE * rand2image_pam= fopen("rand2image.pam", "wb");
    assert(rand2image_pam != NULL);
    fprintf(rand2image_pam, "%s\nWIDTH %d\nHEIGHT %d\nDEPTH %d\nMAXVAL %d\nTUPLTYPE %s\nENDHDR\n", \
        pamfileheader.magicNumber, \
        pamfileheader.width_number, \
        pamfileheader.height_number, \
        pamfileheader.depth_number, \
        pamfileheader.maxval_number, 
        pamfileheader.tupltype_type\
    );
    fwrite(random2image, sizeof(random2image[0][0]), N*N, rand2image_pam);
    fclose(rand2image_pam);

    //free(random2image);

    printf("Done!\n");

    return 0;
}
