/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:12:47 by albaur            #+#    #+#             */
/*   Updated: 2022/11/09 16:13:12 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

static double	check_double_overflow(double value)
{
	if (value > 1)
		return (1);
	else if (value < -1)
		return (-1);
	return (value);
}

static void	key_input_focus(t_data *data, t_ray *ray)
{
	if (data->key == (keys_t)MLX_KEY_F)
	{
		if (ray->m.focus == 0)
			ray->m.focus = 1;
		else
			ray->m.focus = 0;
		data->key = 0;
	}
}

static void	key_input_arrows_pt2(t_data *data, t_ray *ray, t_var *var)
{
	double	alpha;

	if (data->key == (keys_t)MLX_KEY_D)
	{
		if (ray->dir.y > 0)
			alpha = acos(check_double_overflow(ray->dir.x));
		else
			alpha = -acos(check_double_overflow(ray->dir.x));
		if (data->map->map[(int)((sin(alpha + M_PI / 2) * var->movement)
				+ ray->pos.y)][(int)(ray->pos.x)] != '1')
			ray->pos.y = (sin(alpha + M_PI / 2) * var->movement)
				+ ray->pos.y;
		if (data->map->map[(int)(ray->pos.y)][(int)((cos(alpha + M_PI / 2)
			* var->movement) + ray->pos.x)] != '1')
			ray->pos.x = (cos(alpha + M_PI / 2) * var->movement)
				+ ray->pos.x;
	}
	else
		key_input_focus(data, ray);
}

void	key_input_arrows(t_data *data, t_ray *ray, t_var *var)
{
	double	alpha;

	if (data->key == (keys_t)MLX_KEY_A)
	{
		if (ray->dir.y > 0)
			alpha = acos(check_double_overflow(ray->dir.x));
		else
			alpha = -acos(check_double_overflow(ray->dir.x));
		if (data->map->map[(int)((-sin(alpha + M_PI / 2) * var->movement)
				+ ray->pos.y)][(int)(ray->pos.x)] != '1')
			ray->pos.y = (-sin(alpha + M_PI / 2) * var->movement)
				+ ray->pos.y;
		if (data->map->map[(int)(ray->pos.y)][(int)((-cos(alpha + M_PI / 2)
			* var->movement) + ray->pos.x)] != '1')
			ray->pos.x = (-cos(alpha + M_PI / 2) * var->movement)
				+ ray->pos.x;
	}
	else
		key_input_arrows_pt2(data, ray, var);
}
