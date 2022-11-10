/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:13:07 by albaur            #+#    #+#             */
/*   Updated: 2022/11/10 11:21:27 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

static void	key_input_other(t_data *data, t_ray *ray, t_var *var)
{
	if (data->key == (keys_t)MLX_KEY_LEFT)
	{
		var->old_dir_x = ray->camera.dir.x;
		ray->camera.dir.x = ray->camera.dir.x * ray->k.ncos - ray->camera.dir.y
			* ray->k.nsin;
		ray->camera.dir.y = var->old_dir_x * ray->k.nsin + ray->camera.dir.y
			* ray->k.ncos;
		var->old_plane_x = ray->camera.plane.x;
		ray->camera.plane.x = ray->camera.plane.x * ray->k.ncos - ray->camera.plane.y
			* ray->k.nsin;
		ray->camera.plane.y = var->old_plane_x * ray->k.nsin + ray->camera.plane.y
			* ray->k.ncos;
		data->player.yaw -= data->player.speed.rotation;
	}
	if (data->key == (keys_t)MLX_KEY_ESCAPE)
		data->exit = 1;
	else
		key_input_arrows(data, ray, var);
}

static void	key_input_rest(t_data *data, t_ray *ray, t_var *var)
{
	if (data->key == (keys_t)MLX_KEY_RIGHT)
	{
		var->old_dir_x = ray->camera.dir.x;
		ray->camera.dir.x = ray->camera.dir.x * ray->k.pcos - ray->camera.dir.y
			* ray->k.psin;
		ray->camera.dir.y = var->old_dir_x * ray->k.psin + ray->camera.dir.y
			* ray->k.pcos;
		var->old_plane_x = ray->camera.plane.x;
		ray->camera.plane.x = ray->camera.plane.x * ray->k.pcos - ray->camera.plane.y
			* ray->k.psin;
		ray->camera.plane.y = var->old_plane_x * ray->k.psin + ray->camera.plane.y
			* ray->k.pcos;
		data->player.yaw += data->player.speed.rotation;
	}
	else
		key_input_other(data, ray, var);
}

static void	key_input_child(t_data *data, t_ray *ray, t_var *var)
{
	if (data->key == (keys_t)MLX_KEY_S)
	{
		if (data->map->map[(int)(ray->camera.pos.y - ray->camera.dir.y * var->movement)]
			[(int)(ray->camera.pos.x)] != '1')
			ray->camera.pos.y -= ray->camera.dir.y * var->movement;
		if (data->map->map[(int)(ray->camera.pos.y)]
			[(int)(ray->camera.pos.x - ray->camera.dir.x * var->movement)] != '1')
			ray->camera.pos.x -= ray->camera.dir.x * var->movement;
	}
	else
		key_input_rest(data, ray, var);
}

void	update_key(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	if (keydata.key == MLX_KEY_F && keydata.action == MLX_PRESS)
		data->key = keydata.key;
	if (keydata.action == MLX_PRESS)
		data->key = keydata.key;
	else if (keydata.action == MLX_RELEASE && keydata.key == (keys_t)data->key)
		data->key = 0;
}

void	key_input(t_data *data)
{
	t_ray	*ray;
	t_var	var;

	ft_bzero(&var, sizeof(var));
	ray = &data->ray_data;
	var.rotation = data->player.speed.rotation;
	var.movement = data->player.speed.movement;
	if (data->key == (keys_t)MLX_KEY_W)
	{
		if (data->map->map[(int)(ray->camera.pos.y)]
			[(int)(ray->camera.pos.x + ray->camera.dir.x * var.movement)] != '1')
			ray->camera.pos.x += ray->camera.dir.x * var.movement;
		if (data->map->map[(int)(ray->camera.pos.y + ray->camera.dir.y * var.movement)]
			[(int)(ray->camera.pos.x)] != '1')
			ray->camera.pos.y += ray->camera.dir.y * var.movement;
	}
	else
		key_input_child(data, ray, &var);
}
