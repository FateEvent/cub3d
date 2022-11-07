/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:05:15 by albaur            #+#    #+#             */
/*   Updated: 2022/11/07 15:49:28 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	draw_death(t_data *data)
{
	t_shape	background;

	background.height = HEIGHT;
	background.width = WIDTH;
	background.x = 0;
	background.y = 0;
	data->enemy.death_image = malloc(sizeof(t_image));
	data->enemy.death_image->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	draw_rect(data->enemy.death_image->img, background, 0x00000000);
	draw_rect(data->enemy.death_image->img, background, 0xFF000047);
	mlx_image_to_window(data->mlx, data->enemy.death_image->img, 0, 0);
	data->enemy.warning_image->texture = mlx_load_xpm42("images/dead.xpm42");
	data->enemy.alive = 0;
}