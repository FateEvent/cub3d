/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:19:27 by faventur          #+#    #+#             */
/*   Updated: 2022/10/24 17:28:10 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

static void	from_texture_to_image(t_data *data, t_image *texture)
{
	t_ray	*ray;

	ray = &data->ray_data;
	texture[0].img = mlx_texture_to_image(data->mlx,
			&texture[0].texture->texture);
	texture[1].img = mlx_texture_to_image(data->mlx,
			&texture[1].texture->texture);
	texture[2].img = mlx_texture_to_image(data->mlx,
			&texture[2].texture->texture);
	texture[3].img = mlx_texture_to_image(data->mlx,
			&texture[3].texture->texture);
	texture[4].img = mlx_texture_to_image(data->mlx,
			&texture[4].texture->texture);
	if (!texture[0].img || !texture[1].img || !texture[2].img
		|| !texture[3].img || !texture[4].img)
		return ;
	ray->tex_buf[0] = ft_from_uchar_to_hex_arr(texture[0].img->pixels, texture[0].img->width, texture[0].img->height);
	ray->tex_buf[1] = ft_from_uchar_to_hex_arr(texture[1].img->pixels, texture[1].img->width, texture[1].img->height);
	ray->tex_buf[2] = ft_from_uchar_to_hex_arr(texture[2].img->pixels, texture[2].img->width, texture[2].img->height);
	ray->tex_buf[3] = ft_from_uchar_to_hex_arr(texture[3].img->pixels, texture[3].img->width, texture[3].img->height);
	ray->tex_buf[4] = ft_from_uchar_to_hex_arr(texture[4].img->pixels, texture[4].img->width, texture[4].img->height);
}

t_image	*ft_load_textures(t_data *data)
{
	t_image	*texture;

	texture = malloc(sizeof(t_image) * 4);
	if (!texture)
		return (NULL);
	ft_bzero(texture, sizeof(*texture));
	texture[0].texture = mlx_load_xpm42(data->map->north_texture);
	texture[1].texture = mlx_load_xpm42(data->map->south_texture);
	texture[2].texture = mlx_load_xpm42(data->map->east_texture);
	texture[3].texture = mlx_load_xpm42(data->map->west_texture);
	texture[4].texture = mlx_load_xpm42("images/dungeon_wall_1.xpm42");
	if (!texture[0].texture || !texture[1].texture || !texture[2].texture
		|| !texture[3].texture || !texture[4].texture)
		return (NULL);
	from_texture_to_image(data, texture);
	if (!texture[0].img || !texture[1].img || !texture[2].img
		|| !texture[3].img || !texture[4].img)
		return (NULL);
	return (texture);
}
