/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:24:46 by faventur          #+#    #+#             */
/*   Updated: 2022/10/19 14:24:32 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	ft_update(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	data->frame++;
	if (data->frame % 1 == 0 && data->refresh == 1)	// 30 is the render delay
	{
		fill_window(data, 0x650000FF);
		ray_casting(data);
		data->refresh = 0;
	}
}

void	ray_casting(t_data *data)
{
	t_ray		*ray;
	size_t		x;
	int			width;
	int			height;

	x = 0;
	width = WIDTH;
	height = HEIGHT;
	ray = &data->ray_data;
	while (x < WIDTH)
	{
		ray->camera_x = 2 * x / (double)width - 1;
		ray->ray_dir.x = ray->dir.x + ray->plane.x * ray->camera_x;
		ray->ray_dir.y = ray->dir.y + ray->plane.y * ray->camera_x;
		ray->map_pos.x = (int)ray->pos.x;
		ray->map_pos.y = (int)ray->pos.y;
		ray->ray_delta.x = (ray->ray_dir.x == 0) ? 1e30 : fabs(1 / ray->ray_dir.x);
		ray->ray_delta.y = (ray->ray_dir.y == 0) ? 1e30 : fabs(1 / ray->ray_dir.y);
		if (ray->ray_dir.x < 0)
		{
			ray->step_coord.x = -1;
			ray->ray_side.x = (ray->pos.x - ray->map_pos.x) * ray->ray_delta.x;
		}
		else
		{
			ray->step_coord.x = 1;
			ray->ray_side.x = (ray->map_pos.x + 1.0 - ray->pos.x) * ray->ray_delta.x;
		}
		if (ray->ray_dir.y < 0)
		{
			ray->step_coord.y = -1;
			ray->ray_side.y = (ray->pos.y - ray->map_pos.y) * ray->ray_delta.y;
		}
		else
		{
			ray->step_coord.y = 1;
			ray->ray_side.y = (ray->map_pos.y + 1.0 - ray->pos.y) * ray->ray_delta.y;
		}
		ray->hit = 0;
		while (ray->hit == 0)
		{
			if (ray->ray_side.x < ray->ray_side.y)
			{
				ray->ray_side.x += ray->ray_delta.x;
				ray->map_pos.x += ray->step_coord.x;
				ray->side = 0;
			}
			else
			{
				ray->ray_side.y += ray->ray_delta.y;
				ray->map_pos.y += ray->step_coord.y;
				ray->side = 1;
			}
			if (data->map->map[ray->map_pos.y][ray->map_pos.x] > 48)
				ray->hit = 1;
		}
		if (ray->side == 0)
			ray->walldistance = (ray->ray_side.x - ray->ray_delta.x);
		else
			ray->walldistance = (ray->ray_side.y - ray->ray_delta.y);
		ray->lineheight = (int)(height / ray->walldistance);
		ray->drawstart = -ray->lineheight / 2 + height / 2;
		if (ray->drawstart < 0)
			ray->drawstart = 0;
		ray->drawend = ray->lineheight / 2 + height / 2;
		if (ray->drawend >= height)
			ray->drawend = height - 1;
		if (ray->side == 0)
			ray->wall_x = ray->pos.y + ray->walldistance * ray->ray_dir.y;
		else
			ray->wall_x = ray->pos.x + ray->walldistance * ray->ray_dir.x;
		ray->wall_x -= floor(ray->wall_x);
		ray->tex.x = (int)(ray->wall_x * (double)data->textures[ray->text_select].img->width);
		if (ray->side == 0 && ray->ray_dir.x > 0)
			ray->tex.x = data->textures[ray->text_select].img->width - ray->tex.x - 1;
		if (ray->side == 1 && ray->ray_dir.y < 0)
			ray->tex.x = data->textures[ray->text_select].img->width - ray->tex.x - 1;
		ray->step = 1.0 * data->textures[ray->text_select].img->height / ray->lineheight;
		ray->texpos = (ray->drawstart - height / 2 + ray->lineheight / 2) * ray->step;
		draw_ceiling(data, x);
		ft_print_texture(data, x);
		draw_floor(data, x);
		++x;
	}
}
