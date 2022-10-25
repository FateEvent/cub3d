/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:53:14 by albaur            #+#    #+#             */
/*   Updated: 2022/10/25 16:01:34 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

static void	ft_mouse_input_child(t_var var, t_ray *ray, t_data *data, double x)
{
	if (x > data->mouse_x)
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
	data->mouse_x = x;
}

void	ft_mouse_input(double x, double y, void *param)
{
	t_data	*data;
	t_ray	*ray;
	t_var	var;
	
	(void)y;
	ft_bzero(&var, sizeof(var));
	data = (t_data *)param;
	if ((data->mouse_x - x >= -5 && data->mouse_x - x <= 5))
		return ;
	ray = &data->ray_data;
	if (x < data->mouse_x)
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
