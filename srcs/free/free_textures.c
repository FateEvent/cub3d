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

	i = -1;
	while (++i < 20)
	{
		if (i < 19)
		{
			if (i > 8)
				free(data->ray_data.tex_buf[i]);
		}
		if (&data->hud.sprites[i])
		{
			free(&data->hud.sprites[i]);
		}
	}
	free(data->ray_data.tex_buf);
	free(data->textures);
	free(data->enemy.warning_text);
	free(data->enemy.death_bg);
	free(data->enemy.death_text);
}