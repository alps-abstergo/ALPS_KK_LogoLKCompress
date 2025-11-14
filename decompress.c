/*
   decompress.c -- Deompress to BMP bitmap ALPS source LK logo to saving space

   Copyright (C) 2025 alps-abstergo
   All Rights Reserved.

   The LZO library is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of
   the License, or (at your option) any later version.

   The LZO library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with the LZO library; see the file COPYING.
   If not, write to the Free Software Foundation, Inc.,
   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/

#include "minilzo.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HEAP_ALLOC(var,size) \
    lzo_align_t __LZO_MMODEL var [ ((size) + (sizeof(lzo_align_t) - 1)) / sizeof(lzo_align_t) ]

#pragma pack(push, 1)
typedef struct {
    unsigned short bfType;
    unsigned int   bfSize;
    unsigned short bfReserved1;
    unsigned short bfReserved2;
    unsigned int   bfOffBits;
} BITMAPFILEHEADER;

typedef struct {
    unsigned int   biSize;
    int            biWidth;
    int            biHeight;
    unsigned short biPlanes;
    unsigned short biBitCount;
    unsigned int   biCompression;
    unsigned int   biSizeImage;
    int            biXPelsPerMeter;
    int            biYPelsPerMeter;
    unsigned int   biClrUsed;
    unsigned int   biClrImportant;
} BITMAPINFOHEADER;
#pragma pack(pop)

typedef struct
{
	unsigned int   nMagic;
	int 		   nW;
	int 		   nH;
	int 		   nSize;
} BMC_HDR;

BITMAPFILEHEADER fileHeader;
BITMAPINFOHEADER infoHeader;
	

static int read_bmc_file(const char *filename, unsigned char **data, size_t *size, size_t* osize) {
    FILE *fp;
    size_t bitmap_size;
    
    fp = fopen(filename, "rb");
    if (!fp) {
        fprintf(stderr, "fail open input file '%s'\n", filename);
        return -1;
    }
    
    if (fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, fp) != 1) {
        fprintf(stderr, "cannot read hdr\n");
        fclose(fp);
        return -1;
    }
    
    if (fileHeader.bfType != 'CB') {
        fprintf(stderr, "header is not BMC\n");
        fclose(fp);
        return -1;
    }
    
    if (fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, fp) != 1) {
        fprintf(stderr, "fail read infohdr\n");
        fclose(fp);
        return -1;
    }
    
    bitmap_size = infoHeader.biSizeImage;
    if (bitmap_size == 0) {
        int row_size = ((infoHeader.biWidth * infoHeader.biBitCount + 31) / 32) * 4;
        bitmap_size = row_size * abs(infoHeader.biHeight);
    }
    
    *data = (unsigned char *)malloc(bitmap_size);
    if (!*data) {
        fprintf(stderr, "fail allocate memory for bitmap data\n");
        fclose(fp);
        return -1;
    }
    
    fseek(fp, fileHeader.bfOffBits, SEEK_SET);
    
    if (fread(*data, 1, bitmap_size, fp) != bitmap_size) {
        fprintf(stderr, "fail read rawdata\n");
        free(*data);
        fclose(fp);
        return -1;
    }
    
    *size = bitmap_size;
	
	if ((fileHeader.bfReserved1|(fileHeader.bfReserved2<<16)) == 0)
	{
//wz 20251115 debugging
		fprintf(stderr, "fail bmp indata is null -----> origianl file is %s\n", filename);
//wz 20251115 debugging
        free(*data);
        fclose(fp);
        return -1;
    }
	*osize = fileHeader.bfReserved1|(fileHeader.bfReserved2<<16);
	
	fclose(fp);
    
    return 0;
}

static int write_bmp_file(const char *filename, const unsigned char *data, size_t size) {
    FILE *fp;
    
    fp = fopen(filename, "wb");
    if (!fp) {
        fprintf(stderr, "fail create output file '%s'\n", filename);
        return -1;
    }
	
	//change magic
	fileHeader.bfType = 'MB';
	fileHeader.bfReserved1 = 0;
	fileHeader.bfReserved2 = 0;
	infoHeader.biSizeImage = size;
    
	if (fwrite(&fileHeader, 1, sizeof(BITMAPFILEHEADER), fp) != sizeof(BITMAPFILEHEADER)) {
        fprintf(stderr, "fail write header\n");
        fclose(fp);
        return -1;
    }

	if (fwrite(&infoHeader, 1, sizeof(BITMAPINFOHEADER), fp) != sizeof(BITMAPINFOHEADER)) {
        fprintf(stderr, "fail write infoheader\n");
        fclose(fp);
        return -1;
    }

    if (fwrite(data, 1, size, fp) != size) {
        fprintf(stderr, "fail write compressed data\n");
        fclose(fp);
        return -1;
    }
    
    fclose(fp);
    return 0;
}

int main(int argc, char *argv[]) {
    unsigned char *input_data = NULL;
    unsigned char *output_data = NULL;
    size_t input_size;
    lzo_uint output_size;
    int result;
    HEAP_ALLOC(wrkmem, LZO1X_1_MEM_COMPRESS);
    
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input.bmc> <output.bmp>\n", argv[0]);
        return 1;
    }
    
    if (lzo_init() != LZO_E_OK) {
        fprintf(stderr, "init lzo fail\n");
        return 1;
    }
    
    if (read_bmc_file(argv[1], &input_data, &input_size, &output_size) != 0) {
        return 1;
    }
    
    output_data = (unsigned char *)malloc(output_size*2);
    if (!output_data) {
        fprintf(stderr, "fail allocate output buffer\n");
        free(input_data);
        return 1;
    }
    
	int noutsize = output_size;
	
    result = lzo1x_decompress_safe(input_data, input_size, 
                              output_data, &noutsize, 
                              NULL);
    
    if (result != LZO_E_OK) {
        fprintf(stderr, "fail decompression (error code: %d)\n", result);
        free(input_data);
        free(output_data);
        return 1;
    }
	
	if (output_size != noutsize)
	{
		fprintf(stderr, "fail decompression (wrong size)\n", result);
        free(input_data);
        free(output_data);
        return 1;
    }
	
    
    printf("decompress size: %lu (%.2f%% of original)\n", 
           (unsigned long)output_size, 
           (output_size * 100.0) / input_size);
    
    if (write_bmp_file(argv[2], output_data, output_size) != 0) {
        free(input_data);
        free(output_data);
        return 1;
    }
    
    printf("'%s' -> '%s'\n", argv[1], argv[2]);
    
    free(input_data);
    free(output_data);
    
    return 0;
}