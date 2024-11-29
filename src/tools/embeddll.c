#include <LzmaEnc.h>
#include <Alloc.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        return -1;
    }
    FILE *fout = fopen(argv[1], "a+b");
    if (fout == NULL) {
        return -1;
    }
    FILE *f = fopen(argv[2], "rb");
    if (f == NULL) {
        return -1;
    }
    fseek(f, 0, SEEK_END);
    size_t size2 = ftell(f);
    fseek(f, 0, SEEK_SET);
    Byte *dll = (Byte*)malloc(size2);
    if (dll == NULL) {
        fclose(f);
        return -1;
    }
    if (fread(dll, 1, size2, f) != size2) {
        fclose(f);
        goto fail2;
    }
    fclose(f);
    size_t compressed_size = size2 + size2/3 + 128;
    Byte *compressed_data = (Byte*)malloc(compressed_size);
    if (compressed_data == NULL) {
        goto fail2;
    }
    CLzmaEncProps props;
    LzmaEncProps_Init(&props);
    props.level = 9;
    Byte props_encoded[5];
    size_t props_encoded_size = 5;
    if (LzmaEncode(compressed_data, &compressed_size, dll, size2, &props, props_encoded, &props_encoded_size, 0, NULL, &g_Alloc, &g_Alloc) != SZ_OK) {
        goto fail3;
    }
    fwrite(compressed_data, 1, compressed_size, fout);
    fwrite(props_encoded, 1, 5, fout);
    fwrite(&compressed_size, 1, 4, fout);
    fwrite(&size2, 1, 4, fout);
    fwrite("EMBD", 1, 4, fout);
    fclose(fout);

    free(compressed_data);
    free(dll);
    return 0;

fail3:
    free(compressed_data);
fail2:
    free(dll);
    return -1;
}
