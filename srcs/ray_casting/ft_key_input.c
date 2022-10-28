/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:52:36 by faventur          #+#    #+#             */
/*   Updated: 2022/10/28 11:56:25 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

static void	ft_key_input_other(t_data *data, t_ray *ray, t_var *var,
				mlx_key_data_t keydata)
{
	if (keydata.key == (keys_t)LEFT_ARROW)
	{
		var->old_dir_x = ray->dir.x;
		ray->dir.x = ray->dir.x * ray->k.ncos - ray->dir.y
			* ray->k.nsin;
		ray->dir.y = var->old_dir_x * ray->k.nsin + ray->dir.y
			* ray->k.ncos;
		var->old_plane_x = ray->plane.x;
		ray->plane.x = ray->plane.x * ray->k.ncos - ray->plane.y
			* ray->k.nsin;
		ray->plane.y = var->old_plane_x * ray->k.nsin + ray->plane.y
			* ray->k.ncos;
		data->refresh = 1;
	}
	if (keydata.key == (keys_t)ESCAPE)
		exit(0);
	else
		ft_key_input_arrows(data, ray, var, keydata);
}

static void	ft_key_input_rest(t_data *data, t_ray *ray, t_var *var,
				mlx_key_data_t keydata)
{
	if (keydata.key == (keys_t)RIGHT_ARROW)
	{
		var->old_dir_x = ray->dir.x;
		ray->dir.x = ray->dir.x * ray->k.pcos - ray->dir.y
			* ray->k.psin;
		ray->dir.y = var->old_dir_x * ray->k.psin + ray->dir.y
			* ray->k.pcos;
		var->old_plane_x = ray->plane.x;
		ray->plane.x = ray->plane.x * ray->k.pcos - ray->plane.y
			* ray->k.psin;
		ray->plane.y = var->old_plane_x * ray->k.psin + ray->plane.y
			* ray->k.pcos;
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

	ft_bzero(&var, sizeof(var));
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
