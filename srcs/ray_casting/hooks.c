/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:52:36 by faventur          #+#    #+#             */
/*   Updated: 2022/10/24 14:32:44 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	ft_update(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	data->frame++;
	if (data->refresh == 1)	// 30 is the render delay
	{
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
		ray->dir.x = ray->dir.x * ray->ncos - ray->dir.y
			* ray->nsin;
		ray->dir.y = var->old_dir_x * ray->nsin + ray->dir.y
			* ray->ncos;
		var->old_plane_x = ray->plane.x;
		ray->plane.x = ray->plane.x * ray->ncos - ray->plane.y
			* ray->nsin;
		ray->plane.y = var->old_plane_x * ray->nsin + ray->plane.y
			* ray->ncos;
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
		ray->dir.x = ray->dir.x * ray->pcos - ray->dir.y
			* ray->psin;
		ray->dir.y = var->old_dir_x * ray->psin + ray->dir.y
			* ray->pcos;
		var->old_plane_x = ray->plane.x;
		ray->plane.x = ray->plane.x * ray->pcos - ray->plane.y
			* ray->psin;
		ray->plane.y = var->old_plane_x * ray->psin + ray->plane.y
			* ray->pcos;
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
			[(int)(ray->pos.x)] != '1')
			ray->pos.y -= ray->dir.y * var->movement;
		if (data->map->map[(int)(ray->pos.y)]
			[(int)(ray->pos.x - ray->dir.x * var->movement)] != '1')
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
			[(int)(ray->pos.x + ray->dir.x * var.movement)] != '1')
			ray->pos.x += ray->dir.x * var.movement;
		if (data->map->map[(int)(ray->pos.y + ray->dir.y * var.movement)]
			[(int)(ray->pos.x)] != '1')
			ray->pos.y += ray->dir.y * var.movement;
		data->refresh = 1;
	}
	else
		ft_key_input_child(data, ray, &var, keydata);
}
