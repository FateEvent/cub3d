/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_quest.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 10:34:11 by albaur            #+#    #+#             */
/*   Updated: 2022/11/16 16:44:12 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

static void	init_quest_textures(t_data *data)
{
	data->quest.pickup = malloc(sizeof(t_image));
	data->quest.exit_key = malloc(sizeof(t_image));
	data->quest.exit_screen = malloc(sizeof(t_image));
	if (!data->quest.pickup || !data->quest.exit_key || !data->quest.exit_screen)
		free_exit(data);
	data->quest.pickup->texture = mlx_load_xpm42("images/pickup.xpm42");
	data->quest.exit_key->texture = mlx_load_xpm42("images/exit_key.xpm42");
	data->quest.exit_screen->texture = mlx_load_xpm42("images/exit_screen.xpm42");
	data->quest.pickup->img = mlx_texture_to_image(data->mlx,
			&data->quest.pickup->texture->texture);
	data->quest.exit_key->img = mlx_texture_to_image(data->mlx,
			&data->quest.exit_key->texture->texture);
	data->quest.exit_screen->img = mlx_texture_to_image(data->mlx,
			&data->quest.exit_screen->texture->texture);
	if (!data->quest.pickup->texture || !data->quest.exit_key->texture
		|| !data->quest.exit_screen->texture)
		free_exit(data);
}

void	init_quest(t_data *data)
{
	size_t	i;
	size_t	j;

	i = -1;
	data->quest.n_pages = 0;
	while (data->map->map[++i])
	{
		j = -1;
		while (data->map->map[i][++j])
		{
			if (data->map->map[i][j] == '8')
				++data->quest.n_pages;
		}
	}
	init_quest_textures(data);
	data->quest.pickup->img->enabled = 0;
	data->quest.exit_key->img->enabled = 0;
	data->quest.exit_screen->img->enabled = 0;
	data->quest.n_pickup = 0;
	data->quest.done = 0;
}
