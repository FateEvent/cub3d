/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixies.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:19:27 by faventur          #+#    #+#             */
/*   Updated: 2022/09/20 13:31:58 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	ft_invoke_enemy(t_program *data, t_image *pixie, t_vector pos, int var)
{
	mlx_image_to_window(data->mlx, pixie[3].img,
		pos.x * (pixie[3].size.x - 1),
		pos.y * (pixie[3].size.y - 1));
	mlx_image_to_window(data->mlx, pixie[8].img,
		pos.x * (pixie[8].size.x - 1),
		pos.y * (pixie[8].size.y - var));
}

void	ft_invoke_char(t_program *data, t_image *pixie, t_vector pos, int var)
{
	mlx_image_to_window(data->mlx, pixie[3].img,
		pos.x * (pixie[3].size.x - 1),
		pos.y * (pixie[3].size.y - 1));
	if (data->map[pos.y][pos.x] == 'P')
		mlx_image_to_window(data->mlx, pixie[4].img,
			pos.x * (pixie[4].size.x - 1),
			pos.y * (pixie[4].size.y - var));
	else if (data->map[pos.y][pos.x] == 'F')
		mlx_image_to_window(data->mlx, pixie[5].img,
			pos.x * (pixie[5].size.x - 1),
			pos.y * (pixie[5].size.y - var));
	else if (data->map[pos.y][pos.x] == 'B')
		mlx_image_to_window(data->mlx, pixie[6].img,
			pos.x * (pixie[6].size.x - 1),
			pos.y * (pixie[6].size.y - var));
	else if (data->map[pos.y][pos.x] == 'L')
		mlx_image_to_window(data->mlx, pixie[7].img,
			pos.x * (pixie[7].size.x - 1),
			pos.y * (pixie[7].size.y - var));
}

static void	ft_invoke_pixie_pt2(int *i, t_program *data, t_image *pixie)
{
	mlx_image_to_window(data->mlx, pixie[3].img,
		i[1] * (pixie[3].size.x - 1),
		i[0] * (pixie[3].size.y - 1));
}

/*
static void	ft_invoke_pixie_pt2(char c, int *i, t_program *data, t_image *pixie)
{
	if (c == 'K')
		ft_swing(data);
	else
		mlx_image_to_window(data->mlx, pixie[3].img,
			i[1] * (pixie[3].size.x - 1),
			i[0] * (pixie[3].size.y - 1));
}
*/
void	ft_invoke_pixie(char c, int *i, t_program *data, t_image *pixie)
{
	if (c == '1')
		mlx_image_to_window(data->mlx, pixie[0].img,
			i[1] * (pixie[0].size.x - 1),
			i[0] * (pixie[0].size.y - 1));
	else if (c == 'C')
	{
		mlx_image_to_window(data->mlx, pixie[3].img,
			i[1] * (pixie[3].size.x - 1),
			i[0] * (pixie[3].size.y - 1));
		mlx_image_to_window(data->mlx, pixie[1].img,
			i[1] * (pixie[1].size.x - 1),
			i[0] * (pixie[1].size.y - 1));
	}
	else if (c == 'E')
	{
		mlx_image_to_window(data->mlx, pixie[3].img,
			i[1] * (pixie[3].size.x - 1),
			i[0] * (pixie[3].size.y - 1));
		mlx_image_to_window(data->mlx, pixie[2].img,
			i[1] * (pixie[2].size.x - 1),
			i[0] * (pixie[2].size.y - 1));
	}
	else
		ft_invoke_pixie_pt2(i, data, pixie);
}

static void	from_texture_to_image(t_program *data, t_image *pixie)
{
	pixie[0].img = mlx_texture_to_image(data->mlx, pixie[0].texture);
	pixie[1].img = mlx_texture_to_image(data->mlx, pixie[0].texture);
	pixie[2].img = mlx_texture_to_image(data->mlx, pixie[0].texture);
	pixie[3].img = mlx_texture_to_image(data->mlx, pixie[0].texture);
	pixie[4].img = mlx_texture_to_image(data->mlx, pixie[0].texture);
	pixie[5].img = mlx_texture_to_image(data->mlx, pixie[0].texture);
	pixie[6].img = mlx_texture_to_image(data->mlx, pixie[0].texture);
	pixie[7].img = mlx_texture_to_image(data->mlx, pixie[0].texture);
	pixie[8].img = mlx_texture_to_image(data->mlx, pixie[0].texture);
}

t_image	*ft_put_sprite(t_program *data)
{
	t_image	*pixie;

	pixie = malloc(sizeof(t_image) * 9);
	pixie[0].texture = mlx_load_xpm("images/wall.xpm");
	pixie[1].texture = mlx_load_xpm("images/sugarcane.xpm");
	pixie[2].texture = mlx_load_xpm("images/house.xpm");
	pixie[3].texture = mlx_load_xpm("images/grass_tile.xpm");
	pixie[4].texture = mlx_load_xpm("images/befana_right.xpm");
	pixie[5].texture = mlx_load_xpm("images/befana_front.xpm");
	pixie[6].texture = mlx_load_xpm("images/befana_back.xpm");
	pixie[7].texture = mlx_load_xpm("images/befana_left.xpm");
	pixie[8].texture = mlx_load_xpm("images/death.xpm");
	from_texture_to_image(data, pixie);
	return (pixie);
}
