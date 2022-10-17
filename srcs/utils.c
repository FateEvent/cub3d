/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:46:30 by faventur          #+#    #+#             */
/*   Updated: 2022/10/17 11:27:51 by faventur         ###   ########.fr       */
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

uint32_t	**hex_buf_creator(uint32_t *arr, size_t width, size_t height)
{
	uint32_t	**hex_buf;
	size_t		i;
	size_t		j;
	size_t		k;

	if (!arr)
		return (NULL);
	hex_buf = malloc(sizeof(uint32_t *) * height);
	i = 0;
	k = 0;
	while (i < height && k < height * width)
	{
		hex_buf[i] = malloc(sizeof(uint32_t) * width);
		j = 0;
		while (j < width && k < height * width)
		{
			hex_buf[i][j] = arr[k];
//			ft_printf("%d\n", hex_buf[i][j]);
			j++;
			k++;
		}
		i++;
	}
	return (hex_buf);
}

t_color	**rgb_buf_creator(uint32_t **buf, size_t width, size_t height)
{
	t_color	**rgb_buf;
	size_t	i;
	size_t	j;

	if (!buf)
		return (NULL);
	rgb_buf = (t_color **)malloc(sizeof(t_color *) * height);
	i = 0;
	while (i < height)
	{
		rgb_buf[i] = (t_color *)malloc(sizeof(t_color) * width);
		j = 0;
		while (j < width)
		{
			rgb_buf[i][j] = hex_to_rgb(buf[i][j]);
			ft_printf("%d\n", rgb_to_hex(rgb_buf[i][j]));
			j++;
		}
		i++;
	}
	return (rgb_buf);
}

uint32_t	**ft_from_uchar_to_hex_buf(unsigned char *arr, size_t width, size_t height)
{
	uint32_t	*hex_arr;
	uint32_t	**hex_buf;

	hex_arr = ft_from_uchar_to_hex_arr(arr, width, height);
	hex_buf = hex_buf_creator(hex_arr, width, height);
	free(hex_arr);
	return (hex_buf);
}

t_color	**ft_from_uchar_to_rgb_buf(unsigned char *arr, size_t width, size_t height)
{
	uint32_t	*hex_arr;
	uint32_t	**hex_buf;
	t_color		**rgb_buf;

	hex_arr = ft_from_uchar_to_hex_arr(arr, width, height);
	hex_buf = hex_buf_creator(hex_arr, width, height);
	rgb_buf = rgb_buf_creator(hex_buf, width, height);
	free(hex_arr);
	free_uint_arr(hex_buf);
	return (rgb_buf);
}