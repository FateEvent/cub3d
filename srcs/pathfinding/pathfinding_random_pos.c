/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding_random_pos.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 11:46:59 by albaur            #+#    #+#             */
/*   Updated: 2022/11/07 11:14:35 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	pathfinding_list_pos(t_data *data)
{
	size_t		i;
	size_t		j;
	size_t		k;

	i = 0;
	k = 0;
	while (data->map->map[i])
	{
		j = 0;
		while (data->map->map[i][j])
		{
			if (data->map->map[i][j] == '0')
				++k;
			++j;
		}
		++i;
	}
	data->enemy.valid_pos_n = k;
	data->enemy.valid_pos = malloc(sizeof(t_vec) * k);
	i = 0;
	k = 0;
	while (data->map->map[i])
	{
		j = 0;
		while (data->map->map[i][j])
		{
			if (data->map->map[i][j] == '0')
			{
				data->enemy.valid_pos[k] = (t_vec){j, i};
				++k;
			}
			++j;
		}
		++i;
	}
}

t_vec	pathfinding_get_pos(t_data *data)
{
	size_t	i;
	size_t	random;

	i = 0;
	random = rand() % (data->enemy.valid_pos_n - 1);
	while (i < random && i < data->enemy.valid_pos_n - 1)
		++i;
	return (data->enemy.valid_pos[i]);
}

t_vec2	pathfinding_pos_dist(t_data *data, t_vec2 start, t_vec2 end, size_t min)
{
	double	dist;
	t_vec	tmp;
	t_vec2	new;

	dist = -1;
	while (dist == -1 || dist > min)
	{
		tmp = pathfinding_get_pos(data);
		new = (t_vec2){tmp.x + 0.5, tmp.y + 0.5};
		dist = ft_vect2_distance_calc(new, end);
		if (new.x == start.x && new.y == start.y)
			dist = -1;
	}
	return (new);
}
