/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 12:29:32 by albaur            #+#    #+#             */
/*   Updated: 2022/11/10 11:26:37 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	init_minimap(t_data *data)
{
	data->map->minimap = malloc(sizeof(t_minimap));
	if (!data->map->minimap)
		throw_err_ex("Malloc error");
	data->map->minimap->img = NULL;
	data->map->minimap->img = mlx_new_image(data->mlx, 210, 150);
	if (!data->map->minimap->img)
		throw_err_ex("Error : Creating new MLX image failed.");
	data->map->minimap->pos.x = data->ray_data.camera.pos.x;
	data->map->minimap->pos.y = data->ray_data.camera.pos.y;
}
