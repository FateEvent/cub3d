/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixies.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:19:27 by faventur          #+#    #+#             */
/*   Updated: 2022/10/15 15:13:00 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"
/*
static void	ft_invoke_pixie_pt2(uint32_t *i, t_program *data, t_image *pixie)
{
	mlx_image_to_window(data->mlx, pixie[3].img,
		i[1] * (63 - 1), i[0] * (63 - 1));
}

void	ft_invoke_pixie(char c, uint32_t *i, t_program *data, t_image *pixie)
{
	if (c == '1')
		mlx_image_to_window(data->mlx, pixie[0].img,
			i[1] * (63 - 1), i[0] * (63 - 1));
	else if (c == 'C')
	{
		mlx_image_to_window(data->mlx, pixie[3].img,
			i[1] * (63 - 1), i[0] * (63 - 1));
		mlx_image_to_window(data->mlx, pixie[1].img,
			i[1] * (63 - 1), i[0] * (63 - 1));
	}
	else if (c == 'E')
	{
		mlx_image_to_window(data->mlx, pixie[3].img,
			i[1] * (63 - 1), i[0] * (63 - 1));
		mlx_image_to_window(data->mlx, pixie[2].img,
			i[1] * (63 - 1), i[0] * (63 - 1));
	}
	else
		ft_invoke_pixie_pt2(i, data, pixie);
}
*/
static void	from_texture_to_image(t_data *data, t_image *texture)
{
	texture[0].img = mlx_texture_to_image(data->mlx, &texture[0].texture->texture);
	texture[1].img = mlx_texture_to_image(data->mlx, &texture[1].texture->texture);
	if (!texture[0].img || !texture[1].img)
		return ;
}

t_image	*ft_load_textures(t_data *data)
{
	t_image	*texture;

	texture = malloc(sizeof(t_image) * 2);
	if (!texture)
		return (NULL);
	ft_bzero(texture, sizeof(*texture));
	texture[0].texture = mlx_load_xpm42("./images/wall.xpm42");
	texture[1].texture = mlx_load_xpm42("./images/grass_tile.xpm42");
	if (!texture[0].texture || !texture[1].texture)
		return (NULL);
	from_texture_to_image(data, texture);
	if (!texture[0].img || !texture[1].img)
		return (NULL);
	ft_uchar_arr_display(texture[0].texture->texture.pixels, 35);
	return (texture);
}
