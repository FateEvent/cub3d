/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixies.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:19:27 by faventur          #+#    #+#             */
/*   Updated: 2022/10/07 14:19:56 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

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

static void	from_texture_to_image(t_program *data, t_image *pixie)
{
	pixie[0].img = mlx_texture_to_image(data->mlx, &pixie[0].texture->texture);
	pixie[1].img = mlx_texture_to_image(data->mlx, &pixie[1].texture->texture);
	pixie[2].img = mlx_texture_to_image(data->mlx, &pixie[2].texture->texture);
	pixie[3].img = mlx_texture_to_image(data->mlx, &pixie[3].texture->texture);
	pixie[4].img = mlx_texture_to_image(data->mlx, &pixie[4].texture->texture);
	pixie[5].img = mlx_texture_to_image(data->mlx, &pixie[5].texture->texture);
	pixie[6].img = mlx_texture_to_image(data->mlx, &pixie[6].texture->texture);
	pixie[7].img = mlx_texture_to_image(data->mlx, &pixie[7].texture->texture);
	pixie[8].img = mlx_texture_to_image(data->mlx, &pixie[8].texture->texture);
}

t_image	*ft_put_sprite(t_program *data)
{
	t_image	*pixie;

	pixie = malloc(sizeof(t_image) * 9);
	pixie[0].texture = mlx_load_xpm42("images/wall.xpm42");
	pixie[1].texture = mlx_load_xpm42("images/sugarcane.xpm42");
	pixie[2].texture = mlx_load_xpm42("images/house.xpm42");
	pixie[3].texture = mlx_load_xpm42("images/grass_tile.xpm42");
	pixie[4].texture = mlx_load_xpm42("images/befana_right.xpm42");
	pixie[5].texture = mlx_load_xpm42("images/befana_front.xpm42");
	pixie[6].texture = mlx_load_xpm42("images/befana_back.xpm42");
	pixie[7].texture = mlx_load_xpm42("images/befana_left.xpm42");
	pixie[8].texture = mlx_load_xpm42("images/death.xpm42");
	from_texture_to_image(data, pixie);
	return (pixie);
}
