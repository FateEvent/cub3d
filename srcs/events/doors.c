/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:08:44 by albaur            #+#    #+#             */
/*   Updated: 2022/11/11 17:57:25 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	update_doors(t_data *data, t_ray *ray)
{
	if (ray->door.sliding)
	{
		if (ray->door.index == 56)
			ray->door.index = 50;
		if (ray->door.offset == 1.2)
			ray->door.offset = 0;
		ray->map->map[ray->door.map_pos.y][ray->door.map_pos.x] = ray->door.index;
		ray->door.door_offsets[ray->door.map_pos.y][ray->door.map_pos.x] = ray->door.offset;
//		printf("%c %f\n", ray->map->map[ray->door.map_pos.y][ray->door.map_pos.x],
//			ray->door.door_offsets[ray->door.map_pos.y][ray->door.map_pos.x]);
//		printf("%d %f\n", ray->door.index, ray->door.offset);
		if (data->timer >= ray->door.opening_timer + 1)
		{
			++ray->door.index;
			ray->door.offset += 0.20;
			ray->door.opening_timer = data->timer;
		}
		if (ray->door.index == 56)
			ray->door.sliding = 0;
	}
}
