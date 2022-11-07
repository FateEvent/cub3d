/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 13:15:09 by albaur            #+#    #+#             */
/*   Updated: 2022/11/07 16:07:18 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	load_sprites(t_data *data, t_image *texture)
{
	size_t	i;

	i = 5;
	texture[6].texture = mlx_load_xpm42("images/smiler.xpm42");
	texture[7].texture = mlx_load_xpm42("images/selena.xpm42");
	texture[8].texture = mlx_load_xpm42("images/yoshie.xpm42");
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

void	ft_load_fireset_textures(t_data *data, t_image *texture)
{
	size_t	i;

	i = 8;
	texture[9].texture = mlx_load_xpm42("images/fs/fire_door.xpm42");
	texture[10].texture = mlx_load_xpm42("images/fs/fire_door2.xpm42");
	texture[11].texture = mlx_load_xpm42("images/fs/fire_door3.xpm42");
	texture[12].texture = mlx_load_xpm42("images/fs/fire_door4.xpm42");
	texture[13].texture = mlx_load_xpm42("images/fs/fire_door5.xpm42");
	texture[14].texture = mlx_load_xpm42("images/fs/fire_door6.xpm42");
	texture[15].texture = mlx_load_xpm42("images/fs/fire_door7.xpm42");
	texture[16].texture = mlx_load_xpm42("images/fs/fire_door8.xpm42");
	texture[17].texture = mlx_load_xpm42("images/fs/fire_door9.xpm42");
	texture[18].texture = mlx_load_xpm42("images/fs/fire_door10.xpm42");
	data->enemy.warning_text->texture = mlx_load_xpm42("images/run.xpm42");
	if (!texture[9].texture || !texture[10].texture || !texture[11].texture
		|| !texture[12].texture || !texture[13].texture || !texture[14].texture
		|| !texture[15].texture || !texture[16].texture || !texture[17].texture
		|| !texture[18].texture)
		return ;
	tex_to_img(data, texture, 9);
	tex_to_img(data, texture, 10);
	tex_to_img(data, texture, 11);
	tex_to_img(data, texture, 12);
	tex_to_img(data, texture, 13);
	tex_to_img(data, texture, 14);
	tex_to_img(data, texture, 15);
	tex_to_img(data, texture, 16);
	tex_to_img(data, texture, 17);
	tex_to_img(data, texture, 18);
	data->enemy.warning_text->img = mlx_texture_to_image(data->mlx,
		&data->enemy.warning_text->texture->texture);
	if (!texture[9].img || !texture[10].img || !texture[11].img
		|| !texture[12].img || !texture[13].img || !texture[14].img
		|| !texture[15].img || !texture[16].img || !texture[17].img
		|| !texture[18].img)
		return ;
	while (++i < 19)
		data->ray_data.tex_buf[i] = uchar_to_arr(texture[i].img->pixels,
				texture[i].img->width, texture[i].img->height);
}
