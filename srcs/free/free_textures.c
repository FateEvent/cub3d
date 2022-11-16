/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:40:11 by albaur            #+#    #+#             */
/*   Updated: 2022/11/16 10:25:47 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	free_textures(t_data *data)
{
	ssize_t	i;

	i = -1;
	while (++i < 16)
	{
		if (data->map->mode == -1 && (i == 4 || i == 5))
			continue ;
		free(data->ray_data.tex_buf[i]);
		mlx_delete_xpm42(data->textures[i].texture);
	}
	i = -1;
	while (++i < 20)
		mlx_delete_xpm42(data->hud.sprites[i].texture);
	mlx_delete_xpm42(data->enemy.warning_text->texture);
	if (data->enemy.death_text)
		mlx_delete_xpm42(data->enemy.death_text->texture);
	free(data->ray_data.tex_buf);
	free(data->textures);
	free(data->enemy.warning_text);
	free(data->enemy.death_bg);
	free(data->enemy.death_text);
	free(data->hud.sprites);
}
