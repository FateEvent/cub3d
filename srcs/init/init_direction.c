/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_direction.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 12:33:59 by albaur            #+#    #+#             */
/*   Updated: 2022/11/01 12:34:09 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

static void	init_direction_child(t_data *data, t_ray *ray)
{
	if (data->map->dir == 'E')
	{
		data->player.start_direction = 0;
		ray->dir.x = 1;
		ray->dir.y = 0;
		ray->plane.x = 0;
		ray->plane.y = (double)data->player.fov / 100;
	}
	if (data->map->dir == 'W')
	{
		data->player.start_direction = 2;
		ray->dir.x = -1;
		ray->dir.y = 0;
		ray->plane.x = 0;
		ray->plane.y = -(double)data->player.fov / 100;
	}
}

void	init_direction(t_data *data)
{
	t_ray	*ray;

	ray = &data->ray_data;
	if (data->map->dir == 'N')
	{
		data->player.start_direction = 3;
		ray->dir.x = 0;
		ray->dir.y = -1;
		ray->plane.x = (double)data->player.fov / 100;
		ray->plane.y = 0;
	}
	if (data->map->dir == 'S')
	{
		data->player.start_direction = 1;
		ray->dir.x = 0;
		ray->dir.y = 1;
		ray->plane.x = -(double)data->player.fov / 100;
		ray->plane.y = 0;
	}
	init_direction_child(data, ray);
}
