/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 12:07:41 by faventur          #+#    #+#             */
/*   Updated: 2022/10/24 14:43:38 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"
/*
void	ft_display_map(t_image *img, t_map *map)
{
	t_var	var;
	char	c;

	var.width = img->size.x;
	var.height = img->size.y;
	var.i = 0;
	while (var.i * 2 < var.height && map->map[var.i])
	{
		var.j = 0;
		while (var.j * 2 < var.width
			&& map->map[var.i][var.j] != '\n')
		{
			c = map->map[var.i][var.j];
			if (c >= '1' && c <= '3')
				mlx_draw_square(img->img, var.width,
					var.height, 0xFF6676FF);
			var.j++;
		}
		var.i++;
	}
}
*/