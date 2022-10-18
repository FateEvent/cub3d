/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:52:36 by faventur          #+#    #+#             */
/*   Updated: 2022/10/18 12:02:51 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

static void	ft_key_input_child(t_data *data, mlx_key_data_t keydata)
{
	t_var	var;

	if (keydata.key == (keys_t)LEFT)
	{
		var.old_dir_x = data->ray_data.dir_x;
		data->ray_data.dir_x = data->ray_data.dir_x * cos(data->rotate_speed) - data->ray_data.dir_y * sin(data->rotate_speed);
		data->ray_data.dir_y = var.old_dir_x * sin(data->rotate_speed) + data->ray_data.dir_y * cos(data->rotate_speed);
		var.old_plane_x = data->ray_data.plane_x;
		data->ray_data.plane_x = data->ray_data.plane_x * cos(data->rotate_speed) - data->ray_data.plane_y * sin(data->rotate_speed);
		data->ray_data.plane_y = var.old_plane_x * sin(data->rotate_speed) + data->ray_data.plane_y * cos(data->rotate_speed);
		data->refresh = 1;

	}
	if (keydata.key == (keys_t)RIGHT)
	{
		var.old_dir_x = data->ray_data.dir_x;
		data->ray_data.dir_x = data->ray_data.dir_x * cos(-data->rotate_speed) - data->ray_data.dir_y * sin(-data->rotate_speed);
		data->ray_data.dir_y = var.old_dir_x * sin(-data->rotate_speed) + data->ray_data.dir_y * cos(-data->rotate_speed);
		var.old_plane_x = data->ray_data.plane_x;
		data->ray_data.plane_x = data->ray_data.plane_x * cos(-data->rotate_speed) - data->ray_data.plane_y * sin(-data->rotate_speed);
		data->ray_data.plane_y = var.old_plane_x * sin(-data->rotate_speed) + data->ray_data.plane_y * cos(-data->rotate_speed);
		data->refresh = 1;
	}
	if (keydata.key == (keys_t)ESCAPE)
		exit(0);
}

void	ft_key_input(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keydata.key == (keys_t)UP)
	{
		if (data->map->map[(int)(data->ray_data.pos_y)]
			[(int)(data->ray_data.pos_x + data->ray_data.dir_x * data->move_speed)] <= '0')
			data->ray_data.pos_x += data->ray_data.dir_x * data->move_speed;
		if (data->map->map[(int)(data->ray_data.pos_y + data->ray_data.dir_y * data->move_speed)]
			[(int)(data->ray_data.pos_x)] <= '0')
			data->ray_data.pos_y += data->ray_data.dir_y * data->move_speed;
		data->refresh = 1;
	}
	if (keydata.key == (keys_t)DOWN)
	{
		if (data->map->map[(int)(data->ray_data.pos_y - data->ray_data.dir_y * data->move_speed)]
			[(int)(data->ray_data.pos_x)] <= '0')
			data->ray_data.pos_y -= data->ray_data.dir_y * data->move_speed;
		if (data->map->map[(int)(data->ray_data.pos_y)]
			[(int)(data->ray_data.pos_x - data->ray_data.dir_x * data->move_speed)] <= '0')
			data->ray_data.pos_x -= data->ray_data.dir_x * data->move_speed;
		data->refresh = 1;
	}
	else
		ft_key_input_child(data, keydata);
}
