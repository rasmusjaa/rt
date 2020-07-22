#ifndef IMAGE_SAVE_LOAD_H
#define IMAGE_SAVE_LOAD_H

# include <stdlib.h>
# include "../../../libft/includes/libft.h"
# include "../../../libft/includes/ft_get_next_line.h"

typedef struct	s_rgba8
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
}				t_rgba8;

typedef struct s_image_data
{
	t_rgba8 *pixels;
	int width;
	int height;
	int color_range;
	char *file_path;
}				t_image_data;

void	img_to_ppm(unsigned char *img, char *file_name, int width, int height);
t_image_data	*img_load_ppm(char *filename);

t_image_data *image_data_init(void);
void	image_data_delete(t_image_data **img);
t_rgba8		rgba8_init(void);

#endif
