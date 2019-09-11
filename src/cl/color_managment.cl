#include "kernel.h"

double3	trim_color(double3 color)
{
	if (color[0] > (double)255)
		color[0] = (double)255;
	if (color[1] > (double)255)
		color[1] = (double)255;
	if (color[2] > (double)255)
		color[2] = (double)255;

	if (color[0] < (double)0)
		color[0] = (double)0;
	if (color[1] < (double)0)
		color[1] = (double)0;
	if (color[2] < (double)0)
		color[2] = (double)0;
	return (color);
}

uint	color_to_canvas(double3 color)
{
	return (((uint)color[0] << 16) + ((uint)color[1] << 8) + (uint)color[2]);
}

double3		uint_to_double3(uint a)
{
	double3	d;

	d[0] = (a >> 16) & 0xff;
	d[1] = (a >> 8) & 0xff;
	d[2] = a & 0xff;
	return (d);
}
