/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:52:36 by faventur          #+#    #+#             */
/*   Updated: 2022/10/19 14:26:59 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

static void	ft_key_input_child(t_data *data, mlx_key_data_t keydata)
{
	t_var	var;

	if (keydata.key == (keys_t)LEFT)
	{
		var.old_dir_x = data->ray_data.dir.x;
		data->ray_data.dir.x = data->ray_data.dir.x * cos(data->rotate_speed) - data->ray_data.dir.y * sin(data->rotate_speed);
		data->ray_data.dir.y = var.old_dir_x * sin(data->rotate_speed) + data->ray_data.dir.y * cos(data->rotate_speed);
		var.old_plane_x = data->ray_data.plane.x;
		data->ray_data.plane.x = data->ray_data.plane.x * cos(data->rotate_speed) - data->ray_data.plane.y * sin(data->rotate_speed);
		data->ray_data.plane.y = var.old_plane_x * sin(data->rotate_speed) + data->ray_data.plane.y * cos(data->rotate_speed);
		data->refresh = 1;

	}
	if (keydata.key == (keys_t)RIGHT)
	{
		var.old_dir_x = data->ray_data.dir.x;
		data->ray_data.dir.x = data->ray_data.dir.x * cos(-data->rotate_speed) - data->ray_data.dir.y * sin(-data->rotate_speed);
		data->ray_data.dir.y = var.old_dir_x * sin(-data->rotate_speed) + data->ray_data.dir.y * cos(-data->rotate_speed);
		var.old_plane_x = data->ray_data.plane.x;
		data->ray_data.plane.x = data->ray_data.plane.x * cos(-data->rotate_speed) - data->ray_data.plane.y * sin(-data->rotate_speed);
		data->ray_data.plane.y = var.old_plane_x * sin(-data->rotate_speed) + data->ray_data.plane.y * cos(-data->rotate_speed);
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
		if (data->map->map[(int)(data->ray_data.pos.y)]
			[(int)(data->ray_data.pos.x + data->ray_data.dir.x * data->move_speed)] <= '0')
			data->ray_data.pos.x += data->ray_data.dir.x * data->move_speed;
		if (data->map->map[(int)(data->ray_data.pos.y + data->ray_data.dir.y * data->move_speed)]
			[(int)(data->ray_data.pos.x)] <= '0')
			data->ray_data.pos.y += data->ray_data.dir.y * data->move_speed;
		data->refresh = 1;
	}
	if (keydata.key == (keys_t)DOWN)
	{
		if (data->map->map[(int)(data->ray_data.pos.y - data->ray_data.dir.y * data->move_speed)]
			[(int)(data->ray_data.pos.x)] <= '0')
			data->ray_data.pos.y -= data->ray_data.dir.y * data->move_speed;
		if (data->map->map[(int)(data->ray_data.pos.y)]
			[(int)(data->ray_data.pos.x - data->ray_data.dir.x * data->move_speed)] <= '0')
			data->ray_data.pos.x -= data->ray_data.dir.x * data->move_speed;
		data->refresh = 1;
	}
	else
		ft_key_input_child(data, keydata);
}
