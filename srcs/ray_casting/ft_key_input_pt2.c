/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_input_pt2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 10:17:11 by faventur          #+#    #+#             */
/*   Updated: 2022/10/28 14:58:37 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

static double	ft_check_double_overflow(double value)
{
	if (value > 1)
		return (1);
	else if (value < -1)
		return (-1);
	return (value);
}

static void	ft_key_input_focus(t_ray *ray, mlx_key_data_t keydata)
{
	if (keydata.key == (keys_t)MLX_KEY_F && keydata.action == MLX_PRESS)
	{
		if (ray->m.focus == 0)
			ray->m.focus = 1;
		else
			ray->m.focus = 0;
	}
}

static void	ft_key_input_arrows_pt2(t_data *data, t_ray *ray, t_var *var,
				mlx_key_data_t keydata)
{
	int	alpha;

	if (keydata.key == (keys_t)RIGHT
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		if (ray->dir.y > 0)
			alpha = acos(ft_check_double_overflow(ray->dir.x));
		else
			alpha = -acos(ft_check_double_overflow(ray->dir.x));
		if (data->map->map[(int)((sin(alpha + M_PI / 2) * var->movement)
				+ ray->pos.y)][(int)(ray->pos.x)] != '1')
			ray->pos.y = (sin(alpha + M_PI / 2) * var->movement)
				+ ray->pos.y;
		if (data->map->map[(int)(ray->pos.y)][(int)((cos(alpha + M_PI / 2)
			* var->movement) + ray->pos.x)] != '1')
			ray->pos.x = (cos(alpha + M_PI / 2) * var->movement)
				+ ray->pos.x;
		data->refresh = 1;
	}
	else
		ft_key_input_focus(ray, keydata);
}

void	ft_key_input_arrows(t_data *data, t_ray *ray, t_var *var,
				mlx_key_data_t keydata)
{
	int	alpha;

	if (keydata.key == (keys_t)LEFT
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		if (ray->dir.y > 0)
			alpha = acos(ft_check_double_overflow(ray->dir.x));
		else
			alpha = -acos(ft_check_double_overflow(ray->dir.x));
		if (data->map->map[(int)((-sin(alpha + M_PI / 2) * var->movement)
				+ ray->pos.y)][(int)(ray->pos.x)] != '1')
			ray->pos.y = (-sin(alpha + M_PI / 2) * var->movement)
				+ ray->pos.y;
		if (data->map->map[(int)(ray->pos.y)][(int)((-cos(alpha + M_PI / 2)
			* var->movement) + ray->pos.x)] != '1')
			ray->pos.x = (-cos(alpha + M_PI / 2) * var->movement)
				+ ray->pos.x;
		data->refresh = 1;
	}
	else
		ft_key_input_arrows_pt2(data, ray, var, keydata);
}
