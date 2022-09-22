#include "mlx_utils.h"

void	ft_put_background(t_program *data, char *path)
{
	t_image		bg;
	uint32_t	i;
	uint32_t	j;
	t_vector	size;

	size = calculate_window_size(data->map);
	bg.texture = mlx_load_xpm42(path);
	bg.img = mlx_texture_to_image(data->mlx, &bg.texture->texture);
	i = 0;
	while (i * bg.texture->texture.height < size.y)
	{
		j = 0;
		while (j * bg.texture->texture.width < size.x)
		{
			mlx_image_to_window(data->mlx, bg.img,
				j * (63 - 1), i * (63 - 1));
			j++;
		}
		i++;
	}
}

void	mlx_draw_square(mlx_image_t *img, uint32_t width, uint32_t height,
			uint32_t color)
{
	uint32_t	h;
	uint32_t	w;

	h = -1;
	while (++h < height)
	{
		w = -1;
		while (++w < width)
		{
			mlx_put_pixel(img, w, h, color);
		}
	}
}
