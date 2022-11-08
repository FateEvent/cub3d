/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding_except.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:30:57 by albaur            #+#    #+#             */
/*   Updated: 2022/11/08 17:51:06 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

t_vec2	pathfinding_pos_except(t_data *data, t_vec2 pos)
{
	int		tries;
	t_vec2	pos2;

	tries = 1500;
	pos2 = pathfinding_pos_dist(data, (t_vec2){0, 0},
		data->ray_data.pos, MINDISTANCE);
	while (pos.x - 0.5 == pos2.x && pos.y - 0.5 == pos2.y)
	{
		pos2 = pathfinding_pos_dist(data, (t_vec2){0, 0},
		data->ray_data.pos, MINDISTANCE);
		if (tries <= 0)
			return ((t_vec2){-1, -1});
		--tries;
	}
	return (pos2);
}