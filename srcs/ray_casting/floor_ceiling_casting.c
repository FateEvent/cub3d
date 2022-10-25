/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceiling_casting.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:13:13 by faventur          #+#    #+#             */
/*   Updated: 2022/10/25 17:18:06 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

uint32_t	get_shading_floor(uint32_t color, t_ray ray, double distance)
{
	t_color	table;
	double	multiplier;
	double	intensity;

	(void)ray;
	if (distance <= 1.00)
		return (color);
	table = hex_to_rgb(color);
	intensity = 1 - ((distance / 100) * 2);
	multiplier = 1 + (distance / intensity);
	table.a = table.a * (intensity / distance * multiplier);
	return (rgb_to_hex(table));
}

void	floor_casting(t_data *data, t_ray *ray)
{
	t_var	var;

	ft_bzero(&var, sizeof(var));
	var.width = data->textures[1].img->width;
	var.height = data->textures[1].img->height;
	while (var.y < ray->resolution.y)
	{
		ray->ray_dir0.x = ray->dir.x - ray->plane.x;
		ray->ray_dir0.y = ray->dir.y - ray->plane.y;
		ray->ray_dir1.x = ray->dir.x + ray->plane.x;
		ray->ray_dir1.y = ray->dir.y + ray->plane.y;
		ray->p = var.y - ray->resolution.y / 2;
		ray->pos_z = 0.5 * ray->resolution.y;
		ray->row_distance = ray->pos_z / ray->p;
		ray->floor_step.x = ray->row_distance * (ray->ray_dir1.x - ray->ray_dir0.x) / ray->resolution.x;
		ray->floor_step.y = ray->row_distance * (ray->ray_dir1.y - ray->ray_dir0.y) / ray->resolution.x;
		ray->floor.x = ray->pos.x + ray->row_distance * ray->ray_dir0.x;
		ray->floor.y = ray->pos.y + ray->row_distance * ray->ray_dir0.y;
		for(int x = 0; x < ray->resolution.x; ++x)
		{
			ray->cell.x = (int)(ray->floor.x);
			ray->cell.y = (int)(ray->floor.y);
			ray->t.x = (int)(var.width * (ray->floor.x - ray->cell.x)) & (var.width - 1);
			ray->t.y = (int)(var.height * (ray->floor.y - ray->cell.y)) & (var.height - 1);
			ray->floor.x += ray->floor_step.x;
			ray->floor.y += ray->floor_step.y;
			ray->floor_tex = 1;
			ray->ceiling_tex = 2;
			var.color = ray->tex_buf[ray->floor_tex][var.width * ray->t.y + ray->t.x];
			var.color = get_shading_floor(var.color, *ray, ray->row_distance);
			mlx_put_pixel(data->screen.display.img, x, var.y, var.color);
			var.color = ray->tex_buf[ray->ceiling_tex][var.width * ray->t.y + ray->t.x];
			var.color = get_shading_floor(var.color, *ray, ray->row_distance);
			mlx_put_pixel(data->screen.display.img, x, ray->resolution.y - var.y - 1,
				var.color);
		}
		var.y++;
	}
}