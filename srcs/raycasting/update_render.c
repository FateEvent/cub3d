/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:21:12 by albaur            #+#    #+#             */
/*   Updated: 2022/11/11 17:42:43 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	sliding_doors(t_ray *ray)
{
	ray->door.door_offsets[ray->map_pos.y][ray->map_pos.x] += 0.20;
	ray->door.sliding = 0;
}

void	update_render(void *param)
{
	t_data	*data;
	t_ray	*ray;

	data = (t_data *)param;
	ray = &data->ray_data;
	get_delay(1, 16666);
	while (data->delay > 16666)
	{
		key_input(data);
		++data->time;
		data->delay -= 16666;
	}
	key_input(data);
	if (data->exit == 1)
		return (close_hook(data));
	if (update_events(data))
		return ;
	ray_casting(data);
	update_doors(data, &data->ray_data);
	draw_minimap(data);
	data->delay += get_delay(0, 16666);
	++data->time;
	data->timer = get_time();
	if (data->enemy.alive == 0)
		show_death(data);
}
