/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding_random_pos.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 11:46:59 by albaur            #+#    #+#             */
/*   Updated: 2022/11/05 15:15:59 by faventur         ###   ########.fr       */
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
	printf("%zu\n", random);
	while (i < random && i < data->enemy.valid_pos_n - 1)
		++i;
	return (data->enemy.valid_pos[i]);
}
