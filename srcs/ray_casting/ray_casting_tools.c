/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:24:46 by faventur          #+#    #+#             */
/*   Updated: 2022/11/01 09:24:47 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	sprite_casting_init(t_ray *ray)
{
	int	i;

	i = 0;
	ray->scast.sprites = malloc(sizeof(t_sprite) * numSprites);
	ray->scast.sprite_order = malloc(sizeof(int) * numSprites);
	ray->scast.sprite_dist = malloc(sizeof(double) * numSprites);
	ray->scast.z_buffer = malloc(sizeof(double) * ray->resolution.x);
	if (!ray->scast.sprites || !ray->scast.z_buffer || !ray->scast.sprite_order
		|| !ray->scast.sprite_dist)
		return ;
	ray->scast.sprites[0].x = 3;
	ray->scast.sprites[0].y = 3;
	ray->scast.sprites[0].texture = 6;
	ray->scast.sprites[1].x = 4;
	ray->scast.sprites[1].y = 3;
	ray->scast.sprites[1].texture = 7;
	ray->scast.sprites[2].x = 5;
	ray->scast.sprites[2].y = 3;
	ray->scast.sprites[2].texture = 8;
	while (i < numSprites)
	{
		ray->scast.sprite_order[i] = i;
		ray->scast.sprite_dist[i] = ((ray->pos.x - ray->scast.sprites[i].x) * (ray->pos.x - ray->scast.sprites[i].x) + (ray->pos.y - ray->scast.sprites[i].y) * (ray->pos.y - ray->scast.sprites[i].y));
		i++;
	}
	sort_sprites(ray->scast.sprite_order, ray->scast.sprite_dist, numSprites);
}

void	line_drawer(t_data *data, t_ray *ray, t_var var, int i)
{
	ray->scast.stripe = ray->scast.draw_start.x;
	while (ray->scast.stripe < ray->scast.draw_end.x)
	{
		ray->scast.tex.x = (int)(256 * (ray->scast.stripe - (-ray->scast.sprite_width / 2 + ray->scast.sprite_screen_x)) * var.width / ray->scast.sprite_width) / 256;
		if(ray->scast.transform.y > 0 && ray->scast.stripe > 0 && ray->scast.stripe < WIDTH && ray->scast.transform.y < ray->scast.z_buffer[ray->scast.stripe])
		for(int y = ray->scast.draw_start.y; y < ray->scast.draw_end.y; y++)
		{
			ray->scast.d = (y) * 256 - HEIGHT * 128 + ray->scast.sprite_height * 128;
			ray->scast.tex.y = ((ray->scast.d * var.height) / ray->scast.sprite_height) / 256;
			var.color = ray->tex_buf[ray->scast.sprites[ray->scast.sprite_order[i]].texture][var.width * ray->scast.tex.y + ray->scast.tex.x];
			if((var.color & 0xFFFFFF00) != 0)
				mlx_put_pixel(data->screen.display.img, ray->scast.stripe, y, var.color);
		}
		ray->scast.stripe++;
	}
}

void	point_referencer(t_ray *ray)
{
	if (ray->scast.draw_start.y < 0)
		ray->scast.draw_start.y = 0;
	ray->scast.draw_end.y = ray->scast.sprite_height / 2 + HEIGHT / 2;
	if (ray->scast.draw_end.y >= HEIGHT)
		ray->scast.draw_end.y = HEIGHT - 1;
	ray->scast.sprite_width = abs((int)(HEIGHT / (ray->scast.transform.y)));
	ray->scast.draw_start.x = -ray->scast.sprite_width / 2 + ray->scast.sprite_screen_x;
	if (ray->scast.draw_start.x < 0)
		ray->scast.draw_start.x = 0;
	ray->scast.draw_end.x = ray->scast.sprite_width / 2 + ray->scast.sprite_screen_x;
	if (ray->scast.draw_end.x >= WIDTH)
		ray->scast.draw_end.x = WIDTH - 1;
}

void	faut_trouver_un_nom(t_ray *ray, int i)
{
	ray->scast.sprite.x = ray->scast.sprites[ray->scast.sprite_order[i]].x - ray->pos.x;
	ray->scast.sprite.y = ray->scast.sprites[ray->scast.sprite_order[i]].y - ray->pos.y;
	ray->scast.inv_det = 1.0 / (ray->plane.x * ray->dir.y - ray->dir.x * ray->plane.y);
	ray->scast.transform.x = ray->scast.inv_det * (ray->dir.y * ray->scast.sprite.x - ray->dir.x * ray->scast.sprite.y);
	ray->scast.transform.y = ray->scast.inv_det * (-ray->plane.y * ray->scast.sprite.x + ray->plane.x * ray->scast.sprite.y);
	ray->scast.sprite_screen_x = (int)((WIDTH / 2) * (1 + ray->scast.transform.x / ray->scast.transform.y));
	ray->scast.sprite_height = abs((int)(HEIGHT / (ray->scast.transform.y)));
	ray->scast.draw_start.y = -ray->scast.sprite_height / 2 + HEIGHT / 2;
}

void	sprite_caster(t_data *data, t_ray *ray, t_var var)
{
	int	i;

	i = 0;
	while (i < numSprites)
	{
		faut_trouver_un_nom(ray, i);
		point_referencer(ray);
		line_drawer(data, ray, var, i);
		i++;
	}
}

void	ray_casting(t_data *data)
{
	t_ray	*ray;
	size_t	x;
	t_var	var;		// sprites

	ft_bzero(&var, sizeof(var));	// sprites
	x = 0;
	ray = &data->ray_data;
	ray->map = data->map;
	var.width = 64;	// sprites
	var.height = 64;	// sprites
	sprite_casting_init(ray);
//	if ()	
		floor_casting(data, ray);
	while (x < ray->resolution.x)
	{
		ray_data_init(ray, x);
		rayside_calculator(ray);
		ray_launcher(ray);
		wall_distance_calculator(ray);
		wall_line_calculator(ray);
		texture_x_pos_calculator(data, ray);
		texture_y_pos_calculator(data, ray);
//		if ()
//			draw_ceiling(data, x);
		draw_walls(data, x);
//		if ()
//			draw_floor(data, x);
		ray->scast.z_buffer[x] = ray->wall_distance;
		++x;
	}
	sprite_caster(data, ray, var);
}
