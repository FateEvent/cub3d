/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils_pt2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 17:13:22 by albaur            #+#    #+#             */
/*   Updated: 2022/11/02 11:11:31 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

static void	check_map_char(char *map, int *count, char *str)
{
	if (str[2] == '\0')
	{
		if (map[0] == str[0] && map[1] == str[1])
			++*count;
	}
	else
	{
		if (map[0] == str[0] && map[1] == str[1] && map[2] == str[2])
			++*count;
	}
}

static void	check_map_batch(char *map, int *count)
{
	check_map_char(map, count, "NO ");
	check_map_char(map, count, "SO ");
	check_map_char(map, count, "WE ");
	check_map_char(map, count, "EA ");
	check_map_char(map, count, "FT ");
	check_map_char(map, count, "CT ");
	check_map_char(map, count, "F \0");
	check_map_char(map, count, "C \0");
}

char	**get_map_description(char **map)
{
	size_t	i;
	int		count;

	i = -1;
	count = 0;
	while (map[++i])
	{
		check_map_batch(map[i], &count);
		if (count == 6)
		{
			while (map[++i])
			{
				if (map[i][0] == '\n')
					continue ;
				if (ft_strstr(map[i], "1\0"))
					return (ft_arrdup(map + i));
				else
					return (NULL);
			}
		}
	}
	return (NULL);
}
