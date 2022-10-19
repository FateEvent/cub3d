/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:39:31 by faventur          #+#    #+#             */
/*   Updated: 2022/10/19 14:27:26 by faventur         ###   ########.fr       */
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

void	draw_floor(t_data *data, int x)
{
	t_ray	ray;
	size_t	height;
	int		half_height;
	
	ray = data->ray_data;
	height = HEIGHT;
	half_height = height / 2;
	draw_line(data->img.img, (t_vector2){x, half_height + ray.lineheight / 2}, (t_vector2){x, height}, rgb_to_hex(data->map->floor_color));
}

void	draw_ceiling(t_data *data, int x)
{
	t_ray	ray;
	size_t	height;
	int		half_height;
	
	ray = data->ray_data;
	height = HEIGHT;
	half_height = height / 2;
	draw_line(data->img.img, (t_vector2){x, 0}, (t_vector2){x, half_height - ray.lineheight / 2}, rgb_to_hex(data->map->ceiling_color));
}

uint32_t	get_shading(uint32_t color, t_ray ray)
{
	t_color	table;
	double	multiplier;
	double	distance;
	double	intensity;

	distance = ray.walldistance;
	if (distance <= 1.00)
		return (color);
	table = hex_to_rgb(color);
	intensity = 1 - ((distance / 100) * 2);
	multiplier = 1 + (distance / intensity);
	table.a = table.a * (intensity / distance * multiplier);
	return (rgb_to_hex(table));
}

void	ft_print_texture(t_data *data, int x)
{
	t_ray		ray;
	size_t		width;
	size_t		height;
	int			y;
	uint32_t	color;
	uint32_t	*texture;

	ray = data->ray_data;
	y = ray.drawstart;
	width = data->textures[ray.text_select].img->width;
	height = data->textures[ray.text_select].img->height;
	texture = ft_from_uchar_to_hex_arr(data->textures[ray.text_select].img->pixels, width, height);
	while (y < ray.drawend)
	{
		ray.tex.y = (int)ray.texpos & (height - 1);
		ray.texpos += ray.step;
		color = texture[((ray.tex.y * width) + ray.tex.x)];
		color = get_shading(color, ray);
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
	if ((int)start.y >= HEIGHT)
		return ;
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

	if (start.x < 0 || start.y < 0)
		return ;
	if (finish.x < 0 || finish.y < 0)
		return ;
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
