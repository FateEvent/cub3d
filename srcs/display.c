/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:48:53 by faventur          #+#    #+#             */
/*   Updated: 2022/09/20 11:26:18 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "forms_and_colours.h"

void	ft_put_background(t_program *data, char *path)
{
	t_image	bg;
	int		i;
	int		j;

	bg.reference = mlx_xpm_file_to_image(data->mlx, path, &bg.size.x,
			&bg.size.y);
	i = 0;
	j = 0;
	while (i * bg.size.y < data->window.size.y)
	{	
		while (j * bg.size.x < data->window.size.x)
		{		
			mlx_image_to_window(data->mlx, bg.reference,
				j * (bg.size.x - 1), i * (bg.size.y - 1));
			j++;
		}
		j = 0;
		i++;
	}
}
