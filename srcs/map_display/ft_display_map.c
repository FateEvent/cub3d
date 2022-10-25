/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 12:07:41 by faventur          #+#    #+#             */
/*   Updated: 2022/10/24 17:19:54 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	ft_display_map(t_data *data, t_image *tile)
{
	t_var		var;
	char		c;

	ft_bzero(&var, sizeof(var));
	var.width = data->screen.resolution.x;
	var.height = data->screen.resolution.y;
	var.i = 0;
	printf("%d\n", var.i);
	while (var.i * tile->img->height < var.height && data->map->map[var.i])
	{
		printf("%d\n", var.i);
		var.j = 0;
		while (var.j * tile->img->width < var.width
			&& data->map->map[var.i][var.j] != '\n')
		{
			printf("%c", data->map->map[var.i][var.j]);
			c = data->map->map[var.i][var.j];
			if (c == '1')
				mlx_image_to_window(data->mlx, tile->img,
					var.j * (tile->img->width - 1), var.i * (tile->img->height - 1));
			var.j++;
		}
		printf("\n");
		var.i++;
	}
	printf("%d\n", var.i);
}
