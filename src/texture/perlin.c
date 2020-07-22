#include "mlx.h"
#include <stdlib.h>
#include <math.h>
#define W  600
#define H  400
#define GRAD_MAX 100

int escape()
{
	exit(0);
	return (0);
}

double ft_lerp(double v0, double v1, double t)
{
  	return ((1.0 - t) * v0 + t * v1);
}

void  delete_grad(unsigned char  ***g)
{
	int i;
	int j;

	j = 0;
	while (j < GRAD_MAX)
	{
		i = 0;
		while (i < GRAD_MAX)
		{
			free(g[j][i]);
			i++;
		}
		free(g[j]);
		j++;
	}
	free(g);
}

unsigned char  ***create_gradient_vectors()
{
	unsigned char	***g;
	int				i;
	int				j;

	j = 0;
	g = malloc(sizeof(char**)*GRAD_MAX);
	while (j < GRAD_MAX)
	{
		g[j] = malloc(sizeof(char*) *GRAD_MAX);
		i = 0;
		while(i < GRAD_MAX)
		{
			g[j][i] = malloc(sizeof(char) * 2);
			g[j][i][0] = rand() % 255;
			g[j][i][1] = rand() % 255;
			i++;
		}
		j++;
	}
	return (g);
}

double dotgrad(int ix, int iy, double x, double y, unsigned char ***g)
{
	double dx;
	double dy;
	double xvalue;
	double yvalue;

	dx = x - (double)ix;
    dy = y - (double)iy;
	ix = ix % GRAD_MAX;
	iy = iy % GRAD_MAX;
	xvalue = (float)g[iy][ix][0] / 122.5 - 1;
	yvalue = (float)g[iy][ix][1] / 122.5 - 1;
	
	return (dx * xvalue + dy * yvalue);
}


double	perlin_noise(double x, double y, unsigned char ***g)
{

	int x0 = (int)x;
	int y0 = (int)y;
	int x1 = x0 + 1;
	int y1 = y0 + 1;
	double sx = x - (float)x0;
	double sy = y - (float)y0;
	double n0, n1, ix0, ix1, value;

	n0 = dotgrad(x0, y0, x, y, g);
	n1 = dotgrad(x1, y0, x, y, g);
	ix0 = ft_lerp(n0, n1, sx);
	n0 = dotgrad(x0, y1, x, y, g);
	n1 = dotgrad(x1, y1, x, y, g);
	ix1 = ft_lerp(n0, n1, sx);
	value = ft_lerp(ix0, ix1, sy);
	return (value / 2 + 0.5);
}

double octave_perlin(double x, double y, int oct, double pers, unsigned char ***g)
{
	double total = 0;
	double freq = 100;
	double amplitude = 1;
	double maxvalue = 0;

	for (int i = 0; i < oct; i++)
	{
		total += perlin_noise(x * freq, y * freq, g) * amplitude;
		maxvalue += amplitude;
		amplitude *= pers;
		freq *= 2;
	}
	return (total / maxvalue);
}

double ft_map(double v, double s1, double e1, double s2, double e2)
{
	double r;
	double l1;
	double l2;
	double offset;

	l1 = e1 - s1;
	l2 = e2 - s2;
	offset = 0 - s1;
	r = (v + offset) / l1 * l2;
	return (r);
}
/*
typedef struct s_data
{
	void *mlx_ptr;
	void *mlx_win;
}				t_data;

int main()
{
	t_data data;

	data.mlx_ptr = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx_ptr, W, H, "hello");
	unsigned char ***g = create_gradient_vectors(); 
	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < W; j++)
		{
			float x = j / (float)(W);
			float y = i / (float)(H);
			double p = octave_perlin(x, y,1, 1, g);
			int col = p*255;
			int hex = (((col << 8 ) + col) << 8) + col;
			mlx_pixel_put(data.mlx_ptr, data.mlx_win, j, i, hex);
		}
	}
	delete_grad(g);
	mlx_hook(data.mlx_win,17, 0, escape, NULL);
	mlx_loop(data.mlx_ptr);
	return (0);
}
*/
