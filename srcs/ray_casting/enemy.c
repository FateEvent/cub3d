/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:15:14 by albaur            #+#    #+#             */
/*   Updated: 2022/11/07 14:27:29 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	update_enemy(t_data *data, t_ray *ray)
{
	t_s_caster	*sprite;
	t_vec2		start;
	t_vec2		pos;
	double		dist;

	sprite = &ray->sprite;
	if (data->enemy.disable_ai == 1)
		return ;
	start = (t_vec2){sprite->sprites[0].x, sprite->sprites[0].y};
	dist = ft_vect2_distance_calc(start, data->ray_data.pos);
	if (dist <= 5)
	{
		mlx_image_to_window(data->mlx, data->enemy.warning_image->img, (WIDTH / 2) - 100,
			(HEIGHT / 2) - 200);
		data->enemy.warning_image->img->enabled = 1;
		if (data->time % 60 == 0)
			data->enemy.kill_countdown--;
	}
	else
	{
		data->enemy.warning_image->img->enabled = 0;
		data->enemy.kill_countdown = KILLCOUNTDOWN;
		if (data->time % 60 == 0)
			data->enemy.move_countdown--;
		if (data->enemy.move_countdown <= 0)
		{
			pos = pathfinding_pos_dist(data, start, ray->pos, 10);
			sprite->sprites[0].x = pos.x;
			sprite->sprites[0].y = pos.y;
			data->enemy.move_countdown = MOVECOUNTDOWN;
		}
	}
}
