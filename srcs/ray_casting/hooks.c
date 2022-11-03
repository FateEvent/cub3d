/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:53:14 by albaur            #+#    #+#             */
/*   Updated: 2022/11/03 11:53:50 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

static void	ft_mouse_input_child(t_var var, t_ray *ray, t_data *data, double x)
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
		data->refresh = 1;
	}
	ft_mouse_input_child(var, ray, data, x);
}

void	update_pathfinding(t_data *data)
{
	t_vector3	pos;
	t_vector3	end;

	if (data->time % 60 != 0)
		return ;
	pos.x = floor(data->ray_data.pos.x);
	pos.y = floor(data->ray_data.pos.y);
	end.x = (int)data->player.player_spawn_pos.x;
	end.y = (int)data->player.player_spawn_pos.y;
	data->player.path = pathfinding(data, pos, end);
}

void	ft_update(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	get_delay(1, 16666);
	while (data->delay > 16666)
	{
		ft_key_input(data);
		++data->time;
		data->delay -= 16666;
		update_pathfinding(data);
	}
	ft_key_input(data);
	update_pathfinding(data);
	ray_casting(data);
	draw_minimap(data);
	mlx_image_to_window(data->mlx, data->map->minimap->img, 0, 0);
	data->delay += get_delay(0, 16666);
	++data->time;
}
