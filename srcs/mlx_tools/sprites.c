/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 13:15:09 by albaur            #+#    #+#             */
/*   Updated: 2022/11/02 13:59:03 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	load_sprites(t_data *data, t_image *texture)
{
	size_t	i;

	i = 5;
	texture[6].texture = mlx_load_xpm42("images/smiler.xpm42");
	texture[7].texture = mlx_load_xpm42("images/greenlight.xpm42");
	texture[8].texture = mlx_load_xpm42("images/pillar.xpm42");
	if (!texture[6].texture || !texture[7].texture || !texture[8].texture)
		return ;
	tex_to_img(data, texture, 6);
	tex_to_img(data, texture, 7);
	tex_to_img(data, texture, 8);
	if (!texture[6].img || !texture[7].img || !texture[8].img)
		return ;
	while (++i < 9)
		data->ray_data.tex_buf[i] = uchar_to_arr(texture[i].img->pixels,
				texture[i].img->width, texture[i].img->height);
}
