/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:08:44 by albaur            #+#    #+#             */
/*   Updated: 2022/11/11 22:34:12 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

static void	update_doors_pt2(t_data *data, t_ray *ray)
{
	if (ray->door.sliding == 2)
	{
		if (ray->door.index == 49)
			ray->door.index = 50;
		if (ray->door.offset == -0.2)
			ray->door.offset = 0;
		ray->map->map[ray->door.map_pos.y][ray->door.map_pos.x] = ray->door.index;
		ray->door.door_offsets[ray->door.map_pos.y][ray->door.map_pos.x] = ray->door.offset;
		if (data->timer >= ray->door.opening_timer + 1)
		{
			--ray->door.index;
			ray->door.offset -= 0.20;
			ray->door.opening_timer = data->timer;
		}
		if (ray->door.index == 49)
			ray->door.sliding = 0;
	}
}

void	update_doors(t_data *data, t_ray *ray)
{
	if (ray->door.sliding == 1)
	{
		if (ray->door.index == 56)
			ray->door.index = 50;
		if (ray->door.offset == 1.2)
			ray->door.offset = 0;
		ray->map->map[ray->door.map_pos.y][ray->door.map_pos.x] = ray->door.index;
		ray->door.door_offsets[ray->door.map_pos.y][ray->door.map_pos.x] = ray->door.offset;
		if (data->timer >= ray->door.opening_timer + 1)
		{
			++ray->door.index;
			ray->door.offset += 0.20;
			ray->door.opening_timer = data->timer;
		}
		if (ray->door.index == 56)
		{
			--ray->door.index;
			ray->door.offset -= 0.20;
			ray->door.sliding = 2;
		}
	}
	else if (ray->door.sliding == 2)
		update_doors_pt2(data, ray);
}
