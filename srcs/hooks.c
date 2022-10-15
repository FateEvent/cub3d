/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:52:36 by faventur          #+#    #+#             */
/*   Updated: 2022/10/15 22:00:26 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

static int	ft_key_input_child(t_data *data, int key)
{
	t_var	var;

	if (key == LEFT)
	{
		var.old_dir_x = data->ray_data.dir_x;
		data->ray_data.dir_x = data->ray_data.dir_x * cos(data->rotate_speed) - data->ray_data.dir_y * sin(data->rotate_speed);
		data->ray_data.dir_y = var.old_dir_x * sin(data->rotate_speed) + data->ray_data.dir_y * cos(data->rotate_speed);
		var.old_plane_x = data->ray_data.plane_x;
		data->ray_data.plane_x = data->ray_data.plane_x * cos(data->rotate_speed) - data->ray_data.plane_y * sin(data->rotate_speed);
		data->ray_data.plane_y = var.old_plane_x * sin(data->rotate_speed) + data->ray_data.plane_y * cos(data->rotate_speed);

	}
	if (key == RIGHT)
	{
		var.old_dir_x = data->ray_data.dir_x;
		data->ray_data.dir_x = data->ray_data.dir_x * cos(-data->rotate_speed) - data->ray_data.dir_y * sin(-data->rotate_speed);
		data->ray_data.dir_y = var.old_dir_x * sin(-data->rotate_speed) + data->ray_data.dir_y * cos(-data->rotate_speed);
		var.old_plane_x = data->ray_data.plane_x;
		data->ray_data.plane_x = data->ray_data.plane_x * cos(-data->rotate_speed) - data->ray_data.plane_y * sin(-data->rotate_speed);
		data->ray_data.plane_y = var.old_plane_x * sin(-data->rotate_speed) + data->ray_data.plane_y * cos(-data->rotate_speed);
	}
	if (key == ESCAPE)
		exit(0);
	return (0);
}

int	ft_key_input(int key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (key == UP)
	{
		if (data->map->map[(int)(data->ray_data.pos_y)]
			[(int)(data->ray_data.pos_x + data->ray_data.dir_x * data->move_speed)] <= '0')
			data->ray_data.pos_x += data->ray_data.dir_x * data->move_speed;
		if (data->map->map[(int)(data->ray_data.pos_y + data->ray_data.dir_y * data->move_speed)]
			[(int)(data->ray_data.pos_x)] <= '0')
			data->ray_data.pos_y += data->ray_data.dir_y * data->move_speed;
	}
	if (key == DOWN)
	{
		if (data->map->map[(int)(data->ray_data.pos_y - data->ray_data.dir_y * data->move_speed)]
			[(int)(data->ray_data.pos_x)] <= '0')
			data->ray_data.pos_y -= data->ray_data.dir_y * data->move_speed;
		if (data->map->map[(int)(data->ray_data.pos_y)]
			[(int)(data->ray_data.pos_x - data->ray_data.dir_x * data->move_speed)] <= '0')
			data->ray_data.pos_x -= data->ray_data.dir_x * data->move_speed;
	}
	else
		return (ft_key_input_child(data, key));
	return (0);
}
