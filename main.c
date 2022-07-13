#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    char str[1000];
    int img[1024][768];
    int w, h;
    int d;
    int x, y;
    FILE *fp1, *fp2;

    if ((fp1 = fopen(argv[1], "r")) == NULL) {
        perror( argv[1] );
        exit(1);
    }
    if ((fp2 = fopen(argv[2], "r")) == NULL) {
        perror( argv[2] );
        exit(1);
    }
    fscanf(fp1, "%s", str);
    fscanf(fp1, "%d %d", &w, &h);
    fscanf(fp1, "%d", &d);

    for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {
            fscanf(fp1, "%d", &img[x][y]);
        }
    }
    for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {
            img[x][y] = 255 - img[x][y];
        }
    }

    fprintf(fp2, "%s\n%d %d\n%d\n", str, w, h, d);
    for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {
            fprintf(fp2, "%d ", img[x][y]);
        }
        fprintf(fp2, "\n");
    }
    fclose(fp1);
    fclose(fp2);

    return 0;
}
