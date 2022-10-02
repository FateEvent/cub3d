/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 14:25:26 by faventur          #+#    #+#             */
/*   Updated: 2022/10/02 15:45:53 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The ft_map_reader() function opens the .ber files and creates an array
** of strings made up of the lines composing the file.
** 
** The ft_map_parser() function parses the map obtained by the reading of
** the .ber file and checks if it complies with the standards.
** 
** The ft_map_freer() function frees the memory allocated to each string
** of the array passed as a parameter and finally frees the array itself.
*/

#include "mlx_utils.h"

static int	ft_wall_parser(char **map)
{
	int		i;
	int		j;
	int		line;

	line = ft_strlen(map[0]) - 1;
	i = 0;
	j = -1;
	while (map[0][++j])
	{
		if (map[0][j] != '1')
			return (0);
	}
	while (map[++i])
	{
		if (map[i][0] != '1' || map[i][line] != '1')
			return (0);
	}
	j = -1;
	i--;
	while (map[i][++j])
	{
		if (map[i][j] != '1')
			return (0);
	}
	return (1);
}

static int	ft_start_pos_counter(char **map)
{
	int		i;
	int		j;
	t_prop	obj;

	i = 0;
	j = 0;
	ft_prop_init(&obj);
	while (map[i])
	{
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'W' || map[i][j] == 'E')
				obj.start_pos++;
			j++;
		}
		j = 0;
		i++;
	}
	if (obj.start_pos == 1)
		return (1);
	return (0);
}

int	ft_map_parser(char **map)
{
	int		i;
	size_t	line;

	line = ft_strlen(map[0]);
	i = 1;
	while (map[i])
	{
		if (ft_strlen(map[i]) != line)
		{
			ft_puterror("The map doesn't seem valid!");
			return (0);
		}
		i++;
	}
	if (ft_start_pos_counter(map) && ft_wall_parser(map))
		return (1);
	ft_puterror("The map doesn't seem valid!");
	return (0);
}

char	**ft_map_reader(char *filename)
{
	char	**arr;
	char	*buffer;
	char	*temp;
	int		fd;
	int		i;

	fd = open(filename, O_RDONLY);
	i = 0;
	buffer = malloc(sizeof(char) * 1);
	if (!buffer)
		return (NULL);
	buffer[0] = '\0';
	temp = buffer;
	while (42)
	{
		temp = get_next_line(fd);
		if (temp == NULL)
			break ;
		buffer = ft_strjoin(buffer, temp);
		free(temp);
	}
	arr = ft_split(buffer, '\n');
	free(buffer);
	close(fd);
	return (arr);
}
