/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:46:30 by faventur          #+#    #+#             */
/*   Updated: 2022/10/16 17:45:18 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	ft_uchar_arr_display(unsigned char *arr, size_t size)
{
	size_t	i;

	if (!arr)
		return ;
	i = 0;
	while (i < size)
	{
		ft_printf("%d\n", arr[i]);
		i++;
	}
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
	coord.x = 3000;
	coord.y = 3000;
	return (coord);
}

uint32_t	*ft_from_uchar_to_hex_arr(unsigned char *arr, size_t width, size_t height)
{
	uint32_t	*hex_arr;
	size_t		i;
	size_t		j;

	if (!arr)
		return (NULL);
	hex_arr = malloc(sizeof(uint32_t) * width * height);
	i = 0;
	j = 0;
	while (i < width * height * 4 && j < width * height)
	{
		hex_arr[j] = get_rgba(arr[i], arr[i + 1], arr[i + 2], arr[i + 3]);
//		ft_printf("%d\n", hex_arr[j]);
		i += 4;
		j++;
	}
	return (hex_arr);
}
