/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceiling_textures.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:54:08 by faventur          #+#    #+#             */
/*   Updated: 2022/11/09 11:50:43 by albaur           ###   ########.fr       */
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
	draw_line(data->screen.display.img, (t_vec2){x,
		half_height + ray.line_height / 2},
		(t_vec2){x, height}, rgb_to_hex(data->map->floor_color));
}

void	draw_ceiling(t_data *data, int x)
{
	t_ray	ray;
	size_t	height;
	int		half_height;

	ray = data->ray_data;
	height = HEIGHT;
	half_height = height / 2;
	draw_line(data->screen.display.img, (t_vec2){x, 0},
		(t_vec2){x, half_height - ray.line_height / 2},
		rgb_to_hex(data->map->ceiling_color));
}

uint32_t	get_shading(t_data *data, uint32_t color, double distance)
{
	t_color	table;

	if (distance <= 1.00)
		return (color);
	if (distance > 25.00)
		return (0x000000FF);
	else if (distance == data->shading.distance)
	{
		table = hex_to_rgb(color);
		table.r = table.r * data->shading.multiplier;
		table.g = table.g * data->shading.multiplier;
		table.b = table.b * data->shading.multiplier;
		return (rgb_to_hex(table));
	}		
	else
	{
		data->shading.multiplier = 0.7 / distance * 1.5;
		data->shading.distance = distance;
		table = hex_to_rgb(color);
		table.r = table.r * data->shading.multiplier;
		table.g = table.g * data->shading.multiplier;
		table.b = table.b * data->shading.multiplier;
		return (rgb_to_hex(table));
	}
}

void	draw_walls(t_data *data, int x)
{
	t_ray	*ray;
	t_var	var;

	ft_bzero(&var, sizeof(var));
	ray = &data->ray_data;
	var.y = ray->draw_start;
	choose_wall_texture(ray);
	var.width = data->textures[ray->text_select].img->width;
	var.height = data->textures[ray->text_select].img->height;
	var.pixels = data->textures[ray->text_select].img->pixels;
	if (ray->map->map[ray->map_pos.y][ray->map_pos.x] == '3')
	{
		ray->text_select = 10;
	}
	while (var.y <= ray->draw_end)
	{
		ray->tex.y = (int)ray->tex_pos & (var.height - 1);
		ray->tex_pos += ray->step;
		var.color = ray->tex_buf[ray->text_select][((ray->tex.y * var.width)
				+ ray->tex.x)];
		var.color = get_shading(data, var.color, ray->wall_distance);
		mlx_put_pixel(data->screen.display.img, x, var.y, var.color);
		++var.y;
	}
}
