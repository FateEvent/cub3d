/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour_conversions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 11:59:33 by faventur          #+#    #+#             */
/*   Updated: 2022/10/18 11:23:08 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

int	rgb_to_hex(t_color rgb)
{
	return (rgb.r << 24 | rgb.g << 16 | rgb.b << 8 | rgb.a);
}

t_color	lerp(t_color a, t_color b, float t)
{
	a.r += (b.r - a.r) * t;
	a.g += (b.g - a.g) * t;
	a.b += (b.b - a.b) * t;
	a.a += (b.a - a.a) * t;
	return (a);
}

t_color	hex_to_rgb(uint32_t hex_value)
{	
	t_color	rgb;

	rgb.a = ((hex_value >> 24) & 0xff);
	rgb.r = ((hex_value >> 16) & 0xff);
	rgb.g = ((hex_value >> 8) & 0xff);
	rgb.b = ((hex_value) & 0xff);
	return (rgb);
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
