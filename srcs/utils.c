/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:46:30 by faventur          #+#    #+#             */
/*   Updated: 2022/05/09 18:16:49 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

int	verify_conditions(char **map)
{
	t_vector	candy_pos;

	candy_pos = ft_get_x_and_y(map, 'C');
	if (candy_pos.x < 0)
		return (1);
	else
		return (0);
}

void	ft_prop_init(t_prop *obj)
{
	obj->item = 0;
	obj->exit = 0;
	obj->start_pos = 0;
}

t_vector	ft_get_coordinates(char **map, char prop)
{
	t_vector	coord;

	coord.x = 0;
	coord.y = 0;
	while (map[coord.y])
	{
		while (map[coord.y][coord.x])
		{
			if (map[coord.y][coord.x] == prop)
			{
				coord.y *= 65;
				coord.x *= 65;
				return (coord);
			}
			coord.x++;
		}
		coord.x = 0;
		coord.y++;
	}
	coord.x = -1;
	coord.y = -1;
	return (coord);
}

t_vector	ft_get_x_and_y(char **map, char prop)
{
	t_vector	coord;

	coord.x = 0;
	coord.y = 0;
	while (map[coord.y])
	{
		while (map[coord.y][coord.x])
		{
			if (map[coord.y][coord.x] == prop)
				return (coord);
			coord.x++;
		}
		coord.x = 0;
		coord.y++;
	}
	coord.x = -1;
	coord.y = -1;
	return (coord);
}

t_vector	ft_get_char_pos(char **map)
{
	t_vector	pos;

	pos = ft_get_x_and_y(map, 'P');
	if (pos.x == -1)
		pos = ft_get_x_and_y(map, 'L');
	if (pos.x == -1)
		pos = ft_get_x_and_y(map, 'F');
	if (pos.x == -1)
		pos = ft_get_x_and_y(map, 'B');
	return (pos);
}
