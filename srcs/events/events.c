/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:53:14 by albaur            #+#    #+#             */
/*   Updated: 2022/11/10 11:25:33 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

static void	update_jumpscare_pos(t_data *data, ssize_t i)
{
	t_vec2	pos;

	pos = pathfinding_pos_close(data, data->ray_data.camera.pos, 2);
	data->ray_data.sprite.sprites[i].x = pos.x;
	data->ray_data.sprite.sprites[i].y = pos.y;
	if (i == 1)
	{
		data->enemy.selena_timer = data->timer;
		ma_sound_start(&data->audio.behind_you[3]);
	}
	else
	{
		data->enemy.yoshie_timer = data->timer;
		ma_sound_start(&data->audio.behind_you[rand() % 3]);
	}
}

static void	update_jumpscare_hide(t_data *data)
{
	if (data->timer >= data->enemy.selena_timer + 10)
	{
		data->ray_data.sprite.sprites[1].x = -1;
		data->ray_data.sprite.sprites[1].y = -1;
	}
	if (data->timer >= data->enemy.yoshie_timer + 10)
	{
		data->ray_data.sprite.sprites[2].x = -1;
		data->ray_data.sprite.sprites[2].y = -1;
	}
}

static void	update_jumpscare(t_data *data)
{
	ssize_t	i;

	i = rand() % 2;
	if (i == 0)
		i = 2;
	update_jumpscare_hide(data);
	if (data->timer > JUMPSCARE_FREQ - 1 && data->timer % JUMPSCARE_FREQ == 0
		&& data->enemy.lock == 0)
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
	if (data->enemy.kill_countdown <= 0 && data->enemy.disable_ai == 0
		&& data->enemy.alive == 1)
		draw_death(data);
	update_enemy(data, &data->ray_data);
	update_jumpscare(data);
	if (data->timer % JUMPSCARE_FREQ != 0 && data->enemy.lock == 1)
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
