/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_complement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:11:36 by faventur          #+#    #+#             */
/*   Updated: 2022/11/14 12:46:09 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	check_door(t_ray *ray)
{
	if (ray->map->map[ray->map_pos.y][ray->map_pos.x] == '2')
	{
		if (ray->map->map[(int)ray->camera.pos.y + 1][(int)ray->camera.pos.x] == '2'
			|| ray->map->map[(int)ray->camera.pos.y - 1][(int)ray->camera.pos.x] == '2'
			|| ray->map->map[(int)ray->camera.pos.y][(int)ray->camera.pos.x + 1] == '2'
			|| ray->map->map[(int)ray->camera.pos.y][(int)ray->camera.pos.x - 1] == '2'
			|| ray->map->map[(int)ray->camera.pos.y + 1][(int)ray->camera.pos.x + 1] == '2'
			|| ray->map->map[(int)ray->camera.pos.y + 1][(int)ray->camera.pos.x - 1] == '2'
			|| ray->map->map[(int)ray->camera.pos.y - 1][(int)ray->camera.pos.x + 1] == '2'
			|| ray->map->map[(int)ray->camera.pos.y - 1][(int)ray->camera.pos.x - 1] == '2'
			|| ray->map->map[(int)ray->camera.pos.y][(int)ray->camera.pos.x] == '2')
		{
			ray->door.sliding = 1;
			ray->door.map_pos.x = ray->map_pos.x;
			ray->door.map_pos.y = ray->map_pos.y;
		}
	}
}

static void	door_complement_pt2(t_ray *ray)
{
	ray->wall_x_offset = 0.5 * ray->step_coord.x;
	ray->wall_distance = (ray->map_pos.x - ray->camera.pos.x + ray->wall_x_offset
			+ (1 - ray->step_coord.x) / 2) / ray->ray_dir.x;
	ray->wall_x = ray->camera.pos.y + ray->wall_distance * ray->ray_dir.y;
	ray->wall_x -= floor(ray->wall_x);
	if (ray->ray_side.x - (ray->ray_delta.x / 2) < ray->ray_side.y)
	{
		if (1.0 - ray->wall_x <= ray->door.door_offsets[ray->map_pos.y]
			[ray->map_pos.x])
		{
			ray->hit = 0;
			ray->wall_x_offset = 0;
		}
	}
	else
	{
		ray->map_pos.y += ray->step_coord.y;
		ray->side = 1;
		ray->ray_tex = 0;	//any doorframes?
		ray->wall_x_offset = 0;
	}
}

void	door_complement(t_ray *ray)
{
	if (ray->side == 1)
	{
		ray->wall_y_offset = 0.5 * ray->step_coord.y;
		ray->wall_distance = (ray->map_pos.y - ray->camera.pos.y + ray->wall_y_offset
				+ (1 - ray->step_coord.y) / 2) / ray->ray_dir.y;
		ray->wall_x = ray->camera.pos.x + ray->wall_distance * ray->ray_dir.x;
		ray->wall_x -= floor(ray->wall_x);
		if (ray->ray_side.y - (ray->ray_delta.y / 2) < ray->ray_side.x)
		{
			if (1.0 - ray->wall_x <= ray->door.door_offsets[ray->map_pos.y]
				[ray->map_pos.x])
			{
				ray->hit = 0;
				ray->wall_y_offset = 0;
			}
		}
		else
		{
			ray->map_pos.x += ray->step_coord.x;
			ray->side = 0;
			ray->ray_tex = 0; //Draw door frame instead
			ray->wall_y_offset = 0;
		}
	}
	else
		door_complement_pt2(ray);
}
