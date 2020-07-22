#include "image_save_load.h"

t_image_data *image_data_init(void)
{
	t_image_data *img;

	img = (t_image_data*)malloc(sizeof(t_image_data));
	if (!img)
		return (NULL);
	img->pixels = NULL;
	img->file_path = NULL;
	img->color_range = 0;
	img->width = 0;
	img->height = 0;
	return (img);
}

void	image_data_delete(t_image_data **img)
{
	if (!img || *img)
		return ;
	free(img[0]->file_path);
	free(img[0]->pixels);
	free(*img);
}

t_rgba8		rgba8_init(void)
{
	t_rgba8 color;

	color.r = 0;
	color.g = 0;
	color.b = 0;
	color.a = 255;
	return (color);
}
