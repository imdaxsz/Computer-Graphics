#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define H 480
#define W 640

unsigned char outImg[H][W][3];
enum { SOLID, DASH, DOT };
int LT[3][8] = { {1,1,1,1,1,1,1,1},{1,1,1,1,0,0,0,0},{1,1,0,0,1,1,0,0} };

void lineDDA(int x1, int y1, int x2, int y2, int lt)
{
	int dx = x2 - x1, dy = y2 - y1, step, k;
	float xinc, yinc, x = (float)x1, y = (float)y1;

	if (abs(dx) > abs(dy)) step = abs(dx);
	else step = abs(dy);
	xinc = dx / (float)step;
	yinc = dy / (float)step;

	outImg[x1][y1][0] = 0; // start pixel marking(setpixel function)
	int r = rand() % 256;
	int g = rand() % 256;
	int b = rand() % 256;
	//printf("%d %d %d\n", r, g, b);

	for (k = 0; k < step; k++) {
		x += xinc;
		y += yinc;
		if (LT[lt][k % 8]) {
			outImg[(int)(x + 0.5)][(int)(y + 0.5)][0] = r;// marking(setpixel function)
			outImg[(int)(x + 0.5)][(int)(y + 0.5)][1] = g;
			outImg[(int)(x + 0.5)][(int)(y + 0.5)][2] = b;
		}
	}
}

int main(void) {
	FILE *fp;

	int x1, y1, x2, y2;
	srand((unsigned)time(NULL));

	for (int i = 0; i < 3; i++) {
		x1 = rand() % (H - 1); x2 = rand() % (H - 1);
		y1 = rand() % (W - 1); y2 = rand() % (W - 1);
		lineDDA(x1, y1, x2, y2, SOLID);	
	}

	for (int i = 0; i < 3; i++) {
		x1 = rand() % (H - 1); x2 = rand() % (H - 1);
		y1 = rand() % (W - 1); y2 = rand() % (W - 1);
		lineDDA(x1, y1, x2, y2, DASH);
	}

	for (int i = 0; i < 3; i++) {
		x1 = rand() % (H - 1); x2 = rand() % (H - 1);
		y1 = rand() % (W - 1); y2 = rand() % (W - 1);
		lineDDA(x1, y1, x2, y2, DOT);
	}

	fp = fopen("testDDA.ppm", "wb");
	fprintf(fp, "P6\n");
	fprintf(fp, "%d %d\n", W, H);
	fprintf(fp, "255\n");

	fwrite(outImg, sizeof(char), H*W*3, fp);
	fclose(fp);

}
