/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:08:44 by albaur            #+#    #+#             */
/*   Updated: 2022/11/15 11:42:56 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

static void	get_doors_sliding(t_data *data)
{
	size_t	i;
	size_t	j;

	i = -1;
	data->ray_data.door.count = 0;
	while (++i < (size_t)data->map->size.y)
	{
		j = -1;
		while ((int)++j < data->map->size_arr[i])
		{
			if (data->ray_data.door.door_map[i][j].is_door == 1
				&& data->ray_data.door.door_map[i][j].sliding != 0)
				++data->ray_data.door.count;
		}
	}
}

static t_vec	*get_doors(t_data *data)
{
	size_t	i;
	size_t	j;
	t_vec	*pos;

	i = -1;
	get_doors_sliding(data);
	pos = malloc(sizeof(t_vec) * data->ray_data.door.count);
	data->ray_data.door.count = 0;
	while ((int)++i < data->map->size.y)
	{
		j = -1;
		while ((int)++j < data->map->size_arr[i])
		{
			if (data->ray_data.door.door_map[i][j].is_door == 1
				&& data->ray_data.door.door_map[i][j].sliding != 0)
				pos[data->ray_data.door.count++] = (t_vec){j, i};
		}
	}
	return (pos);
}

static void	update_doors_pt2(t_data *data, t_ray *ray, size_t x, size_t y)
{
	if (ray->door.door_map[y][x].sliding == 2)
	{
		ray->map->map[y][x] = ray->door.door_map[y][x].index;
		if (data->timer >= ray->door.door_map[y][x].opening_timer + 0.05)
		{
			--ray->door.door_map[y][x].index;
			ray->door.door_map[y][x].offset -= 0.20;
			ray->door.door_map[y][x].opening_timer = data->timer;
		}
		if (ray->door.door_map[y][x].index == 49)
			ray->door.door_map[y][x].sliding = 0;
	}
}

void	update_doors(t_data *data, t_ray *ray)
{
	t_vec	*pos;
	size_t	i;
	size_t	x;
	size_t	y;

	i = -1;
	pos = get_doors(data);
	while (++i < ray->door.count)
	{
		x = pos[i].x;
		y = pos[i].y;
		if (ray->door.door_map[y][x].sliding == 1)
		{
			ray->map->map[y][x] = ray->door.door_map[y][x].index;
			if (data->timer >= ray->door.door_map[y][x].opening_timer + 0.05)
			{
				++ray->door.door_map[y][x].index;
				ray->door.door_map[y][x].offset += 0.20;
				ray->door.door_map[y][x].opening_timer = data->timer;
			}
			if (ray->door.door_map[y][x].index == 56)
			{
				--ray->door.door_map[y][x].index;
				ray->door.door_map[y][x].offset -= 0.20;
			}
		}
		else if (ray->door.door_map[y][x].sliding == 2)
			update_doors_pt2(data, ray, x, y);
	}
	free(pos);
}
