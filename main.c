#include <stdio.h>
#include <stdlib.h>

#define WIDTH 1024
#define HEIGHT 768

FILE* openFile(char *filename, char *mode) {
    FILE *file = fopen(filename, mode);
    if (file == NULL) {
        perror(filename);
        exit(1);
    }
    return file;
}

void readPGMHeader(FILE *pgmFile, char* type, int *width, int *height, int *max) {
    fscanf(pgmFile, "%s", type);
    fscanf(pgmFile, "%d %d", width, height);
    fscanf(pgmFile, "%d", max);
}

void readImage(int target[][HEIGHT], FILE *pgmFile, int width, int height) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            fscanf(pgmFile, "%d", &target[i][j]);
        }
    }
}

void writeImage(int source[][HEIGHT], FILE *pgmFile, int width, int height) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            fprintf(pgmFile, "%d ", source[i][j]);
        }
        fprintf(pgmFile, "\n");
    }
}

int main(int argc, char **argv) {
    char pgmType[1000];
    int originImage[WIDTH][HEIGHT];
    int targetImage[WIDTH][HEIGHT];
    int imageWidth, imageHeight;
    int maxValue;
    int x, y;
    FILE *originFile = openFile(argv[1], "r");
    FILE *targetFile = openFile(argv[2], "w");

    readPGMHeader(originFile, pgmType, &imageWidth, &imageHeight, &maxValue);
    readImage(originImage, originFile, imageWidth, imageHeight);


    // 画像を処理する

    // ↓白黒反転 検証済み
//    for (y = 0; y < imageHeight; y++) {
//        for (x = 0; x < imageWidth; x++) {
//            targetImage[y][x] = 255 - originImage[y][x];
//        }
//    }
    // ↑白黒反転

    // ↓90度回転 検証済み
    /*
    int halfDifference = (imageWidth - imageHeight) / 2;
    for (y = 0; y < imageHeight; y++) {
        for (x = 0; x < imageWidth; x++) {
            targetImage[y][x + halfDifference] = originImage[imageHeight - x - 1][y + halfDifference];
        }
    }
     */
    // ↑90度回転

    // ↓180度回転 検証済み
    /*
    for (y = 0; y < imageHeight; y++) {
        for (x = 0; x < imageWidth; x++) {
            targetImage[y][x] = originImage[imageHeight - y - 1][x];
        }
    }
     */
    // ↑180度回転

    // ↓270度回転 検証ずみ
    /*
    int halfDifference = (imageWidth - imageHeight) / 2;
    for (y = 0; y < imageHeight; y++) {
        for (x = 0; x < imageWidth; x++) {
            targetImage[y][x + halfDifference] = originImage[x][imageHeight - y - 1 + halfDifference];
        }
    }
    */
    // ↑270度回転

    // ↓左右反転 検証済み
    /*
    for (y = 0; y < imageHeight; y++) {
        for (x = 0; x < imageWidth; x++) {
            targetImage[y][x] = originImage[y][imageWidth - x - 1];
        }
    }
     */
    // ↑左右反転

    // ↓上下反転 検証済み
    /*
    for (y = 0; y < imageHeight; y++) {
        for (x = 0; x < imageWidth; x++) {
            targetImage[y][x] = originImage[imageHeight - y - 1][x];
        }
    }
     */
    // ↑上下反転

    // ↓ 縦横n分の1に縮小 検証済み
    /*
    int n = 3;
    for (y = 0; y * n < imageHeight; y++) {
        for (x = 0; x * n < imageWidth; x++) {
            targetImage[y][x] = originImage[y * n][x * n];
        }
    }
     */
    // ↑ 縦横n分の1に縮小

    fprintf(targetFile, "%s\n%d %d\n%d\n", pgmType, imageWidth, imageHeight, maxValue);
    writeImage(targetImage, targetFile, imageWidth, imageHeight);

    fclose(originFile);
    fclose(targetFile);

    return 0;
}