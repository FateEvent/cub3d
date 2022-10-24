/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:27:38 by albaur            #+#    #+#             */
/*   Updated: 2022/10/24 11:18:44 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

static int	min_check(char **map)
{
	size_t	i;
	size_t	j;
	size_t	count;

	i = -1;
	count = 0;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
				++count;
		}
	}
	if (count != 1)
	{
		printf("Invalid player position.\n");
		return (-1);
	}
	return (0);
}

int	space_check(char **map, ssize_t i, ssize_t j)
{
	ssize_t	tmp;

	tmp = j;
	while (tmp >= 0 && map[i][tmp])
	{
		if (map[i][tmp] == '1')
			return (0);
		--tmp;
	}
	tmp = j;
	while (map[i][tmp] && tmp <= (ssize_t)ft_strlen(map[i]) - 1)
	{
		if (map[i][tmp] == '1')
			return (0);
		++tmp;
	}
	return (-1);
}

int	check_map_components(char **map)
{
	if (min_check(map) == -1 || invalid_check(map) == -1)
		return (-1);
	if (wall_check(map) == -1)
	{
		printf("Invalid map description. The map must be surrounded by walls.\n");
		return (-1);
	}
	if (gap_check(map) == -1)
	{
		printf("Invalid map description. Error between gaps.\n");
		return (-1);
	}
	if (hole_check(map) == -1)
	{
		printf("Invalid map description. There are holes in your map.\n");
		return (-1);
	}
	return (0);
}
