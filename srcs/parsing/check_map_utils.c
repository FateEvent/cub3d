/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:27:38 by albaur            #+#    #+#             */
/*   Updated: 2022/10/07 15:08:24 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

static int invalid_check(char **map)
{
	size_t i;
	size_t j;
	size_t count;

	i = 0;
	count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != 'N' && map[i][j] != 'S' && map[i][j] != 'E'
					&& map[i][j] != 'W' && map[i][j] != '0' && map[i][j] != '1'
					&& map[i][j] != 32)
				++count;
			++j;
		}
		++i;
	}
	if (count != 0)
	{
		printf("Invalid character. Maps descriptions only accepts NSEW, spaces, 0 or 1.\n");
		return (-1);
	}
	else
		return (0);
}

static int	min_check(char **map)
{
	size_t	i;
	size_t	j;
	size_t	count;

	i = 0;
	count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
				++count;
			++j;
		}
		++i;
	}
	if (count != 1)
	{
		printf("Invalid player position. You must have only one position (N, S, E or W).\n");
		return (-1);
	}
	else
		return (0);
}

// static int	gap_check(char **map)
// {
// 	size_t	i;
// 	size_t	j;
// 	size_t	last_row;
// 	int		ret;

// 	i = 0;
// 	ret = 0;
// 	last_row = ft_arrlen(map) - 1;
// 	while (map[i])
// 	{
// 		j = 0;
// 		while (map[i][j])
// 		{
// 			if ((map[i][j] != '1' && i == 0) || (map[i][j] != '1' && i == last_row))
// 			{
// 				printf("i %zu j %zu\n", i, j);
// 				++ret;
// 			}
// 			if ((map[i][j] != '1' && j == 0) || (j == ft_strlen(map[i]) - 1 && map[i][j] != '1'))
// 			{
// 				printf("i %zu j %zu\n", i, j);
// 				++ret;
// 			}
// 			++j;
// 		}
// 		++i;
// 	}
// 	if (ret != 0)
// 	{
// 		printf("GAP_ERROR\n");
// 		return (-1);
// 	}
// 	return (0);
// }

static int	detect_gap(char **map, size_t i, size_t j)
{
	size_t	tmp;
	size_t	last_row;

	last_row = ft_arrlen(map) - 1;
	if (map[i][j] == ' ')
	{
		tmp = j;
		while (map[i][tmp] && j >= 0)
		{
			if (map[i][tmp] == '1')
				return (0);
			--tmp;
		}
		tmp = j;
		while (map[i][tmp] && j <= ft_strlen(map[i]) - 1)
		{
			if (map[i][tmp] == '1')
				return (0);
			++tmp;
		}
		tmp = i;
		while (map[tmp][j] && tmp >= 0)
		{
			if (map[tmp][j] == '1')
				return (0);
			--tmp;
		}
		tmp = i;
		while (map[tmp][j] && tmp <= last_row)
		{
			if (map[tmp][j] == '1')
				return (0);
			++tmp;
		}
		printf("i %zu j %zu\n", i, j);
	}
	return (-1);
}

static int	wall_check(char **map)
{
	size_t	i;
	size_t	j;
	size_t	last_row;
	int		ret;

	i = 0;
	ret = 0;
	last_row = ft_arrlen(map) - 1;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == ' ')
			{
				//if (detect_gap(map, i, j) == -1)
				//	++ret;
			}
			//if ((j == 0 && map[i][j] != '1') || (j == ft_strlen(map[i]) - 1 && map[i][j] != '1'))
			//	++ret;
			++j;
		}
		++i;
	}
	if (ret != 0)
	{
		printf("Invalid map description. Map must be surrounded by 1s (walls).\n");
		return (-1);
	}
	return (0);
}

int	check_map_components(char **map)
{
	if (min_check(map) == -1 || invalid_check(map) == -1 || wall_check(map) == -1)
		return (-1);
	return (0);
}
