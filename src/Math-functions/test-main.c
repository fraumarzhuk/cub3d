#include "xMath.h"
#include <stdio.h>

int	main(void)
{
	double x[3] = {1, 2, 3};
	double y[3] = {4, 5, 6};
	double dir[2] = {0, 0};
	double pos[3];
	printf("\e[1;32mStarting Tests...\n");
	printf("\e[1;33mDistance Tests:\n");
	printf("\e[1;34m 2D: 4.24264-%f\n", get_distance2(x, y));
	printf("\e[1;34m 3D: 5.19615-%f\n", get_distance3(x, y));
	printf("\e[1;33mPosition Tests:\n");
	get_new_pos2(x, dir, 1, pos);
	printf("\e[1;34m Moving 1 Step in 0: %f, %f\n", pos[0], pos[1]);
	get_new_pos3(x, dir, 1, pos);
	printf("\e[1;34m Moving 1 Step in 0: %f, %f, %f\n", pos[0], pos[1], pos[2]);
	dir[0] = 90;
	get_new_pos2(x, dir, 1, pos);
	printf("\e[1;34m Moving 1 Step in 90: %f, %f\n", pos[0], pos[1]);
	get_new_pos3(x, dir, 1, pos);
	printf("\e[1;34m Moving 1 Step in 90: %f, %f, %f\n", pos[0], pos[1],
		pos[2]);
	dir[0] = 180;
	get_new_pos2(x, dir, 1, pos);
	printf("\e[1;34m Moving 1 Step in 180: %f, %f\n", pos[0], pos[1]);
	get_new_pos3(x, dir, 1, pos);
	printf("\e[1;34m Moving 1 Step in 180: %f, %f, %f\n", pos[0], pos[1],
		pos[2]);
	dir[0] = 270;
	get_new_pos2(x, dir, 1, pos);
	printf("\e[1;34m Moving 1 Step in 270: %f, %f\n", pos[0], pos[1]);
	get_new_pos3(x, dir, 1, pos);
	printf("\e[1;34m Moving 1 Step in 270: %f, %f, %f\n", pos[0], pos[1],
		pos[2]);
	dir[0] = 22.5;
	get_new_pos2(x, dir, 1, pos);
	printf("\e[1;34m Moving 1 Step in 45: %f, %f\n", pos[0], pos[1]);
	get_new_pos3(x, dir, 1, pos);
	printf("\e[1;34m Moving 1 Step in 45: %f, %f, %f\n", pos[0], pos[1],
		pos[2]);
	printf("\e[1;33mWall Tests:\n");
	x[0] = 0.5;
	x[1] = 0.3;
	x[2] = 2.23;
	dir[0] = 0;
	to_border(x, dir, pos);
	printf("\e[1;34m Moving in 0: %f, %f, %f\n", pos[0], pos[1], pos[2]);
	dir[0] = 90;
	to_border(x, dir, pos);
	printf("\e[1;34m Moving in 90: %f, %f, %f\n", pos[0], pos[1], pos[2]);
	dir[0] = 180;
	to_border(x, dir, pos);
	printf("\e[1;34m Moving in 180: %f, %f, %f\n", pos[0], pos[1], pos[2]);
	dir[0] = 270;
	to_border(x, dir, pos);
	printf("\e[1;34m Moving in 270: %f, %f, %f\n", pos[0], pos[1], pos[2]);
	dir[0] = 45;
	to_border(x, dir, pos);
	printf("\e[1;34m Moving in 45: %f, %f, %f\n", pos[0], pos[1], pos[2]);
	return (0);
}