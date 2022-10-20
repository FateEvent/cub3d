/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:52:36 by faventur          #+#    #+#             */
/*   Updated: 2022/10/20 14:31:16 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	ft_update(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	data->frame++;
	if (data->frame % 1 == 0 && data->refresh == 1)	// 30 is the render delay
	{
		fill_window(data, 0x650000FF);
		ray_casting(data);
		data->refresh = 0;
	}
}

static void	ft_key_input_other(t_data *data, t_ray *ray, t_var *var,
				mlx_key_data_t keydata)
{
if (keydata.key == (keys_t)RIGHT)
	{
		var->old_dir_x = ray->dir.x;
		ray->dir.x = ray->dir.x * cos(-var->rotation) - ray->dir.y
			* sin(-var->rotation);
		ray->dir.y = var->old_dir_x * sin(-var->rotation) + ray->dir.y
			* cos(-var->rotation);
		var->old_plane_x = ray->plane.x;
		ray->plane.x = ray->plane.x * cos(-var->rotation) - ray->plane.y
			* sin(-var->rotation);
		ray->plane.y = var->old_plane_x * sin(-var->rotation) + ray->plane.y
			* cos(-var->rotation);
		data->refresh = 1;
	}
	if (keydata.key == (keys_t)ESCAPE)
		exit(0);
}

static void	ft_key_input_rest(t_data *data, t_ray *ray, t_var *var,
				mlx_key_data_t keydata)
{
	if (keydata.key == (keys_t)LEFT)
	{
		var->old_dir_x = ray->dir.x;
		ray->dir.x = ray->dir.x * cos(var->rotation) - ray->dir.y
			* sin(var->rotation);
		ray->dir.y = var->old_dir_x * sin(var->rotation) + ray->dir.y
			* cos(var->rotation);
		var->old_plane_x = ray->plane.x;
		ray->plane.x = ray->plane.x * cos(var->rotation) - ray->plane.y
			* sin(var->rotation);
		ray->plane.y = var->old_plane_x * sin(var->rotation) + ray->plane.y
			* cos(var->rotation);
		data->refresh = 1;
	}
	else
		ft_key_input_other(data, ray, var, keydata);
}

static void	ft_key_input_child(t_data *data, t_ray *ray, t_var *var,
				mlx_key_data_t keydata)
{
	if (keydata.key == (keys_t)DOWN)
	{
		if (data->map->map[(int)(ray->pos.y - ray->dir.y * var->movement)]
			[(int)(ray->pos.x)] <= '0')
			ray->pos.y -= ray->dir.y * var->movement;
		if (data->map->map[(int)(ray->pos.y)]
			[(int)(ray->pos.x - ray->dir.x * var->movement)] <= '0')
			ray->pos.x -= ray->dir.x * var->movement;
		data->refresh = 1;
	}
	else
		ft_key_input_rest(data, ray, var, keydata);
}

void	ft_key_input(mlx_key_data_t keydata, void *param)
{
	t_data	*data;
	t_ray	*ray;
	t_var	var;

	data = (t_data *)param;
	ray = &data->ray_data;
	var.rotation = data->player.speed.rotation;
	var.movement = data->player.speed.movement;
	if (keydata.key == (keys_t)UP)
	{
		if (data->map->map[(int)(ray->pos.y)]
			[(int)(ray->pos.x + ray->dir.x * var.movement)] <= '0')
			ray->pos.x += ray->dir.x * var.movement;
		if (data->map->map[(int)(ray->pos.y + ray->dir.y * var.movement)]
			[(int)(ray->pos.x)] <= '0')
			ray->pos.y += ray->dir.y * var.movement;
		data->refresh = 1;
	}
	else
		ft_key_input_child(data, ray, &var, keydata);
}
