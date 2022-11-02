/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:19:27 by faventur          #+#    #+#             */
/*   Updated: 2022/11/02 11:46:20 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

static void	sprite_arr_creator(t_data *data, t_image *texture)
{
	size_t	i;

	i = 5;
	texture[6].texture = mlx_load_xpm42("images/smiler.xpm42");
	texture[7].texture = mlx_load_xpm42("images/greenlight.xpm42");
	texture[8].texture = mlx_load_xpm42("images/pillar.xpm42");
	if (!texture[6].texture || !texture[7].texture || !texture[8].texture)
		return ;
	texture[6].img = mlx_texture_to_image(data->mlx,
			&texture[6].texture->texture);
	texture[7].img = mlx_texture_to_image(data->mlx,
			&texture[7].texture->texture);
	texture[8].img = mlx_texture_to_image(data->mlx,
			&texture[8].texture->texture);
	if (!texture[6].img || !texture[7].img || !texture[8].img)
		return ;
	while (++i < 9)
		data->ray_data.tex_buf[i] = uchar_to_arr(texture[i].img->pixels,
				texture[i].img->width, texture[i].img->height);
}

static void	from_texture_to_image(t_data *data, t_image *texture)
{
	t_ray	*ray;
	size_t	i;

	ray = &data->ray_data;
	i = -1;
	texture[0].img = mlx_texture_to_image(data->mlx,
			&texture[0].texture->texture);
	texture[1].img = mlx_texture_to_image(data->mlx,
			&texture[1].texture->texture);
	texture[2].img = mlx_texture_to_image(data->mlx,
			&texture[2].texture->texture);
	texture[3].img = mlx_texture_to_image(data->mlx,
			&texture[3].texture->texture);
	if (data->map->mode == 1)
	{
		texture[4].img = mlx_texture_to_image(data->mlx,
			&texture[4].texture->texture);
		texture[5].img = mlx_texture_to_image(data->mlx,
			&texture[5].texture->texture);
	}
	if (!texture[0].img || !texture[1].img || !texture[2].img
		|| !texture[3].img || (data->map->mode == 1 && (!texture[4].img || !texture[5].img)))
		return ;
	while (++i < 6)
	{
		if ((i == 4 || i == 5) && data->map->mode != 1)
			continue ;
		ray->tex_buf[i] = uchar_to_arr(texture[i].img->pixels,
				texture[i].img->width, texture[i].img->height);
	}
	sprite_arr_creator(data, texture);
}

t_image	*ft_load_textures(t_data *data)
{
	t_image	*texture;

	texture = malloc(sizeof(t_image) * 9);
	if (!texture)
		return (NULL);
	ft_bzero(texture, sizeof(*texture));
	texture[0].texture = mlx_load_xpm42(data->map->north_texture);
	texture[1].texture = mlx_load_xpm42(data->map->south_texture);
	texture[2].texture = mlx_load_xpm42(data->map->east_texture);
	texture[3].texture = mlx_load_xpm42(data->map->west_texture);
	if (data->map->mode == 1)
	{
		texture[4].texture = mlx_load_xpm42(data->map->ceiling_texture);
		texture[5].texture = mlx_load_xpm42(data->map->floor_texture);
	}
	if (!texture[0].texture || !texture[1].texture || !texture[2].texture
		|| !texture[3].texture || (data->map->mode == 1 && (!texture[4].texture || !texture[5].texture)))
		return (NULL);
	from_texture_to_image(data, texture);
	if (!texture[0].img || !texture[1].img || !texture[2].img
		|| !texture[3].img || (data->map->mode == 1 && (!texture[4].img || !texture[5].img))
		|| !texture[6].img || !texture[7].img || !texture[8].img)
		return (NULL);
	return (texture);
}
