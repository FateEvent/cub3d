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

void	mlx_draw_line(mlx_image_t *img, int x0, int y0,
			int x1, int y1, uint32_t color)
{
  uint32_t	dx =  abs (x1 - x0), sx = x0 < x1 ? 1 : -1;
  uint32_t	dy = -abs (y1 - y0), sy = y0 < y1 ? 1 : -1; 
  uint32_t	err = dx + dy, e2; /* error value e_xy */
 
  for (;;){  /* loop */
    mlx_put_pixel(img, x0, y0, color);
    if (x0 == x1 && y0 == y1) break;
    e2 = 2 * err;
    if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
    if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
  }
}
