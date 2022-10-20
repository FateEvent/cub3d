/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:52:36 by faventur          #+#    #+#             */
/*   Updated: 2022/10/20 13:59:14 by faventur         ###   ########.fr       */
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

static void	ft_key_input_other(t_data *data, t_var *var,
				mlx_key_data_t keydata)
{
if (keydata.key == (keys_t)RIGHT)
	{
		var->old_dir_x = data->ray_data.dir.x;
		data->ray_data.dir.x = data->ray_data.dir.x * cos(-data->player.speed.rotation) - data->ray_data.dir.y * sin(-data->player.speed.rotation);
		data->ray_data.dir.y = var->old_dir_x * sin(-data->player.speed.rotation) + data->ray_data.dir.y * cos(-data->player.speed.rotation);
		var->old_plane_x = data->ray_data.plane.x;
		data->ray_data.plane.x = data->ray_data.plane.x * cos(-data->player.speed.rotation) - data->ray_data.plane.y * sin(-data->player.speed.rotation);
		data->ray_data.plane.y = var->old_plane_x * sin(-data->player.speed.rotation) + data->ray_data.plane.y * cos(-data->player.speed.rotation);
		data->refresh = 1;
	}
	if (keydata.key == (keys_t)ESCAPE)
		exit(0);
}

static void	ft_key_input_rest(t_data *data, t_var *var,
				mlx_key_data_t keydata)
{
	if (keydata.key == (keys_t)LEFT)
	{
		var->old_dir_x = data->ray_data.dir.x;
		data->ray_data.dir.x = data->ray_data.dir.x * cos(data->player.speed.rotation) - data->ray_data.dir.y * sin(data->player.speed.rotation);
		data->ray_data.dir.y = var->old_dir_x * sin(data->player.speed.rotation) + data->ray_data.dir.y * cos(data->player.speed.rotation);
		var->old_plane_x = data->ray_data.plane.x;
		data->ray_data.plane.x = data->ray_data.plane.x * cos(data->player.speed.rotation) - data->ray_data.plane.y * sin(data->player.speed.rotation);
		data->ray_data.plane.y = var->old_plane_x * sin(data->player.speed.rotation) + data->ray_data.plane.y * cos(data->player.speed.rotation);
		data->refresh = 1;
	}
	else
		ft_key_input_other(data, var, keydata);
}

static void	ft_key_input_child(t_data *data, t_var *var,
				mlx_key_data_t keydata)
{
	if (keydata.key == (keys_t)DOWN)
	{
		if (data->map->map[(int)(data->ray_data.pos.y - data->ray_data.dir.y * data->player.speed.movement)]
			[(int)(data->ray_data.pos.x)] <= '0')
			data->ray_data.pos.y -= data->ray_data.dir.y * data->player.speed.movement;
		if (data->map->map[(int)(data->ray_data.pos.y)]
			[(int)(data->ray_data.pos.x - data->ray_data.dir.x * data->player.speed.movement)] <= '0')
			data->ray_data.pos.x -= data->ray_data.dir.x * data->player.speed.movement;
		data->refresh = 1;
	}
	else
		ft_key_input_rest(data, var, keydata);
}

void	ft_key_input(mlx_key_data_t keydata, void *param)
{
	t_data	*data;
	t_ray	ray;
	t_var	var;

	data = (t_data *)param;
	ray = data->ray_data;
	var.rotation = data->player.speed.rotation;
	var.movement = data->player.speed.movement;
	if (keydata.key == (keys_t)UP)
	{
		if (data->map->map[(int)(data->ray_data.pos.y)]
			[(int)(data->ray_data.pos.x + data->ray_data.dir.x * data->player.speed.movement)] <= '0')
			data->ray_data.pos.x += data->ray_data.dir.x * data->player.speed.movement;
		if (data->map->map[(int)(data->ray_data.pos.y + data->ray_data.dir.y * data->player.speed.movement)]
			[(int)(data->ray_data.pos.x)] <= '0')
			data->ray_data.pos.y += data->ray_data.dir.y * data->player.speed.movement;
		data->refresh = 1;
	}
	else
		ft_key_input_child(data, &var, keydata);
}
