/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:10:17 by albaur            #+#    #+#             */
/*   Updated: 2022/11/09 16:11:05 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

static void	mouse_input_child(t_var var, t_ray *ray, t_data *data, double x)
{
	if (x > ray->half_width)
	{
		var.old_dir_x = ray->dir.x;
		ray->dir.x = ray->dir.x * ray->m.pcos - ray->dir.y * ray->m.psin;
		ray->dir.y = var.old_dir_x * ray->m.psin + ray->dir.y * ray->m.pcos;
		var.old_plane_x = ray->plane.x;
		ray->plane.x = ray->plane.x * ray->m.pcos - ray->plane.y * ray->m.psin;
		ray->plane.y = var.old_plane_x * ray->m.psin + ray->plane.y
			* ray->m.pcos;
		data->player.yaw += data->player.speed.rotation / 2;
	}
	mlx_set_mouse_pos(data->mlx, WIDTH / 2, HEIGHT / 2);
}

void	mouse_input(double x, double y, void *param)
{
	t_data	*data;
	t_ray	*ray;
	t_var	var;

	(void)y;
	ft_bzero(&var, sizeof(var));
	data = (t_data *)param;
	ray = &data->ray_data;
	if (ray->m.focus == 1)
		return ;
	if ((ray->half_width - x >= -5 && ray->half_width - x <= 5))
		return ;
	if (x < ray->half_width)
	{
		var.old_dir_x = ray->dir.x;
		ray->dir.x = ray->dir.x * ray->m.ncos - ray->dir.y * ray->m.nsin;
		ray->dir.y = var.old_dir_x * ray->m.nsin + ray->dir.y * ray->m.ncos;
		var.old_plane_x = ray->plane.x;
		ray->plane.x = ray->plane.x * ray->m.ncos - ray->plane.y * ray->m.nsin;
		ray->plane.y = var.old_plane_x * ray->m.nsin + ray->plane.y
			* ray->m.ncos;
		data->player.yaw -= data->player.speed.rotation / 2;
	}
	mouse_input_child(var, ray, data, x);
}
