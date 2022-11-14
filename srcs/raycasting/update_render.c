/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:21:12 by albaur            #+#    #+#             */
/*   Updated: 2022/11/14 11:01:33 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	update_render(void *param)
{
	t_data	*data;

	data = (t_data *)param;
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
