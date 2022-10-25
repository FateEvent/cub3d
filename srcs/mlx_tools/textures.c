/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:19:27 by faventur          #+#    #+#             */
/*   Updated: 2022/10/25 17:48:30 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

static void	from_texture_to_image(t_data *data, t_image *texture)
{
	t_ray	*ray;
	size_t	i;

	i = -1;
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
	texture[5].img = mlx_texture_to_image(data->mlx,
			&texture[5].texture->texture);
	if (!texture[0].img || !texture[1].img || !texture[2].img
		|| !texture[3].img || !texture[4].img)
		return ;
	while (++i < 6)
		ray->tex_buf[i] = uchar_to_arr(texture[i].img->pixels,
				texture[i].img->width, texture[i].img->height);
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
	texture[4].texture = mlx_load_xpm42("images/ceiling.xpm42");
	texture[5].texture = mlx_load_xpm42("images/carpet.xpm42");
	if (!texture[0].texture || !texture[1].texture || !texture[2].texture
		|| !texture[3].texture || !texture[4].texture)
		return (NULL);
	from_texture_to_image(data, texture);
	if (!texture[0].img || !texture[1].img || !texture[2].img
		|| !texture[3].img || !texture[4].img)
		return (NULL);
	return (texture);
}
