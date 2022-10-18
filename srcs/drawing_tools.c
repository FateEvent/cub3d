/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:39:31 by faventur          #+#    #+#             */
/*   Updated: 2022/10/18 15:30:53 by albaur           ###   ########.fr       */
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

void	ft_print_texture(t_data *data, int x)
{
	t_ray		ray;
	size_t		width;
	size_t		height;
	int			y;
	uint32_t	color;
	uint32_t	*texture;

	y = ray.drawstart;
	ray = data->ray_data;
	width = data->textures[ray.text_select].img->width;
	height = data->textures[ray.text_select].img->height;
	texture = ft_from_uchar_to_hex_arr(data->textures[ray.text_select].img->pixels, width, height);
	while (y < ray.drawend)
	{
		ray.texy = (int)ray.texpos & (height - 1);
		ray.texpos += ray.step;
		color = texture[((ray.texy * width) + ray.texx)];
		mlx_put_pixel(data->img.img, x, y, color);
		++y;
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
