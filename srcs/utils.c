/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:46:30 by faventur          #+#    #+#             */
/*   Updated: 2022/10/15 22:17:20 by faventur         ###   ########.fr       */
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

void	ft_my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	static int	octet;

	if (octet == 0)
		octet = img->bits_per_pixel / 8;
	*(unsigned int *)(img->pixels
			+ (y * img->line_size + x * 4)) = color;
}
