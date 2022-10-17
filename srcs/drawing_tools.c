/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:39:31 by faventur          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/10/17 17:17:15 by albaur           ###   ########.fr       */
=======
/*   Updated: 2022/10/17 14:22:32 by faventur         ###   ########.fr       */
>>>>>>> de682cfe3fa98614c7571f89bf9a4f16c783481b
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

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

int get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

/*
void	ft_print_texture(t_data *data, int x)
{
	while (data->ray_data.drawstart <= data->ray_data.drawend)
	{
		data->ray_data.texy = (int)data->ray_data.texpos & (data->textures[data->ray_data.text_select].img->height - 1);
		data->ray_data.texpos += data->ray_data.step;
		ft_my_mlx_pixel_put(data, x, data->ray_data.drawstart,
			img_add[data->textures[data->ray_data.text_select].img->width * data->ray_data.texy + data->ray_data.texx]);
		data->ray_data.drawstart++;
	}
}
*/

void	ft_my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	static int	octet;

	if (octet == 0)
		octet = BPP / 8;
	*(unsigned int *)(data->img.img->pixels
			+ (y * data->line_length + x * 4)) = color;
}

void	ft_print_texture(t_data *data, int x, int x2)
{
	t_ray		ray;
	int			text_select;
	int			img_width;
	uint8_t		*pixels;
	uint32_t	**hex;

	ray = data->ray_data;
	text_select = ray.text_select;
	img_width = data->textures[text_select].img->width;
	pixels = data->textures[text_select].img->pixels;
	hex = ft_from_uchar_to_hex_buf(pixels, img_width, data->textures[text_select].img->height);
	while (ray.drawstart <= ray.drawend)
	{
		ray.texy = (int)ray.texpos & (data->textures[text_select].img->height - 1);
		ray.texpos += ray.step;
		uint32_t color = hex[img_width * ray.texy + x2];
		//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
		if (ray.side == 1) color = (color >> 1) & 8355711;
		mlx_put_pixel(data->img.img, x, ray.drawstart, color);
		//printf("%i\n", x2);
//		ft_my_mlx_pixel_put(data, x, ray.drawstart, color);
		ray.drawstart++;
	}
}

static void	draw_line_pt2(mlx_image_t *img, t_vector2 start, t_vector2 finish,
		uint32_t color)
{
	float	w;
	float	p;
	int		y;
	float	x;

	if (start.y > finish.y)
		ft_vec2_swap(&start, &finish);
	w = (finish.x - start.x) / (finish.y - start.y);
	p = start.x - w * start.y;
	y = (int)start.y;
	while (y < (int)finish.y)
	{
		x = w * (float)y + p;
		mlx_put_pixel(img, (int)x, y, color);
		y++;
	}
}

void	draw_line(mlx_image_t *img, t_vector2 start, t_vector2 finish,
		uint32_t color)
{
	float	m;
	float	b;
	int		x;
	float	y;

	if (finish.x != start.x)
		m = (finish.y - start.y) / (finish.x - start.x);
	if (finish.x != start.x && fabsf(m) <= 1)
	{
		if (start.x > finish.x)
			ft_vec2_swap(&start, &finish);
		b = start.y - m * start.x;
		x = (int)start.x;
		while (x < (int)finish.x)
		{
			y = m * (float)x + b;
			mlx_put_pixel(img, x, (int)y, color);
			x++;
		}
	}
	else
		draw_line_pt2(img, start, finish, color);
}

void	draw_vertical_line(mlx_image_t *img, t_vector draw_start,
			uint32_t draw_end, uint32_t color)
{
	while (draw_start.y < draw_end)
	{
		mlx_put_pixel(img, draw_start.x, draw_start.y, color);
		draw_start.y++;
	}
}
