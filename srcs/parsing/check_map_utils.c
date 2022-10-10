/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:27:38 by albaur            #+#    #+#             */
/*   Updated: 2022/10/10 15:17:15 by albaur           ###   ########.fr       */
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
					&& map[i][j] != ' ')
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

static int	space_check(char **map, ssize_t i, ssize_t j)
{
	size_t	tmp;

	tmp = j;
	while (map[i][tmp] && tmp >= 0)
	{
		if (map[i][tmp] == '1')
			return (0);
		--tmp;
	}
	tmp = j;
	while (map[i][tmp] && tmp <= ft_strlen(map[i]) - 1)
	{
		if (map[i][tmp] == '1')
			return (0);
		++tmp;
	}
	return (-1);
}

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

static int	wall_check(char **map)
{
	ssize_t	i;
	ssize_t	j;
	ssize_t	last_row;

	i = -1;
	j = 0;
	last_row = ft_arrlen(map) - 1;
	while (map[0][++i]) //premiere ligne
	{
		if (map[0][i] == '1' || (map[0][i] == ' ' && !space_check(map, 0, i)))
			continue ;
		return (-1);
	}
	i = -1;
	while (map[last_row][++i]) // derniere ligne
	{
		if (map[last_row][i] == '1' || (map[last_row][i] == ' ' && !space_check(map, last_row, i)))
			continue ;
		return (-1);
	}
	while (map[j]) // premier et dernier char sont des 1
	{
		i = -1;
		while (map[j][++i])
		{
			if (!wall_check_first(map[j]) && map[j][ft_strlen(map[j]) - 1] == '1')
				continue ;
			return (-1);
		}
		++j;
	}
	return (0);
}

static int	gap_check_reverse(char **map, ssize_t i, ssize_t j)
{
	ssize_t	k;

	k = j;
	while (k >= 0)
	{
		if (map[i][k] == '1')
		{
			if (i == 0)
			{
				if (map[i + 1][k] == '1')
					return (0);
				else
					return (-1);
			}
			else
			{
				if (map[i - 1][k] == '1')
					return (0);
				else if (i < ft_arrlen(map) - 1 && map[i + 1][k] == '1')
					return (0);
				else
					return (-1);
			}
		}
		--k;
	}
	return (0);
}

static int	gap_check(char **map)
{
	ssize_t	i;
	ssize_t	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == ' ')
			{
				if (j < (ssize_t)ft_strlen(map[i]) - 1 && map[i][j + 1] == ' ')
					continue ;
				if (j < (ssize_t)ft_strlen(map[i]) - 1 && map[i][j + 1] == '1')
				{
					if (i == 0)
					{
						if (j < (ssize_t)ft_strlen(map[i + 1]) - 1 && map[i + 1][j + 1] == '1')
						{
							if (!gap_check_reverse(map, i, j))
								continue ;
						}
					}
					else
					{
						if (j < (ssize_t)ft_strlen(map[i - 1]) - 1 && map[i - 1][j + 1] == '1')
						{
							if (!gap_check_reverse(map, i, j))
								continue ;
						}
						if (j < (ssize_t)ft_strlen(map[i - 1]) - 1 && i < ft_arrlen(map) - 1 && map[i + 1][j + 1] == '1')
						{
							if (!gap_check_reverse(map, i, j))
								continue ;
						}
					}
				}
				return (-1);
			}
		}
	}
	return (0);
}

static int	hole_check(char **map)
{
	size_t	i;
	size_t	j;
	size_t	al;
	int		ret;

	i = -1;
	al = ft_arrlen(map) - 1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			ret = 0;
			if (map[i][j] == '0')
			{
				if (j > 0 && (map[i][j - 1] == '0' || map[i][j - 1] == '1' || map[i][j - 1] == 'S'))
					++ret;
				if (j < ft_strlen(map[i]) - 1 && (map[i][j + 1] == '0' || map[i][j + 1] == '1' || map[i][j + 1] == 'S'))
					++ret;
				if (i > 0 && (map[i - 1][j] == '0' || map[i - 1][j] == '1' || map[i - 1][j] == 'S'))
					++ret;
				if (i < al && (map[i + 1][j] == '0' || map[i + 1][j] == '1' || map[i + 1][j] == 'S'))
					++ret;
				if (i > 0 && j > 0 && (map[i - 1][j - 1] == '0' || map[i - 1][j - 1] == '1' || map[i - 1][j - 1] == 'S'))
					++ret;
				if (i > 0 && j < ft_strlen(map[i]) - 1 && (map[i - 1][j + 1] == '0' || map[i - 1][j + 1] == '1' || map[i - 1][j + 1] == 'S'))
					++ret;
				if (i < al && j > 0 && (map[i + 1][j - 1] == '0' || map[i + 1][j - 1] == '1' || map[i + 1][j - 1] == 'S'))
					++ret;
				if (i < al && j < ft_strlen(map[i]) - 1 && (map[i + 1][j + 1] == '0' || map[i + 1][j + 1] == '1' || map[i + 1][j + 1] == 'S'))
					++ret;
			}
			if (map[i][j] == '0' && ret != 8)
			{
				printf ("ret %i\n", ret);
				printf ("i %zu j %zu = %c\n", i, j, map[i][j]);
				return (-1);
			}
		}
	}
	return (0);
}

int	check_map_components(char **map)
{
	if (min_check(map) == -1 || invalid_check(map) == -1)
		return (-1);
	if (wall_check(map) == -1)
	{
		printf("Invalid map description. Map must be surrounded by 1s (walls).\n");
		return (-1);
	}
	if (gap_check(map) == -1)
	{
		printf("Invalid map description. Error between gaps.\n");
		return (-1);
	}
	if (hole_check(map) == -1)
	{
		printf("Invalid map description. There is holes in your map.\n");
		return (-1);
	}
	return (0);
}
