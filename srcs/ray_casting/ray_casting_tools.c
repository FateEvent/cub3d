/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:24:46 by faventur          #+#    #+#             */
/*   Updated: 2022/11/08 13:51:21 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

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
	init_sprites_pos(data, ray);
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
