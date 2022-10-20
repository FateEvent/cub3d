/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colours.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 11:54:00 by faventur          #+#    #+#             */
/*   Updated: 2022/10/20 14:50:22 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

t_color	new_color(int r, int g, int b, int a)
{
	t_color	color;

	color.r = (char)r;
	color.g = (char)g;
	color.b = (char)b;
	color.a = (char)a;
	return (color);
}

int	add_shade(double distance, int color)
{
	t_color	rgb;
	t_color	black;

	rgb = hex_to_rgb(color);
	black = hex_to_rgb(0xff000000);
	if (distance >= 0 && distance <= 1)
	{
		rgb = lerp(rgb, black, distance);
		color = rgb_to_hex(rgb);
		return (color);
	}
	return (0x0);
}

int	get_opposite(int color)
{
	t_color	rgb;

	rgb = hex_to_rgb(color);
	color = rgb_to_hex(rgb);
	return (color);
}
