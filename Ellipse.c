#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define H 480
#define W 640
#define ROUND(x) (int)(x+0.5)

unsigned char outImg[H][W][3];
int RGB[3] = { 0, 0, 0 };

void setPixel(int x, int y, int* rgb) {
	if (x >= 0 && x < H && y >= 0 && y < W) {
		outImg[x][y][0] = rgb[0];
		outImg[x][y][1] = rgb[1];
		outImg[x][y][2] = rgb[2];
	}
}

void rotation(int Cx, int Cy, int x, int y, int* rgb, int a) {
	int x2 = (x - Cx)*cos(a) - (y - Cy)*sin(a); // 회전
	int y2 = (x - Cx)*sin(a) + (y - Cy)*cos(a);
	
	x2 += Cx; // 중심이동
	y2 += Cy;

	setPixel(x2, y2, rgb); //marking
}

void ellipsePlot(int Cx, int Cy, int x, int y, int* rgb, int a)
{
	rotation(Cx, Cy, Cx + x, Cy + y, rgb, a);
	rotation(Cx, Cy, Cx - x, Cy + y, rgb, a);
	rotation(Cx, Cy, Cx + x, Cy - y, rgb, a);
	rotation(Cx, Cy, Cx - x, Cy - y, rgb, a);
}

void ellipseMidpoint(int xCenter, int yCenter, int Rx, int Ry, int a)
{
	int Rx2 = Rx * Rx, Ry2 = Ry * Ry, twoRx2 = 2 * Rx2, twoRy2 = 2 * Ry2;
	int p, x = 0, y = Ry, px = 0, py = twoRx2 * y;

	for (int i = 0; i < 3; i++) {
		RGB[0] = rand() % 256;
		RGB[1] = rand() % 256;
		RGB[2] = rand() % 256;
	}
	//printf("R: %d G: %d B: %d\n\n", RGB[0], RGB[1], RGB[2]);

	ellipsePlot(xCenter, yCenter, x, y, RGB, a);//start pixel marking..

	//Region 1
	p = ROUND(Ry2 - (Rx2*Ry) + (0.25*Rx2));
	while (px < py) {
		x++;
		px += twoRy2;
		if (p < 0) p += Ry2 + px;
		else { y--; py -= twoRx2; p += Ry2 + px - py; }

		ellipsePlot(xCenter, yCenter, x, y, RGB, a);//marking..
	}

	//Region 2
	p = ROUND(Ry2*(x + 0.5)*(x + 0.5) + Rx2 * (y - 1)*(y - 1) - Rx2 * Ry2);
	while (y > 0) {
		y--;
		py -= twoRx2;
		if (p > 0) p += Rx2 - py;
		else { x++; px += twoRy2; p += Rx2 - py + px; }

		ellipsePlot(xCenter, yCenter, x, y, RGB, a);//marking..
	}
}

int main(void) {

	FILE *fp;

	int cx, cy, rx, ry;
	srand((unsigned)time(NULL));

	for (int i = 0; i < 5; i++) {
		rx = (rand() % 210) + 1;
		ry = (rand() % 210) + 1;
		cx = rand() % (H - 1);
		cy = rand() % (W - 1);
		int a = rand() % 361;
		//printf("x반지름 : %d y반지름 : %d\n x중심 : %d y중심 : %d  각도 : %d\n", rx, ry, cx, cy, a);
		ellipseMidpoint(cx, cy, rx, ry, a);
	}

	fp = fopen("testEllipse.ppm", "wb");
	fprintf(fp, "P6\n");
	fprintf(fp, "%d %d\n", W, H);
	fprintf(fp, "255\n");
	fwrite(outImg, sizeof(char), H*W * 3, fp);
	fclose(fp);
}