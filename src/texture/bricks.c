#include <stdlib.h>
#include <stdio.h>
#include "mlx.h"
#include <math.h>
#define W 400
#define H 400


typedef struct s_data
{
	void *ptr;
	void *win;
}				t_data;

int escape()
{
	exit(0);
	return (0);
}

static double dmodulo(double d, double m)
{
	double mod;

	mod = (d) - (floor((d) / (double)m) * m);
	return (mod);
}

double brick_texture(double u, double v)
{
	int rows = 10;
	double col1 = 0.6;
	double col2 = 0;
	double line = 0.01;


	double lines = rows - 1;
	double rs = ((1.0 - lines * line)) / (double)rows;
	v += line;
	double mod = dmodulo(v, rs + line);
	if (fabs(mod) < line)
		return (col2);
	else
	{
		if (dmodulo(v, 2*(rs+line)) < rs+line)
			u += 0.3;
		rs = ((1.0 - lines * 2 * line))/(rows/4);
		u += line;
		mod = dmodulo(u, rs + line);
		if(fabs(mod) < line)
			return(col2);
		return (col1);
	}
}
/*
int		main()
{
	t_data data;

	data.ptr = mlx_init();
	data.win = mlx_new_window(data.ptr, W, H, "Brick");
	for(int j = 0; j < H; j++)
	{
		for(int i = 0; i < W; i++)
		{
			
			int col = bricks((double)i/(double)W, (double)j/(double)H) * 255;
			int hex = (((col << 8) + col) << 8) + col;
			mlx_pixel_put(data.ptr, data.win, i, j, hex);
		}
	}
	mlx_hook(data.win, 17, 0, escape, NULL);
	mlx_loop(data.ptr);
	return (0);
}*/
