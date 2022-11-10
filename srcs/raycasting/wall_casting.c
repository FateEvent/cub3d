/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_casting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:08:24 by faventur          #+#    #+#             */
/*   Updated: 2022/11/10 15:07:24 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	wall_distance_calculator(t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_distance = (ray->map_pos.x - ray->camera.pos.x
				+ ray->wall_x_offset + (1 - ray->step_coord.x) / 2)
			/ ray->ray_dir.x;
	else
		ray->wall_distance = (ray->map_pos.y - ray->camera.pos.y
				+ ray->wall_y_offset + (1 - ray->step_coord.y) / 2)
			/ ray->ray_dir.y;
}
/*
void	transparent_wall_complement(t_ray *ray, int x)
{
	t_var	var;

	ft_bzero(&var, sizeof(var));
	if (ray->side == 1) {
		if (ray->ray_side.y - (ray->ray_delta.y / 2) < ray->ray_side.x) { //If ray hits offset wall
			var.is_wall_defined = false;
			while (var.i < tpWalls.length) {
				if (tpWalls[var.i].mapX == ray->map_pos.x && tpWalls[var.i].mapY == ray->map_pos.y) {
					tpWalls[var.i].screenX.push(x);
					var.is_wall_defined = true;
					break;
				}
				var.i++;
			}
			if (!var.is_wall_defined) {
				tpWall = new TransparentWall(whichCamera, ray->map_pos.x, ray->map_pos.y, ray->side, x);
				tpWalls.push(tpWall);
			}
		}
	} else { //side == 0
		if (ray->ray_side.x - (ray->ray_delta.x / 2) < ray->ray_side.y) {
			var.is_wall_defined = false;
			while (var.i < tpWalls.length) {
				if (tpWalls[var.i].mapX == ray->map_pos.x && tpWalls[var.i].mapY == ray->map_pos.y) {
					tpWalls[var.i].screenX.push(x);
					var.is_wall_defined = true;
					break;
				}
				var.i++;
			}
			if (!var.is_wall_defined) {
				tpWall = new TransparentWall(whichCamera, ray->map_pos.x, ray->map_pos.y, side, x);
				tpWalls.push(tpWall);
			}
		}
	}
}
*/

void	door_complement_pt2(t_ray *ray)
{
	ray->wall_x_offset = 0.5 * ray->step_coord.x;
	ray->wall_distance = (ray->map_pos.x - ray->camera.pos.x + ray->wall_x_offset
			+ (1 - ray->step_coord.x) / 2) / ray->ray_dir.x;
	ray->wall_x = ray->camera.pos.y + ray->wall_distance * ray->ray_dir.y;
	ray->wall_x -= floor(ray->wall_x);
	if (ray->ray_side.x - (ray->ray_delta.x / 2) < ray->ray_side.y)
	{
		if (1.0 - ray->wall_x < ray->door.door_offsets[ray->map_pos.y]
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
		ray->ray_tex = 0;
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
		ray->wall_x = ray->camera.pos.y + ray->wall_distance * ray->ray_dir.x;
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

void	ft_check_doors(t_ray *ray, int x)
{
	(void) x;
	ray->ray_tex = ray->map->map[ray->map_pos.y][ray->map_pos.x] - '0';
	if (ray->ray_tex != 0)
	{
		if (ray->ray_tex == 1)
		{
			ray->hit = 1;
			ray->wall_x_offset = 0;
		}
//		else if (rayTex == 9)//Transparent walls)
//			transparent_wall_complement(ray, x);
		else if (ray->ray_tex == 2 && ray->door.door_states[ray->map_pos.y]
			[ray->map_pos.x] != 2)
		{ //Closed, opening, or closing doors
			ray->hit = 1;
			door_complement(ray);
		}
	}
}

void	ray_launcher(t_ray *ray, int x)
{
	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->ray_side.x < ray->ray_side.y)
		{
			ray->ray_side.x += ray->ray_delta.x;
			ray->map_pos.x += ray->step_coord.x;
			ray->side = 0;
		}
		else
		{
			ray->ray_side.y += ray->ray_delta.y;
			ray->map_pos.y += ray->step_coord.y;
			ray->side = 1;
		}
		ft_check_doors(ray, x);
	}
}

void	rayside_calculator(t_ray *ray)
{
	if (ray->ray_dir.x < 0)
	{
		ray->step_coord.x = -1;
		ray->ray_side.x = (ray->camera.pos.x - ray->map_pos.x)
			* ray->ray_delta.x;
	}
	else
	{
		ray->step_coord.x = 1;
		ray->ray_side.x = (ray->map_pos.x + 1.0 - ray->camera.pos.x)
			* ray->ray_delta.x;
	}
	if (ray->ray_dir.y < 0)
	{
		ray->step_coord.y = -1;
		ray->ray_side.y = (ray->camera.pos.y - ray->map_pos.y)
			* ray->ray_delta.y;
	}
	else
	{
		ray->step_coord.y = 1;
		ray->ray_side.y = (ray->map_pos.y + 1.0 - ray->camera.pos.y)
			* ray->ray_delta.y;
	}
}

void	ray_delta_calculator(t_ray *ray)
{
	if (ray->ray_dir.x == 0)
		ray->ray_delta.x = 1e30;
	else
		ray->ray_delta.x = fabs(1 / ray->ray_dir.x);
	if (ray->ray_dir.y == 0)
		ray->ray_delta.y = 1e30;
	else
		ray->ray_delta.y = fabs(1 / ray->ray_dir.y);
}

void	ray_data_init(t_ray *ray, int x)
{
	ray->camera.camera_x = 2 * x / (double)ray->resolution.x - 1;
	ray->ray_dir.x = ray->camera.dir.x + ray->camera.plane.x * ray->camera.camera_x;
	ray->ray_dir.y = ray->camera.dir.y + ray->camera.plane.y * ray->camera.camera_x;
	ray->map_pos.x = (int)ray->camera.pos.x;
	ray->map_pos.y = (int)ray->camera.pos.y;
	ray->text_select = 0;
	ray_delta_calculator(ray);
}