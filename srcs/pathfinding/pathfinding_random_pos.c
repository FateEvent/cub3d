/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding_random_pos.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 11:46:59 by albaur            #+#    #+#             */
/*   Updated: 2022/11/04 17:10:23 by albaur           ###   ########.fr       */
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
	data->enemy.valid_pos = malloc(sizeof(t_vector3) * k);
	i = 0;
	k = 0;
	while (data->map->map[i])
	{
		j = 0;
		while (data->map->map[i][j])
		{
			if (data->map->map[i][j] == '0')
			{
				data->enemy.valid_pos[k] = (t_vector3){j, i};
				++k;
			}
			++j;
		}
		++i;
	}
}

t_vector3	pathfinding_get_pos(t_data *data)
{
	size_t	i;
	size_t	random;

	i = 0;
	random = rand() % (data->enemy.valid_pos_n - 1);
	printf("%zu\n", random);
	while (i < random && i < data->enemy.valid_pos_n - 1)
		++i;
	return (data->enemy.valid_pos[i]);
}
