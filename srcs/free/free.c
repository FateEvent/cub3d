/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:36:16 by albaur            #+#    #+#             */
/*   Updated: 2022/11/09 13:07:16 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	free_n_exit(void *ptr)
{
	t_data	*data;

	data = ptr;
	mlx_close_window(data->mlx);
	mlx_terminate(data->mlx);
	free_audio(data);
	free_textures(data);
	free(data->map->minimap);
	free(data->ray_data.sprite.sprites);
	free(data->ray_data.sprite.sprite_order);
	free(data->ray_data.sprite.sprite_dist);
	free(data->ray_data.sprite.z_buffer);
	free(data->map->size_arr);
	free(data->map->map_str);
	free(data->enemy.valid_pos);
	free(data->map->floor_texture);
	free(data->map->ceiling_texture);
	free(data->map->north_texture);
	free(data->map->south_texture);
	free(data->map->east_texture);
	free(data->map->west_texture);
	ft_arr_freer(data->map->map);
	free(data->map);
	printf("exit\n");
	exit(0);
}
