/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:42:39 by albaur            #+#    #+#             */
/*   Updated: 2022/11/08 17:07:21 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	init_enemy_texture(t_data *data, t_image *texture)
{
	size_t	i;

	i = 5;
	texture[6].texture = mlx_load_xpm42("images/smiler.xpm42");
	texture[7].texture = mlx_load_xpm42("images/selena.xpm42");
	texture[8].texture = mlx_load_xpm42("images/yoshie.xpm42");
	if (!texture[6].texture || !texture[7].texture || !texture[8].texture)
		throw_err_ex("Malloc error");
	while (++i < 9)
	{
		tex_to_img(data, texture, i);
		if (!texture[i].img)
			throw_err_ex("Malloc error");
		data->ray_data.tex_buf[i] = uchar_to_arr(texture[i].img->pixels,
				texture[i].img->width, texture[i].img->height);
	}
}

void	init_door_texture(t_data *data, t_image *texture)
{
	ssize_t	i;
	char	base[20];
	char	*str;

	i = -1;
	ft_strcpy(base, "images/fs/fire_door");
	while (++i < 10)
	{
		str = ft_strdup("images/fs/fire_door");
		str = ft_concat(str, ft_itoa(i + 1));
		str = ft_concat(str, ".xpm42");
		texture[i + 9].texture = mlx_load_xpm42(str);
		if (!texture[i + 9].texture)
			throw_err_ex("Malloc error");
		free(str);
	}
	i = 8;
	while (++i < 19)
	{
		tex_to_img(data, texture, i);
		if (!texture[i].img)
			throw_err_ex("Malloc error");
		data->ray_data.tex_buf[i] = uchar_to_arr(texture[i].img->pixels,
				texture[i].img->width, texture[i].img->height);
	}
}