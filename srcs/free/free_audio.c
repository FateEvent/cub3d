/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_audio.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:26:09 by albaur            #+#    #+#             */
/*   Updated: 2022/11/09 12:38:07 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	free_audio(t_data *data)
{
	free_audio_behind_you(data);
	free_audio_footstep(data);
	free_audio_ambiance(data);
	free_audio_suspense(data);
	ma_engine_uninit(data->audio.audio_engine);
}
