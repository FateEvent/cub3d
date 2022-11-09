/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:53:14 by albaur            #+#    #+#             */
/*   Updated: 2022/11/09 17:11:00 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

static void	update_jumpscare_pos(t_data *data, ssize_t i)
{
	t_vec2	pos;

	pos = pathfinding_pos_close(data, data->ray_data.pos, 2);
	data->ray_data.sprite.sprites[i].x = pos.x;
	data->ray_data.sprite.sprites[i].y = pos.y;
	if (i == 1)
		ma_sound_start(&data->audio.behind_you[3]);
	else
		ma_sound_start(&data->audio.behind_you[rand() % 3]);
}

static void	update_jumpscare(t_data *data)
{
	ssize_t	i;

	i = rand() % 2;
	if (i == 0)
		i = 2;
	if (data->timer > 2 && data->timer % 90 == 0 && data->enemy.lock == 0)
	{
		if (rand() % 2)
		{
			if (data->ray_data.sprite.sprites[i].x == -1
				&& data->ray_data.sprite.sprites[i].y == -1)
				update_jumpscare_pos(data, i);
			data->enemy.lock = 1;
		}
	}
}

static int	is_wasd(t_data *data)
{
	if (data->key == (keys_t)MLX_KEY_W || data->key == (keys_t)MLX_KEY_A
		|| data->key == (keys_t)MLX_KEY_S || data->key == (keys_t)MLX_KEY_D)
		return (0);
	return (1);
}

int	update_events(t_data *data)
{
	if (!data->enemy.alive)
	{
		key_input(data);
		return (1);
	}
	if (data->time == 0)
		init_hud_draw(data);
	if (!is_wasd(data))
		update_hud(data);
	if (data->enemy.kill_countdown <= 0 && data->enemy.disable_ai == 0 && data->enemy.alive == 1)
		draw_death(data);
	update_enemy(data, &data->ray_data);
	update_jumpscare(data);
	if (data->timer % 90 != 0 && data->enemy.lock == 1)
		data->enemy.lock = 0;
	if (data->timer > 2 && data->timer % 60 == 0 && data->audio.lock == 0)
	{
		data->audio.lock = 1;
		ma_sound_start(&data->audio.suspense[rand() % 14]);
	}
	if (data->timer % 60 != 0 && data->audio.lock == 1)
		data->audio.lock = 0;
	return (0);
}
