#include "mlx.h"
#include "image_save_load.h"
#include <stdlib.h>
#include <stdio.h>

int exit_program()
{
	exit(0);
	return (0);
}

# define W 400
# define H 300

int main(int argc, char **argv)
{
	void *ptr;
	void *win;
	t_image_data *image;

	if (argc < 2)
		return (0);
	ptr = mlx_init();
	win = mlx_new_window(ptr, W, H, "window");
	image = img_load_ppm(argv[1]);
	if (!image)
		ft_putendl("null image");
	float sx = image->width / (float)W;
	float sy = image->height / (float)H;
	for (int j = 0; j < H; j++)
	{
		for(int i = 0; i < W; i++)
		{	
			int p = (int)(sy *j ) * image->width + i * sx;
			int r = image->pixels[p].r;
			int g = image->pixels[p].g;
			int b = image->pixels[p].b;
			int col = (((r << 8) | g) << 8) | b;

			mlx_pixel_put(ptr, win, i, j ,col);
		}
	}
	image_data_delete(&image);	
	mlx_hook(win, 17, 0, exit_program, NULL);
	mlx_loop(ptr);
	return (0);
}
