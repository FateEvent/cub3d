/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceiling_casting.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:13:13 by faventur          #+#    #+#             */
/*   Updated: 2022/10/25 16:59:56 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	floor_casting(t_data *data, t_ray *ray)
{
	t_var	var;

	ft_bzero(&var, sizeof(var));
	var.y = 0;
	// je verrai après pour les textures
	var.width = data->textures[1].img->width;
	var.height = data->textures[1].img->height;
	//FLOOR CASTING
	while (var.y < ray->resolution.y)
	{
		// rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
		ray->ray_dir0.x = ray->dir.x - ray->plane.x;
		ray->ray_dir0.y = ray->dir.y - ray->plane.y;
		ray->ray_dir1.x = ray->dir.x + ray->plane.x;
		ray->ray_dir1.y = ray->dir.y + ray->plane.y;

		// Current y position compared to the center of the screen (the horizon)
		ray->p = var.y - ray->resolution.y / 2;

		// Vertical position of the camera.
		ray->pos_z = 0.5 * ray->resolution.y;

		// Horizontal distance from the camera to the floor for the current row.
		// 0.5 is the z position exactly in the middle between floor and ceiling.
		ray->row_distance = ray->pos_z / ray->p;

		// calculate the real world step vector we have to add for each x (parallel to camera plane)
		// adding step by step avoids multiplications with a weight in the inner loop
		ray->floor_step.x = ray->row_distance * (ray->ray_dir1.x - ray->ray_dir0.x) / ray->resolution.x;
		ray->floor_step.y = ray->row_distance * (ray->ray_dir1.y - ray->ray_dir0.y) / ray->resolution.x;

		// real world coordinates of the leftmost column. This will be updated as we step to the right.
		ray->floor.x = ray->pos.x + ray->row_distance * ray->ray_dir0.x;
		ray->floor.y = ray->pos.y + ray->row_distance * ray->ray_dir0.y;

		for(int x = 0; x < ray->resolution.x; ++x)
		{
			// the cell coord is simply got from the integer parts of ray->floor.x and ray->floor.y
			ray->cell.x = (int)(ray->floor.x);
			ray->cell.y = (int)(ray->floor.y);

			// get the texture coordinate from the fractional part
			ray->t.x = (int)(var.width * (ray->floor.x - ray->cell.x)) & (var.width - 1);
			ray->t.y = (int)(var.height * (ray->floor.y - ray->cell.y)) & (var.height - 1);

			ray->floor.x += ray->floor_step.x;
			ray->floor.y += ray->floor_step.y;

			// choose texture and draw the pixel
			// je verrai après pour les textures
			ray->floor_tex = 1;
			ray->ceiling_tex = 2;
			// floor
			var.color = ray->tex_buf[ray->floor_tex][var.width * ray->t.y + ray->t.x];
			var.color = (var.color >> 1) & 8355711; // make a bit darker
			mlx_put_pixel(data->screen.display.img, x, var.y, var.color);

			//ceiling (symmetrical, at ray->resolution.y - y - 1 instead of y)
			var.color = ray->tex_buf[ray->ceiling_tex][var.width * ray->t.y + ray->t.x];
			var.color = (var.color >> 1) & 8355711; // make a bit darker
			mlx_put_pixel(data->screen.display.img, x, ray->resolution.y - var.y - 1,
				var.color);
		}
		var.y++;
	}
}