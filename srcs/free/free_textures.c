/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:40:11 by albaur            #+#    #+#             */
/*   Updated: 2022/11/09 13:17:52 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	free_textures(t_data *data)
{
	ssize_t	i;

	i = 0;
	while (++i < 20)
	{
		if (i < 19)
		{
			mlx_delete_texture(&data->textures->texture[i].texture);
			mlx_delete_image(data->mlx, &data->textures->img[i]);
			mlx_delete_xpm42(&data->textures->texture[i]);
			free(data->ray_data.tex_buf[i]);
		}
		mlx_delete_texture(&data->hud.sprites->texture[i].texture);
		mlx_delete_xpm42(data->hud.sprites[i].texture);
		free(&data->hud.sprites[i]);
		
	}
	free(data->ray_data.tex_buf);
	free(data->textures);
	free(data->hud.sprites);
	mlx_delete_image(data->mlx, data->enemy.warning_text->img);
	mlx_delete_xpm42(data->enemy.warning_text->texture);
	free(data->enemy.warning_text);
}