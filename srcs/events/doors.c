/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:08:44 by albaur            #+#    #+#             */
/*   Updated: 2022/11/11 17:28:59 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	update_doors(t_data *data, t_ray *ray)
{
	if (ray->door.sliding)
	{
		if (ray->door.index == 56)
			ray->door.index = 50;
		if (ray->door.offset == 1)
			ray->door.offset = 0;
		ray->map->map[ray->door.map_pos.y][ray->door.map_pos.x] = ray->door.index;
		ray->map->map[ray->door.map_pos.y][ray->door.map_pos.x] = ray->door.offset;
		++ray->door.index;
		ray->door.offset += 0.20;
		if (data->timer >= ray->door.opening_timer + 0.4)
		{
			ray->door.opening_timer = data->timer;
		}
		ray->door.sliding = 0;
	}
}
