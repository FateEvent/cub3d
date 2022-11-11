/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:11:35 by albaur            #+#    #+#             */
/*   Updated: 2022/11/10 17:12:43 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	update_move(t_data *data)
{
	size_t	i;

	i = rand() % 5;
	if (data->hud.pos > 19)
		data->hud.pos = 0;
	if (data->hud.pos > 0)
		data->hud.sprites[data->hud.pos - 1].img->enabled = 0;
	else if (data->hud.pos == 0)
		data->hud.sprites[19].img->enabled = 0;
	data->hud.sprites[data->hud.pos].img->enabled = 1;
	++data->hud.pos;
	if (data->timestamp >= data->player.footstep_timestamp)
	{
		data->player.footstep_timestamp = data->timestamp + 0.8;
		ma_sound_start(&data->audio.footstep[i]);
	}
	else
		data->player.footstep_timestamp -= 0.4;
}
