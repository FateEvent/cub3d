/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quest.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:07:19 by albaur            #+#    #+#             */
/*   Updated: 2022/11/16 16:48:24 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

static void	update_quest_hud(t_data *data)
{
	t_vec	pos;
	pos.x = data->ray_data.camera.pos.x + data->ray_data.camera.dir.x;
	pos.y = data->ray_data.camera.pos.y + data->ray_data.camera.dir.y;
	if (data->map->map[pos.y][pos.x] == '8')
	{
		data->quest.pickup->img->enabled = 1;
		if (data->key == MLX_KEY_E)
		{
			if (data->quest.n_pickup == 0)
				data->quest.exit_pos = pos;
			ma_sound_start(&data->audio.pickup);
			data->map->map[pos.y][pos.x] = '1';
			++data->quest.n_pickup;
		}
	}
	else
		data->quest.pickup->img->enabled = 0;
	if (data->map->map[pos.y][pos.x] == '9' && data->quest.done != 3)
	{
		data->quest.exit_key->img->enabled = 1;
		if (data->key == MLX_KEY_E)
		{
			data->quest.exit_key->img->enabled = 0;
			data->quest.exit_screen->img->enabled = 1;
			data->quest.done = 3;
			data->enemy.alive = 0;
		}
	}
	else if (data->quest.done != 3)
		data->quest.exit_key->img->enabled = 0;
}

void	update_quest(t_data *data)
{
	update_quest_hud(data);
	if (data->quest.done < 2 && data->quest.n_pages != 0
		&& data->quest.n_pages == data->quest.n_pickup)
	{
		if (data->quest.done == 0)
		{
			data->map->map[data->quest.exit_pos.y][data->quest.exit_pos.x] = '9';
			data->enemy.disable_ai = 1;
			data->ray_data.sprite.sprites[0].x = -1;
			data->ray_data.sprite.sprites[0].y = -1;
			ma_sound_stop(&data->audio.creeping_down);
			ma_sound_start(&data->audio.unraveled);
			data->quest.done = 1;
		}
		if (data->timer >= data->shading.timer + 0.025
			&& data->shading.shading_lock == 0 && data->shading.ratio < 2.5)
		{
			data->shading.timer = data->timer;
			data->shading.shading_lock = 1;
			data->shading.ratio += 0.035;
		}
		else if (data->timer >= data->shading.timer + 0.025)
			data->shading.shading_lock = 0;
		if (data->shading.ratio >= 2.5)
			data->quest.done = 2;
	}
}
