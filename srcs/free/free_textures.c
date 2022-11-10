/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:40:11 by albaur            #+#    #+#             */
/*   Updated: 2022/11/10 12:16:26 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

static void	free_texture(xpm_t *texture)
{
	if (texture)
	{
		free(texture->texture.pixels);
		free(texture);
	}
}

void	free_textures(t_data *data)
{
	ssize_t	i;

	i = -1;
	while (++i < 15)
	{
		if (data->ray_data.tex_buf[i])
			free(data->ray_data.tex_buf[i]);
		free_texture(data->textures[i].texture);
	}
	i = -1;
	while (++i < 20)
		free_texture(data->hud.sprites[i].texture);
	free(data->enemy.warning_text->texture->texture.pixels);
	free(data->enemy.warning_text->texture);
	free(data->ray_data.tex_buf);
	free(data->textures);
	free(data->enemy.warning_text);
	free(data->enemy.death_bg);
	free(data->enemy.death_text);
	free(data->hud.sprites);
}