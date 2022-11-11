/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:08:44 by albaur            #+#    #+#             */
/*   Updated: 2022/11/11 16:11:25 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	update_doors(t_data *data, t_ray *ray)
{
	t_var	var;

	ft_bzero(&var, sizeof(var));
	var.width = data->map->size.x;
	var.height = data->map->size.y;
	(void) ray;
//	if (ray->door.sliding && ray->map->map[ray->map_pos.y][ray->map_pos.x] == '2')
//	{
//		ray->door.door_offsets[ray->map_pos.y][ray->map_pos.x] += 0.20;
//		ray->map->map[ray->map_pos.y][ray->map_pos.x] += 1;
//		ray->door.sliding = 0;
//	}
}
