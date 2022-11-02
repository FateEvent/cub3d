/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:24:46 by faventur          #+#    #+#             */
/*   Updated: 2022/11/02 13:57:25 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

static void	sprite_casting_init_pt2(t_ray *ray, t_s_caster *sprite)
{
	size_t	i;

	i = 0;
	while (i < NUMSPRITES)
	{
		sprite->sprite_order[i] = i;
		sprite->sprite_dist[i] = ((ray->pos.x - sprite->sprites[i].x)
				* (ray->pos.x - sprite->sprites[i].x)
				+ (ray->pos.y - sprite->sprites[i].y)
				* (ray->pos.y - sprite->sprites[i].y));
		i++;
	}
	sort_sprites(sprite->sprite_order, sprite->sprite_dist, NUMSPRITES);
}

void	sprite_casting_init(t_ray *ray)
{
	t_s_caster	*sprite;

	sprite = &ray->sprite;
	sprite->sprites = malloc(sizeof(t_sprite) * NUMSPRITES);
	sprite->sprite_order = malloc(sizeof(int) * NUMSPRITES);
	sprite->sprite_dist = malloc(sizeof(double) * NUMSPRITES);
	sprite->z_buffer = malloc(sizeof(double) * ray->resolution.x);
	if (!sprite->sprites || !sprite->z_buffer || !sprite->sprite_order
		|| !sprite->sprite_dist)
		return ;
	sprite->sprites[0].x = 3;
	sprite->sprites[0].y = 3;
	sprite->sprites[0].texture = 6;
	sprite_casting_init_pt2(ray, sprite);
}

void	ray_init(t_data *data, t_ray *ray, t_var var)
{
	ray_data_init(ray, var.x);
	rayside_calculator(ray);
	ray_launcher(ray);
	wall_distance_calculator(ray);
	wall_line_calculator(ray);
	texture_x_pos_calculator(data, ray);
	texture_y_pos_calculator(data, ray);
}

void	ray_casting(t_data *data)
{
	t_ray	*ray;
	t_var	var;

	ft_bzero(&var, sizeof(var));
	ray = &data->ray_data;
	ray->map = data->map;
	sprite_casting_init(ray);
	if (data->map->mode == 1)
		floor_casting(data, ray);
	while (var.x < ray->resolution.x)
	{
		ray_init(data, ray, var);
		if (data->map->mode == -1)
		{
			draw_ceiling(data, var.x);
			draw_floor(data, var.x);
		}
		draw_walls(data, var.x);
		ray->sprite.z_buffer[var.x] = ray->wall_distance;
		++var.x;
	}
	sprite_caster(data, ray, &var);
}
