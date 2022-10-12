/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:52:36 by faventur          #+#    #+#             */
/*   Updated: 2022/10/12 16:32:38 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

static void	ft_key_input_child(t_program *data, mlx_key_data_t keydata)
{
	t_key_input	var;
	int			angle;

	if (keydata.key == DOWN)
	{
		var.player_cos = cosf(degrees_to_radians(data->player.angle))
			* data->player.speed.movement;
		var.player_sin = sinf(degrees_to_radians(data->player.angle))
			* data->player.speed.movement;
		var.new_x = data->player.x - var.player_cos;
		var.new_y = data->player.y - var.player_sin;
		var.check_x = floorf(var.new_x - var.player_cos * data->player.radius);
        var.check_y = floorf(var.new_y - var.player_sin * data->player.radius);
		if (data->map->map[(int)var.check_y][(int)floorf(data->player.x)] == 48)
			data->player.y = var.new_y;
		if (data->map->map[(int)floorf(data->player.y)][(int)var.check_x] == 48)
			data->player.x = var.new_x;
	}
	if (keydata.key == LEFT)
	{
		data->player.angle -= data->player.speed.rotation;
		angle = data->player.angle;
		angle %= 360;

	}
	if (keydata.key == RIGHT)
	{
		data->player.angle += data->player.speed.rotation;
		angle = data->player.angle;
		angle %= 360;
	}
	if (keydata.key == ESCAPE)
		exit(0);
}

void	ft_key_input(mlx_key_data_t keydata, void *param)
{
	t_program	*data;
	t_key_input	var;

	data = (t_program *)param;
	if (keydata.key == UP)
	{
		var.player_cos = cosf(degrees_to_radians(data->player.angle))
			* data->player.speed.movement;
		var.player_sin = sinf(degrees_to_radians(data->player.angle))
			* data->player.speed.movement;
		var.new_x = data->player.x + var.player_cos;
		var.new_y = data->player.y + var.player_sin;
		var.check_x = floorf(var.new_x + var.player_cos * data->player.radius);
        var.check_y = floorf(var.new_y + var.player_sin * data->player.radius);
		if (data->map->map[(int)var.check_y][(int)floorf(data->player.x)] == 48)
			data->player.y = var.new_y;
		if (data->map->map[(int)floorf(data->player.y)][(int)var.check_x] == 48)
			data->player.x = var.new_x;
	}
	else
		ft_key_input_child(data, keydata);
}
