/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 17:56:23 by albaur            #+#    #+#             */
/*   Updated: 2022/10/14 17:57:01 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

static int	wall_check_first(char *map)
{
	size_t	i;

	i = 0;
	while (map[i])
	{
		if (map[i] == ' ')
			++i;
		else if (map[i] == '1')
			break ;
		else
			return (-1);
	}
	return (0);
}

static int	wall_check_both(char **map, ssize_t i, ssize_t j)
{
	while (map[j])
	{
		i = -1;
		while (map[j][++i])
		{
			if (!wall_check_first(map[j])
				&& map[j][ft_strlen(map[j]) - 1] == '1')
				continue ;
			return (-1);
		}
		++j;
	}
	return (0);
}

int	wall_check(char **map)
{
	ssize_t	i;
	ssize_t	j;
	ssize_t	last_row;

	i = -1;
	j = 0;
	last_row = ft_arrlen(map) - 1;
	while (map[0][++i])
	{
		if (map[0][i] == '1' || (map[0][i] == ' ' && !space_check(map, 0, i)))
			continue ;
		return (-1);
	}
	i = -1;
	while (map[last_row][++i])
	{
		if (map[last_row][i] == '1' || (map[last_row][i] == ' '
			&& !space_check(map, last_row, i)))
			continue ;
		return (-1);
	}
	if (wall_check_both(map, i, j) == -1)
		return (-1);
	return (0);
}
