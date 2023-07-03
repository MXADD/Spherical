//
// (c) MX^Addict 2023 (mxadd@mxadd.org)
//
#include <windows.h>
#include <stdio.h>
#include <vector>
#include <compressapi.h>
#include "ZopFLI/zopfli.h"

#pragma comment (lib, "Cabinet.lib")

#define COMPRESS_ALGORITHM COMPRESS_ALGORITHM_MSZIP // COMPRESS_ALGORITHM_LZMS

const char *CompAlgoName()
{
    switch (COMPRESS_ALGORITHM)
    {
        case COMPRESS_ALGORITHM_INVALID:     return "COMPRESS_ALGORITHM_INVALID";
        case COMPRESS_ALGORITHM_NULL:        return "COMPRESS_ALGORITHM_NULL";
        case COMPRESS_ALGORITHM_MSZIP:       return "COMPRESS_ALGORITHM_MSZIP";
        case COMPRESS_ALGORITHM_XPRESS:      return "COMPRESS_ALGORITHM_XPRESS";
        case COMPRESS_ALGORITHM_XPRESS_HUFF: return "COMPRESS_ALGORITHM_XPRESS_HUFF";
        case COMPRESS_ALGORITHM_LZMS:        return "COMPRESS_ALGORITHM_LZMS";
    }

    return "COMPRESS_ALGORITHM_INVALID";
}

bool LoadInputFile(const char *FileName, std::vector<BYTE> &FileContent)
{
    FILE *Input = fopen(FileName, "rb");
    if (!Input) 
        return false;
    fseek(Input, 0, SEEK_END);
    DWORD Size = ftell(Input);
    fseek(Input, 0, SEEK_SET);
    if (Size == 0)
        return false;
    FileContent.resize(Size);
    fread(FileContent.data(), 1, Size, Input);
    fclose(Input);
    return true;
}

int main(int argc, char* argv[])
{
    std::vector<BYTE> InputMem;
    std::vector<BYTE> OutputMem;

    if (argc != 3)
    {
        printf("%s infilename.bin outfilename.inc\n", argv[0]);
        return 1;
    }

    if (!LoadInputFile(argv[1], InputMem))
    {
        printf("Can't load input file\n");
        return 1;
    }
  
    printf("Payload size: %d bytes\n", InputMem.size());
    const size_t OriginalPayloadSize = InputMem.size();

    // Remove any trailing zeros
    while(InputMem[InputMem.size()-1] == 0) InputMem.pop_back();

    printf("Payload size after stripping tail 0's: %d bytes\n", InputMem.size());

    // Compress
    /*
    {
        OutputMem.resize(InputMem.size()*8, 0);
        DWORD OutputSize = 0;
        COMPRESSOR_HANDLE HCompressor;
        if (!CreateCompressor(COMPRESS_ALGORITHM | COMPRESS_RAW, NULL, &HCompressor)) 
        {
            printf("Compressor error\n");
            return 0;
        }

        if (!Compress(HCompressor, InputMem.data(), InputMem.size(), OutputMem.data(), OutputMem.size(), &OutputSize)) 
        {
            CloseCompressor(HCompressor);
            printf("Compression error\n");
            return 0;
        }
        CloseCompressor(HCompressor);
        OutputMem.resize(OutputSize);

        printf("Payload size after compression: %d bytes (%s)\n", OutputMem.size(), CompAlgoName());
    }
    */

    // Compress (ZopFli) -> Could shave 1 or 2 bytes in some cases
    {
        BYTE *PackedMem = NULL;
        DWORD OutputSize = 0;

        ZopfliOptions Zops;
        Zops.verbose = 1;
        Zops.verbose_more = 0;
        Zops.numiterations = 1024 * 4; 
        Zops.blocksplitting = 1;
        Zops.blocksplittingmax = 16;
        ZopfliCompress(&Zops, ZopfliFormat::ZOPFLI_FORMAT_DEFLATE, InputMem.data(), InputMem.size(), &PackedMem, (size_t*)&OutputSize);

        OutputMem.resize(OutputSize+2);

        // MS-Zip header :[

        OutputMem[0] = 0x43;
        OutputMem[1] = 0x4B;

        memcpy(OutputMem.data()+2, PackedMem, OutputSize);
        free(PackedMem);
    }

    if(OutputMem.size() >= InputMem.size())
    {
        printf("Packed file is bigger than unpacked one ! (%i >= %i)\n", OutputMem.size(), InputMem.size());
        return 1;
    }

    // Test decompression
    {
        DECOMPRESSOR_HANDLE HDecompressor;
        CreateDecompressor(COMPRESS_ALGORITHM | COMPRESS_RAW, NULL, &HDecompressor);
        std::vector<BYTE> TestDecompression; TestDecompression.resize(InputMem.size(), 0);

        if (Decompress(HDecompressor, OutputMem.data(), OutputMem.size(), TestDecompression.data(), TestDecompression.size(), NULL) == FALSE)
        {
            CloseDecompressor(HDecompressor);
            printf("Decompression failed (Codec)\n");
            return 1;
        }

        CloseDecompressor(HDecompressor);

        if (memcmp(TestDecompression.data(), InputMem.data(), InputMem.size()))
        {
            printf("Decompression failed (memcmp)\n");
            return 1;
        }
    }

    // Write final file
    FILE *Output = fopen(argv[2], "wt");

    if (Output)
    {
        fprintf(Output, "; Compressed using: (%s | COMPRESS_RAW)\n\n", CompAlgoName());
        fprintf(Output, "PakInputSize  EQU %d\n",   InputMem.size());
        fprintf(Output, "PakOutputSize EQU %d\n\n", OutputMem.size());
        fprintf(Output, "CompressedPayload:\ndb\t");

        // Remove any trailing zeros from payload, we will put it in zeroed segment
        while(OutputMem[OutputMem.size()-1] == 0) OutputMem.pop_back();

        printf("\n");
        printf("Payload size after compression (deflate) and removing trailing zeros: %d bytes (+2 for header) (%d => %d = %3.3f %%)\n", OutputMem.size(), OriginalPayloadSize, OutputMem.size(), 100.0f * (float(OutputMem.size())/float(OriginalPayloadSize)));

        // Print table
        for (DWORD i = 0; i < OutputMem.size(); i++)
        {
            fprintf(Output, "0x%02X", (DWORD)OutputMem[i]);
            if (i && ((i+1)%16) == 0 && (i != OutputMem.size()-1))
                fprintf(Output, "\ndb\t");
            else
            if (i != OutputMem.size()-1)
                fprintf(Output, ", ");
        }

        fprintf(Output, "\n");
        fclose(Output);
    }

    return 0;
}
