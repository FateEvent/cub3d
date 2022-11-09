/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_audio.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 22:25:05 by albaur            #+#    #+#             */
/*   Updated: 2022/11/09 15:31:32 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	init_audio(t_data *data)
{
	ssize_t		i;
	ma_result	result;
	char		base[15];
	char		*str;

	i = -1;
	ft_strcpy(base, "audio/suspense");
	data->audio.audio_engine = malloc(sizeof(ma_engine));
	data->audio.suspense = malloc(sizeof(ma_sound) * 14);
	data->audio.footstep = malloc(sizeof(ma_sound) * 5);
	data->audio.dead_ambiance = malloc(sizeof(ma_sound) * 2);
	data->audio.dead = malloc(sizeof(ma_sound) * 2);
	data->audio.smiler = malloc(sizeof(ma_sound) * 2);
	data->audio.behind_you = malloc(sizeof(ma_sound) * 4);
	if (!data->audio.audio_engine)
		throw_err_ex("Malloc error");
	result = ma_engine_init(NULL, data->audio.audio_engine);
    if (result != MA_SUCCESS)
		throw_err_ex("Audio initialization error");
	result += ma_sound_init_from_file(data->audio.audio_engine,
		"audio/ambiance.flac", 0, NULL, NULL, &data->audio.ambiance);
	result += ma_sound_init_from_file(data->audio.audio_engine,
		"audio/dead1.flac", 0, NULL, NULL, &data->audio.dead[0]);
	result += ma_sound_init_from_file(data->audio.audio_engine,
		"audio/dead2.flac", 0, NULL, NULL, &data->audio.dead[1]);
	result += ma_sound_init_from_file(data->audio.audio_engine,
		"audio/scare.flac", 0, NULL, NULL, &data->audio.scare);
	result += ma_sound_init_from_file(data->audio.audio_engine,
		"audio/dead_ambiance1.flac", 0, NULL, NULL, &data->audio.dead_ambiance[0]);
	result += ma_sound_init_from_file(data->audio.audio_engine,
		"audio/dead_ambiance2.flac", 0, NULL, NULL, &data->audio.dead_ambiance[1]);
	result += ma_sound_init_from_file(data->audio.audio_engine,
		"audio/footstep1.flac", 0, NULL, NULL, &data->audio.footstep[0]);
	result += ma_sound_init_from_file(data->audio.audio_engine,
		"audio/footstep2.flac", 0, NULL, NULL, &data->audio.footstep[1]);
	result += ma_sound_init_from_file(data->audio.audio_engine,
		"audio/footstep3.flac", 0, NULL, NULL, &data->audio.footstep[2]);
	result += ma_sound_init_from_file(data->audio.audio_engine,
		"audio/footstep4.flac", 0, NULL, NULL, &data->audio.footstep[3]);
	result += ma_sound_init_from_file(data->audio.audio_engine,
		"audio/footstep5.flac", 0, NULL, NULL, &data->audio.footstep[4]);
	result += ma_sound_init_from_file(data->audio.audio_engine,
		"audio/smiler1.flac", 0, NULL, NULL, &data->audio.smiler[0]);
	result += ma_sound_init_from_file(data->audio.audio_engine,
		"audio/smiler2.flac", 0, NULL, NULL, &data->audio.smiler[1]);
	result += ma_sound_init_from_file(data->audio.audio_engine,
		"audio/behindyou1.flac", 0, NULL, NULL, &data->audio.behind_you[0]);
	result += ma_sound_init_from_file(data->audio.audio_engine,
		"audio/behindyou2.flac", 0, NULL, NULL, &data->audio.behind_you[1]);
	result += ma_sound_init_from_file(data->audio.audio_engine,
		"audio/behindyou3.flac", 0, NULL, NULL, &data->audio.behind_you[2]);
	result += ma_sound_init_from_file(data->audio.audio_engine,
		"audio/behindyou4.flac", 0, NULL, NULL, &data->audio.behind_you[3]);
	while (++i < 14)
	{
		str = ft_strjoin(base, ft_itoa(i + 1));
		str = ft_concat(str, ".flac");
		result += ma_sound_init_from_file(data->audio.audio_engine,
			str, 0, NULL, NULL, &data->audio.suspense[i]);
		free(str);
	}
	if (result != MA_SUCCESS)
		throw_err_ex("Audio file initialization error");
	ma_sound_set_looping(&data->audio.ambiance, 1);
	ma_sound_set_looping(&data->audio.scare, 0);
	data->audio.lock = 0;
}