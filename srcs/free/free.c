/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:36:16 by albaur            #+#    #+#             */
/*   Updated: 2022/11/09 13:07:16 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	free_n_exit(void *ptr)
{
	t_data	*data;

	data = ptr;
	mlx_close_window(data->mlx);
	mlx_terminate(data->mlx);
	free_audio(data);
	free_textures(data);
	printf("exit\n");
	exit(0);
}
