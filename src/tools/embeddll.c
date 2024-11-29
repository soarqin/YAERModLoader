#include <lz4.h>
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
    long size2 = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *dll = (char*)malloc(size2);
    if (dll == NULL) {
        fclose(f);
        return -1;
    }
    if (fread(dll, 1, size2, f) != size2) {
        fclose(f);
        goto fail2;
    }
    fclose(f);
    char *compressed_data = (char*)malloc(LZ4_compressBound(size2));
    if (compressed_data == NULL) {
        goto fail2;
    }
    int compressed_size = LZ4_compress_default(dll, compressed_data, size2, LZ4_compressBound(size2));
    if (compressed_size <= 0) {
        goto fail3;
    }
    fwrite(compressed_data, 1, compressed_size, fout);
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
