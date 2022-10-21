/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceiling_textures.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:54:08 by faventur          #+#    #+#             */
/*   Updated: 2022/10/21 10:42:39 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	draw_floor(t_data *data, int x)
{
	t_ray	ray;
	size_t	height;
	int		half_height;

	ray = data->ray_data;
	height = HEIGHT;
	half_height = height / 2;
	draw_line(data->img.img, (t_vector2){x, half_height + ray.line_height / 2},
		(t_vector2){x, height}, rgb_to_hex(data->map->floor_color));
}

void	draw_ceiling(t_data *data, int x)
{
	t_ray	ray;
	size_t	height;
	int		half_height;

	ray = data->ray_data;
	height = HEIGHT;
	half_height = height / 2;
	draw_line(data->img.img, (t_vector2){x, 0},
		(t_vector2){x, half_height - ray.line_height / 2},
		rgb_to_hex(data->map->ceiling_color));
}

uint32_t	get_shading(uint32_t color, t_ray ray)
{
	t_color	table;
	double	multiplier;
	double	distance;
	double	intensity;

	distance = ray.wall_distance;
	if (distance <= 1.00)
		return (color);
	table = hex_to_rgb(color);
	intensity = 1 - ((distance / 100) * 2);
	multiplier = 1 + (distance / intensity);
	table.a = table.a * (intensity / distance * multiplier);
	return (rgb_to_hex(table));
}

int	choose_wall_texture(t_data *data)
{
	t_ray	*ray;

	ray = &data->ray_data;
	if (ray->dir.x == 0 && ray->dir.y == -1)
		return (0);
	else if (ray->dir.x == 0 && ray->dir.y == 1)
		return (1);
	else if (ray->dir.x == -1 && ray->dir.y == 0)
		return (2);
	else if (ray->dir.x == 1 && ray->dir.y == 0)
		return (3);
	return (0);
}

void	draw_walls(t_data *data, int x)
{
	t_ray		ray;
	size_t		width;
	size_t		height;
	int			y;
	uint32_t	color;

	ray = data->ray_data;
	y = ray.draw_start;
	ray.text_select = choose_wall_texture(data);
	width = data->textures[ray.text_select].img->width;
	height = data->textures[ray.text_select].img->height;
	while (y < ray.draw_end)
	{
		ray.tex.y = (int)ray.tex_pos & (height - 1);
		ray.tex_pos += ray.step;
		color = ray.tex_buf[((ray.tex.y * width) + ray.tex.x)];
		color = get_shading(color, ray);
		mlx_put_pixel(data->img.img, x, y, color);
		++y;
	}
}
