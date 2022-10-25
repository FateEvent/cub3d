/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 12:13:29 by faventur          #+#    #+#             */
/*   Updated: 2022/10/25 14:53:36 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	fill_window(t_data *data, uint32_t color)
{
	mlx_image_t	*frame;
	t_var		var;

	ft_bzero(&var, sizeof(var));
	frame = data->screen.display.img;
	var.width = data->screen.resolution.x;
	var.height = data->screen.resolution.y;
	mlx_draw_square(frame, var.width, var.height, color);
}
