#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define H 480
#define W 640

unsigned char outImg[H][W][3];
int RGB[3] = { 0, 0, 0 };

void setPixel(int x, int y, int* rgb) {
	if ((x >= 0 && x < H) && (y >= 0 && y < W)) {
		outImg[x][y][0] = rgb[0];
		outImg[x][y][1] = rgb[1];
		outImg[x][y][2] = rgb[2];
	}
}

void circlePlot(int Cx, int Cy, int x, int y, int* rgb)
{
	setPixel(Cx + x, Cy + y, rgb);//marking function according to the output device
	setPixel(Cx - x, Cy + y, rgb);
	setPixel(Cx + x, Cy - y, rgb);
	setPixel(Cx - x, Cy - y, rgb);
	setPixel(Cx + y, Cy + x, rgb);
	setPixel(Cx - y, Cy + x, rgb);
	setPixel(Cx + y, Cy - x, rgb);
	setPixel(Cx - y, Cy - x, rgb);
}

void circleMidpoint(int xCenter, int yCenter, int radius)
{
	int x = 0, y = radius, p = 1 - radius;

	for (int i = 0; i < 3; i++) {
		RGB[0] = rand() % 256;
		RGB[1] = rand() % 256;
		RGB[2] = rand() % 256;
	}

	circlePlot(xCenter, yCenter, x, y, RGB);//start pixel marking..

	while (x <= y) {
		x++;
		if (p < 0) p += 2 * x + 1;
		else { y--; p += 2 * (x - y) + 1; }

		circlePlot(xCenter, yCenter, x, y, RGB);//marking..
	}
}

int main(void) {

	FILE *fp;

	int x, y, r;
	srand((unsigned)time(NULL));

	for (int i = 0; i < 5; i++) {
		r = (rand() % 236) + 5;
		x = rand() % (H - 1);
		y = rand() % (W - 1);
		//printf("%d %d %d\n", r, x, y);

		circleMidpoint(x, y, r);
	}

	fp = fopen("testCircle.ppm", "wb");
	fprintf(fp, "P6\n");
	fprintf(fp, "%d %d\n", W, H);
	fprintf(fp, "255\n");
	fwrite(outImg, sizeof(char), H*W * 3, fp);
	fclose(fp);
}