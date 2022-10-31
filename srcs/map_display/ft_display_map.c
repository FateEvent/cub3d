/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 12:07:41 by faventur          #+#    #+#             */
/*   Updated: 2022/10/31 17:35:53 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	get_size_arr(t_data *data, int y)
{
	int	i;

	data->map->size_arr = malloc(sizeof(int) * y);
	if (!data->map->size_arr)
		return ;
	i = 0;
	while (data->map->map[i])
	{
		data->map->size_arr[i] = ft_strlen(data->map->map[i]);
		++i;
	}
}

void	get_map_str(t_data *data)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	while (data->map->map[i])
	{
		j += ft_strlen(data->map->map[i]);
		++i;
	}
	data->map->map_str = malloc(sizeof(char) * j + 1);
	get_size_arr(data, i);
	if (!data->map->map_str)
		ft_puterror("Malloc error");
	i = -1;
	while (data->map->map[++i])
	{
		j = -1;
		while (data->map->map[i][++j])
			data->map->map_str[k++] = data->map->map[i][j];
	}
	data->map->map_str[k] = 0;
}

void	get_map_size(t_data *data)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (data->map->map[i])
	{
		data->map->size.x = fmax(data->map->size.x, ft_strlen(data->map->map[i]));
		++i;
	}
	data->map->size.y = i;
}


void	draw_rect(mlx_image_t *img, t_shape rect, int color)
{
	size_t	i;
	size_t	j;
	size_t	height;
	size_t	width;

	i = fmax(rect.x, 0);
	height = img->height;
	width = img->width;
	while ((int)i < rect.x + rect.width && i < width)
	{
		j = fmax(rect.y, 0);
		while ((int)j < rect.y + rect.height && j < height)
		{
			mlx_put_pixel(img, i, j, color);
			++j;
		}
		i++;
	}
}

int		map_get(t_map *map, int x, int y)
{
	int	pos;
	int	i;

	pos = 0;
	i = 0;
	while (i < y)
	{
		pos += map->size_arr[i];
		i++;
	}
	pos += x;
	if (x < 0 || y < 0 || x >= map->size_arr[y] || y >= map->size.y)
		return (0);
	if (map->map_str[pos] == '1')
		return (1);
	else
		return (0);
}

void	draw_tiles(t_vector2 pos, t_vector3 vec, t_shape rect, t_data *data)
{
	size_t	i;

	i = 0;
	if (map_get(data->map, vec.x + (int)(pos.x), vec.y + (int)(pos.y)))
	{
		draw_rect(data->map->minimap->img, rect, 0x64AB82FF);
	}
}


void	draw_position(t_data *data)
{
	t_shape	rec;
	float	f;

	f = 0;
	rec.height = 2;
	rec.width = 2;
	while (f < 1)
	{
		f += 0.1f;
		rec.x = 105 + (cos(data->player.yaw) * f) * 10;
		rec.y = 77 + (sin(data->player.yaw) * f) * 10;
		draw_rect(data->map->minimap->img, rec, 0xD7FFFFFF);
	}
	rec.x = 104;
	rec.y = 77;
	draw_rect(data->map->minimap->img, rec, 0xFF0000FF);
}

void	draw_minimap(t_data	*data)
{
	t_vector3	vec;
	t_shape		rect;

	mlx_draw_square(data->map->minimap->img, 210, 150, get_rgba(0, 0, 0, 0));
	data->map->minimap->pos.x -= (data->map->minimap->pos.x - data->ray_data.pos.x) * 0.17;
	data->map->minimap->pos.y -= (data->map->minimap->pos.y - data->ray_data.pos.y) * 0.17;
	rect.width = 12;
	rect.height = 12;
	rect.x = -fabs(fmod(data->map->minimap->pos.x, 1)) * rect.width;
	vec.x = -8;
	while (vec.x <= 8)
	{
		vec.y = -6;
		rect.y = -fabs(fmod(data->map->minimap->pos.y, 1)) * rect.height;
		while (vec.y <= 7)
		{
			draw_tiles(data->map->minimap->pos, vec, rect, data);
			rect.y += rect.height + 1;
			vec.y++;
		}
		rect.x += rect.width + 1;
		++vec.x;
	}
	draw_position(data);
}
