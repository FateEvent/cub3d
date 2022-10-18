/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:24:46 by faventur          #+#    #+#             */
/*   Updated: 2022/10/18 14:47:40 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	ft_update(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	data->frame++;
	if (data->frame % 1 == 0)	// 30 is the render delay
	{
		fill_window(data, 0x650000FF);
		ray_casting(data);
	}
}

void	ray_casting(t_data *data)
{
	t_ray		*ray;
	size_t		x;
	size_t		y;
	int			width;
	int			height;
	uint32_t	*texture;

	x = 0;
	y = 0;
	width = WIDTH;
	height = HEIGHT;
	ray = &data->ray_data;
	texture = ft_from_uchar_to_hex_arr(data->textures[0].img->pixels, data->textures[0].img->width, data->textures[0].img->height);
	while (x < WIDTH)
	{
		ray->camera_x = 2 * x / (double)width - 1;
		ray->raydir_x = ray->dir_x + ray->plane_x * ray->camera_x;
		ray->raydir_y = ray->dir_y + ray->plane_y * ray->camera_x;
		ray->map_x = (int)ray->pos_x;
		ray->map_y = (int)ray->pos_y;
		ray->ray_delta_x = (ray->raydir_x == 0) ? 1e30 : fabs(1 / ray->raydir_x);
		ray->ray_delta_y = (ray->raydir_y == 0) ? 1e30 : fabs(1 / ray->raydir_y);
		if (ray->raydir_x < 0)
		{
			ray->step_x = -1;
			ray->ray_side_x = (ray->pos_x - ray->map_x) * ray->ray_delta_x;
		}
		else
		{
			ray->step_x = 1;
			ray->ray_side_x = (ray->map_x + 1.0 - ray->pos_x) * ray->ray_delta_x;
		}
		if (ray->raydir_y < 0)
		{
			ray->step_y = -1;
			ray->ray_side_y = (ray->pos_y - ray->map_y) * ray->ray_delta_y;
		}
		else
		{
			ray->step_y = 1;
			ray->ray_side_y = (ray->map_y + 1.0 - ray->pos_y) * ray->ray_delta_y;
		}
		ray->hit = 0;
		while (ray->hit == 0)
		{
			if (ray->ray_side_x < ray->ray_side_y)
			{
				ray->ray_side_x += ray->ray_delta_x;
				ray->map_x += ray->step_x;
				ray->side = 0;
			}
			else
			{
				ray->ray_side_y += ray->ray_delta_y;
				ray->map_y += ray->step_y;
				ray->side = 1;
			}
			if (data->map->map[ray->map_y][ray->map_x] > 48)
				ray->hit = 1;
		}
		if (ray->side == 0)
			ray->walldistance = (ray->ray_side_x - ray->ray_delta_x);
		else
			ray->walldistance = (ray->ray_side_y - ray->ray_delta_y);
		ray->lineheight = (int)(height / ray->walldistance);
		ray->pitch = 100;
		ray->drawstart = -ray->lineheight / 2 + height / 2 + ray->pitch;
		if (ray->drawstart < 0)
			ray->drawstart = 0;
		ray->drawend = ray->lineheight / 2 + height / 2 + ray->pitch;
		if (ray->drawend >= height)
			ray->drawend = height - 1;
		if (ray->side == 0)
			ray->wall_x = ray->pos_y + ray->walldistance * ray->raydir_y;
		else
			ray->wall_x = ray->pos_x + ray->walldistance * ray->raydir_x;
		ray->wall_x -= floor(ray->wall_x);
		ray->texx = (int)(ray->wall_x * (double)data->textures[ray->text_select].img->width);
		if (ray->side == 0 && ray->raydir_x > 0)
			ray->texx = data->textures[ray->text_select].img->width - ray->texx - 1;
		if (ray->side == 1 && ray->raydir_y < 0)
			ray->texx = data->textures[ray->text_select].img->width - ray->texx - 1;
		ray->step = 1.0 * data->textures[ray->text_select].img->height / ray->lineheight;
		ray->texpos = (ray->drawstart - ray->pitch - height / 2 + ray->lineheight / 2) * ray->step;
		ft_print_texture(data, x);
		++x;
	}
}
