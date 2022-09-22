/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 12:07:41 by faventur          #+#    #+#             */
/*   Updated: 2022/09/22 16:14:46 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The ft_put_background() function creates a background by the repetition
** of an image. The amount of times the image is repeated is function of
** the size of the window.
*/

#include "mlx_utils.h"

static void	ft_display_moves_pt2(t_program *d, t_vector pos, int key,
		int *counter)
{
	if (key == 1 && d->map[pos.y + 1][pos.x] != '1')
	{
		if (d->map[pos.y + 1][pos.x] == 'C' || d->map[pos.y + 1][pos.x] == '0')
		{
			d->map[pos.y][pos.x] = '0';
			d->map[pos.y + 1][pos.x] = 'F';
			(*counter)++;
		}
		else if (d->map[pos.y + 1][pos.x] == 'E' && verify_conditions(d->map))
			ft_break_the_game(d, "You win!");
	}
	else if (key == 13 && d->map[pos.y - 1][pos.x] != '1')
	{
		if (d->map[pos.y - 1][pos.x] == 'C' || d->map[pos.y - 1][pos.x] == '0')
		{
			d->map[pos.y][pos.x] = '0';
			d->map[pos.y - 1][pos.x] = 'B';
			(*counter)++;
		}
		else if (d->map[pos.y - 1][pos.x] == 'E' && verify_conditions(d->map))
			ft_break_the_game(d, "You win!");
	}
	else if (key == 53)
		exit(0);
}

void	ft_display_moves(t_program *d, int key, t_vector pos, int *counter)
{
	if (key == 0 && d->map[pos.y][pos.x - 1] != '1')
	{
		if (d->map[pos.y][pos.x - 1] == 'C' || d->map[pos.y][pos.x - 1] == '0')
		{
			d->map[pos.y][pos.x] = '0';
			d->map[pos.y][pos.x - 1] = 'L';
			(*counter)++;
		}
		else if (d->map[pos.y][pos.x - 1] == 'E' && verify_conditions(d->map))
			ft_break_the_game(d, "You win!");
	}
	else if (key == 2 && d->map[pos.y][pos.x + 1] != '1')
	{
		if (d->map[pos.y][pos.x + 1] == 'C' || d->map[pos.y][pos.x + 1] == '0')
		{
			d->map[pos.y][pos.x] = '0';
			d->map[pos.y][pos.x + 1] = 'P';
			(*counter)++;
		}
		else if (d->map[pos.y][pos.x + 1] == 'E' && verify_conditions(d->map))
			ft_break_the_game(d, "You win!");
	}
	else
		ft_display_moves_pt2(d, pos, key, counter);
}

void	mlx_draw_square(mlx_image_t *img, uint32_t width, uint32_t height, uint32_t color)
{
	uint32_t	h;
	uint32_t	w;

	h = -1;
	while (++h < height)
	{
		w = -1;
		while (++w < width)
		{
			mlx_put_pixel(img, w, h, color);
		}
	}
}

void	ft_display_map(t_program *data)
{
	uint32_t	h;
	uint32_t	w;
	t_vector	size;

	h = -1;
	size = calculate_window_size(data->map);
	while (++h < size.y)
	{
		w = -1;
		while (++w < size.x)
		{
			mlx_put_pixel(data->img.img, w, h, 0x0FFFFFF);
		}
	}
	h = -1;
	while (++h < size.y && data->map[h])
	{
		w = -1;
		while (++w < size.x && data->map[h][w] != '\n')
		{
			if (data->map[h][w] == 1)
				mlx_put_pixel(data->img.img, w, h, 0x666666);
		}
	}
	
	// wtile = mlx_new_image(data->mlx, 65, 65);
	// ft_memset(wtile->pixels, 255, wtile->width * wtile->height
	// 	* sizeof(int32_t));
	// i[0] = 0;
	// i[1] = 0;
	// while (i[0] * 65 < data->img.img->height && data->map[i[0]])
	// {	
	// 	while (i[1] * 65 < data->img.img->width
	// 		&& data->map[i[0]][i[1]] != '\n')
	// 	{
	// 		c = data->map[i[0]][i[1]];
	// 		mlx_image_to_window(data->mlx, wtile, i[0], i[1]);
	// 		i[1]++;
	// 	}
	// 	i[1] = 0;
	// 	i[0]++;
	// }
}
