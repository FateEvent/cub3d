/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:36:16 by albaur            #+#    #+#             */
/*   Updated: 2022/11/09 19:37:41 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	free_n_exit(void *ptr)
{
	t_data	*data;

	data = ptr;
	mlx_close_window(data->mlx);
	mlx_terminate(data->mlx);
	ma_engine_uninit(data->audio.audio_engine);
	printf("exit\n");
	exit(0);
}
