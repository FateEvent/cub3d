/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:48:22 by albaur            #+#    #+#             */
/*   Updated: 2022/10/14 16:31:04 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

static int	get_color(char *str, t_map *mapStruct, int mode)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	**colors;
	t_color	rgba;

	i = 2;
	j = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			++i;
		else if (ft_isascii(str[i]) == 1)
		{
			colors = ft_split(str + i, ',');
			if (ft_arrlen(colors) != 3)
			{
				freearr(colors);
				return (-1);
			}
			while (colors[j])
			{
				k = 0;
				while (colors[j][k])
				{
					if (ft_isdigit(colors[j][k]) != 1)
					{
						freearr(colors);
						return (-1);
					}
					++k;
				}
				++j;
			}
			rgba = (t_color){ft_atoi(colors[0]), ft_atoi(colors[1]), ft_atoi(colors[2]), 255};
			if (rgba.r < 0 || rgba.r > 255 || rgba.g < 0 || rgba.g > 255 || rgba.b < 0 || rgba.b > 255)
			{
				freearr(colors);
				return (-1);
			}
			if (mode == 0)
				mapStruct->floor_color = rgba;
			else if (mode == 1)
				mapStruct->ceiling_color = rgba;
			freearr(colors);
			return (0);
		}
		else
			return (-1);
	}
	return (-1);
}

static int	get_texture(char *str, t_map *mapStruct, int mode)
{
	size_t	i;
	char	*path;
	int		fd;

	i = 3;
	while (str[i])
	{
		if (str[i] == ' ')
			++i;
		else if (ft_isascii(str[i]))
		{
			path = malloc(sizeof(char) * (ft_strlen(str + i) + 1));
			if (!path)
				return (-1);
			ft_strcpy(path, str + i);
			if (!ft_strstr(path, ".xpm42\0"))
			{
				free(path);
				return (-1);
			}
			fd = open(path, O_RDONLY);
			if (fd == -1)
			{
				close(fd);
				free(path);
				return (-1);
			}
			close(fd);
			if (mode == 0)
				mapStruct->north_texture = path;
			else if (mode == 1)
				mapStruct->south_texture = path;
			else if (mode == 2)
				mapStruct->west_texture = path;
			else if (mode == 3)
				mapStruct->east_texture = path;
			return (0);
		}
	}
	return (-1);
}

int	check_map_settings(t_map *mapStruct, char **map)
{
	size_t	i;
	int		count;

	i = -1;
	count = 0;
	while (map[++i])
	{
		if (map[i][0] == '\n')
			continue ;
		if (ft_strlen(map[i]) < 3)
			return (-1);
		if (map[i][0] == 'N' && map[i][1] == 'O' && map[i][2] == ' ')
		{
			if (get_texture(map[i], mapStruct, 0) == -1)
				return (-1);
			++count;
		}
		else if (map[i][0] == 'S' && map[i][1] == 'O' && map[i][2] == ' ')
		{
			if (get_texture(map[i], mapStruct, 1) == -1)
				return (-1);
			++count;
		}
		else if (map[i][0] == 'W' && map[i][1] == 'E' && map[i][2] == ' ')
		{
			if (get_texture(map[i], mapStruct, 2) == -1)
				return (-1);
			++count;
		}
		else if (map[i][0] == 'E' && map[i][1] == 'A' && map[i][2] == ' ')
		{
			if (get_texture(map[i], mapStruct, 3) == -1)
				return (-1);
			++count;
		}
		else if (map[i][0] == 'F' && map[i][1] == ' ')
		{
			if (get_color(map[i], mapStruct, 0) == -1)
				return (-1);
			++count;
		}
		else if (map[i][0] == 'C' && map[i][1] == ' ')
		{
			if (get_color(map[i], mapStruct, 1) == -1)
				return (-1);
			++count;
		}
		else
		{
			if (count == 6)
				return (0);
			return (-1);
		}
	}
	return (0);
}

static char	**get_map_description(char **map)
{
	size_t	i;
	int		count;

	i = -1;
	count = 0;
	while (map[++i])
	{
		if (map[i][0] == 'N' && map[i][1] == 'O' && map[i][2] == ' ')
			++count;
		else if (map[i][0] == 'S' && map[i][1] == 'O' && map[i][2] == ' ')
			++count;
		else if (map[i][0] == 'W' && map[i][1] == 'E' && map[i][2] == ' ')
			++count;
		else if (map[i][0] == 'E' && map[i][1] == 'A' && map[i][2] == ' ')
			++count;
		else if (map[i][0] == 'F' && map[i][1] == ' ')
			++count;
		else if (map[i][0] == 'C' && map[i][1] == ' ')
			++count;
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

t_map	*check_map_integrity(char *path)
{
	t_map	*mapStruct;
	char	**map;

	mapStruct = malloc(sizeof(t_map));
	if (!mapStruct)
		throw_err_ex("Error : Cannot malloc map structure.");
	map = ft_map_reader(path);
	if (check_map_settings(mapStruct, map) == -1)
	{
		freearr(map);
		throw_err_ex("Error : Invalid map file.");
	}
	mapStruct->map = get_map_description(map);
	if (mapStruct->map == NULL)
	{
		freearr(map);
		throw_err_ex("Error : Invalid map file.");
	}
	if (check_map_components(mapStruct->map) == -1)
	{
		freearr(map);
		throw_err_ex("Error : Invalid map file.");
	}
	freearr(map);
	return (mapStruct);
}

void check_map_extension(char *argv[])
{
	int fd;

	if (!ft_strstr(argv[1], ".cub\0"))
		throw_err_ex("Error: Invalid file extension.");
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		close(fd);
		throw_err_ex("Error: Cannot open file.");
	}
	close(fd);
}