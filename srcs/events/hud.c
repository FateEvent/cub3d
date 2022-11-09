/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:11:35 by albaur            #+#    #+#             */
/*   Updated: 2022/11/09 17:59:35 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	update_hud(t_data *data)
{
	if (data->hud.pos > 19)
		data->hud.pos = 0;
	if (data->hud.pos > 0)
		data->hud.sprites[data->hud.pos - 1].img->enabled = 0;
	else if (data->hud.pos == 0)
		data->hud.sprites[19].img->enabled = 0;
	data->hud.sprites[data->hud.pos].img->enabled = 1;
	++data->hud.pos;
}
