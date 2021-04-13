#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define H 480
#define W 640

unsigned char outImg[H][W][3];
enum { SOLID, DASH, DOT };
int LT[3][8] = { {1,1,1,1,1,1,1,1},{1,1,1,1,0,0,0,0},{1,1,0,0,1,1,0,0} };

void lineBres(int x1, int y1, int x2, int y2, int lt)
{
	int dx = abs(x2 - x1), dy = abs(y2 - y1);
	int p, twoDx, twoDy, twoDyDx, twoDxDy;
	int x, y, yEnd, xEnd, IorD;

	if (dx > dy) {
		p = 2 * dy - dx; twoDy = 2 * dy; twoDyDx = 2 * (dy - dx);

		if (x1 > x2) { x = x2; y = y2; xEnd = x1; if (y1 - y2 > 0)IorD = 1; else IorD = -1; }
		else { x = x1; y = y1; xEnd = x2; if (y2 - y1 > 0)IorD = 1; else IorD = -1; }

		int r = rand() % 256;
		int g = rand() % 256;
		int b = rand() % 256;

		outImg[x][y][0] = r; outImg[x][y][1] = g; outImg[x][y][2] = b;// start point marking with a user-defined color(r,g,b) 

		while (x < xEnd) {
			x++;
			if (p < 0) p += twoDy;
			else { y += IorD; p += twoDyDx; }
			if (LT[lt][x % 8]) {
				outImg[x][y][0] = r; outImg[x][y][1] = g; outImg[x][y][2] = b;//marking
			}
			
		}// end of while
	}// end of if
	else {
		p = 2 * dx - dy; twoDx = 2 * dx; twoDxDy = 2 * (dx - dy);

		if (y1 > y2) { y = y2; x = x2; yEnd = y1; if (x1 - x2 > 0)IorD = 1; else IorD = -1; }
		else { y = y1; x = x1; yEnd = y2; if (x2 - x1 > 0)IorD = 1; else IorD = -1; }

		int r = rand() % 256;
		int g = rand() % 256;
		int b = rand() % 256;

		outImg[x][y][0] = r; outImg[x][y][1] = g; outImg[x][y][2] = b;// start point marking with a user-defined color(r,g,b) 

		while (y < yEnd) {
			y++;
			if (p < 0) p += twoDx;
			else { x += IorD; p += twoDxDy; }
			if (LT[lt][y % 8]) {
				outImg[x][y][0] = r; outImg[x][y][1] = g; outImg[x][y][2] = b;//marking
			}
		}// end of while

	}// end of else
}

int main(void) {
	FILE *fp;
	srand((unsigned)time(NULL));

	int x1, y1, x2, y2;
	
	for (int i = 0; i < 3; i++) {
		x1 = rand() % (H - 1); x2 = rand() % (H - 1);
		y1 = rand() % (W - 1); y2 = rand() % (W - 1);
		//printf("%d %d %d %d\n", x1,y1,x2, y2);
		lineBres(x1, y1, x2, y2, SOLID);
	}

	for (int i = 0; i < 3; i++) {
		x1 = rand() % (H - 1); x2 = rand() % (H - 1);
		y1 = rand() % (W - 1); y2 = rand() % (W - 1);
		//printf("%d %d %d %d\n", x1, y1, x2, y2);
		lineBres(x1, y1, x2, y2, DASH);
	}

	for (int i = 0; i < 3; i++) {
		x1 = rand() % (H - 1); x2 = rand() % (H - 1);
		y1 = rand() % (W - 1); y2 = rand() % (W - 1);
		//printf("%d %d %d %d\n", x1, y1, x2, y2);
		lineBres(x1, y1, x2, y2, DOT);
	}

	fp = fopen("testBres.ppm", "wb");
	fprintf(fp, "P6\n");
	fprintf(fp, "%d %d\n", W, H);
	fprintf(fp, "255\n");

	fwrite(outImg, sizeof(char), H*W * 3, fp);
	fclose(fp);
}
