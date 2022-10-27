/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:53:14 by albaur            #+#    #+#             */
/*   Updated: 2022/10/27 16:34:45 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

static void	ft_mouse_input_child(t_var var, t_ray *ray, t_data *data, double x)
{
	if (x > ray->half_width)
	{
		var.old_dir_x = ray->dir.x;
		ray->dir.x = ray->dir.x * ray->mpcos - ray->dir.y * ray->mpsin;
		ray->dir.y = var.old_dir_x * ray->mpsin + ray->dir.y * ray->mpcos;
		var.old_plane_x = ray->plane.x;
		ray->plane.x = ray->plane.x * ray->mpcos - ray->plane.y * ray->mpsin;
		ray->plane.y = var.old_plane_x * ray->mpsin + ray->plane.y
			* ray->mpcos;
		data->refresh = 1;
	}
	mlx_set_mouse_pos(data->mlx, WIDTH / 2, HEIGHT / 2);
}

void	ft_mouse_input(double x, double y, void *param)
{
	t_data	*data;
	t_ray	*ray;
	t_var	var;

	(void)y;
	ft_bzero(&var, sizeof(var));
	data = (t_data *)param;
	ray = &data->ray_data;
	if ((ray->half_width - x >= -5 && ray->half_width - x <= 5))
		return ;
	if (x < ray->half_width)
	{
		var.old_dir_x = ray->dir.x;
		ray->dir.x = ray->dir.x * ray->mncos - ray->dir.y * ray->mnsin;
		ray->dir.y = var.old_dir_x * ray->mnsin + ray->dir.y * ray->mncos;
		var.old_plane_x = ray->plane.x;
		ray->plane.x = ray->plane.x * ray->mncos - ray->plane.y * ray->mnsin;
		ray->plane.y = var.old_plane_x * ray->mnsin + ray->plane.y
			* ray->mncos;
		data->refresh = 1;
	}
	ft_mouse_input_child(var, ray, data, x);
}

void	ft_update(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	data->frame++;
	if (data->refresh == 1)
	{
		ray_casting(data);
		data->refresh = 0;
	}
}