/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 12:07:41 by faventur          #+#    #+#             */
/*   Updated: 2022/10/14 15:24:05 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The ft_put_background() function creates a background by the repetition
** of an image. The amount of times the image is repeated is function of
** the size of the window.
*/

#include "mlx_utils.h"
/*
void	ft_display_map(t_program *data, t_image *pixie)
{
	uint32_t	i[2];
	char		c;

	i[0] = 0;
	while (i[0] * pixie[0].texture->texture.height < HEIGHT && data->map->map[i[0]])
	{
		i[1] = 0;
		while (i[1] * pixie[0].texture->texture.width < WIDTH
			&& data->map->map[i[0]][i[1]] != '\n')
		{
			c = data->map->map[i[0]][i[1]];
			ft_invoke_pixie(c, i, data, pixie);
			i[1]++;
		}
		i[0]++;
	}
}
*/