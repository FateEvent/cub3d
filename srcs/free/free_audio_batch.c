/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_audio_batch.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:09:12 by albaur            #+#    #+#             */
/*   Updated: 2022/11/11 12:50:51 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	free_audio_behind_you(t_data *data)
{
	ma_sound_uninit(&data->audio.behind_you[0]);
	ma_sound_uninit(&data->audio.behind_you[1]);
	ma_sound_uninit(&data->audio.behind_you[2]);
	ma_sound_uninit(&data->audio.behind_you[3]);
}

void	free_audio_footstep(t_data *data)
{
	ma_sound_uninit(&data->audio.footstep[0]);
	ma_sound_uninit(&data->audio.footstep[1]);
	ma_sound_uninit(&data->audio.footstep[2]);
	ma_sound_uninit(&data->audio.footstep[3]);
	ma_sound_uninit(&data->audio.footstep[4]);
}

void	free_audio_ambiance(t_data *data)
{
	ma_sound_uninit(&data->audio.ambiance);
	ma_sound_uninit(&data->audio.dead[0]);
	ma_sound_uninit(&data->audio.dead[1]);
	ma_sound_uninit(&data->audio.scare);
	ma_sound_uninit(&data->audio.death[0]);
	ma_sound_uninit(&data->audio.death[1]);
	ma_sound_uninit(&data->audio.smiler[0]);
	ma_sound_uninit(&data->audio.smiler[1]);
	ma_sound_uninit(&data->audio.geiger);
	ma_sound_uninit(&data->audio.creeping_down);
	ma_sound_uninit(&data->audio.unraveled);
}

void	free_audio_suspense(t_data *data)
{
	ssize_t		i;

	i = -1;
	while (++i < 14)
		ma_sound_uninit(&data->audio.suspense[i]);
}
