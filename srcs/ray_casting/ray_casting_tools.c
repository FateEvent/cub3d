/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:24:46 by faventur          #+#    #+#             */
/*   Updated: 2022/11/01 11:29:14 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	sprite_casting_init(t_ray *ray)
{
	t_s_caster	*sprite;
	int	i;

	sprite = &ray->sprite;
	i = 0;
	sprite->sprites = malloc(sizeof(t_sprite) * numSprites);
	sprite->sprite_order = malloc(sizeof(int) * numSprites);
	sprite->sprite_dist = malloc(sizeof(double) * numSprites);
	sprite->z_buffer = malloc(sizeof(double) * ray->resolution.x);
	if (!sprite->sprites || !sprite->z_buffer || !sprite->sprite_order
		|| !sprite->sprite_dist)
		return ;
	sprite->sprites[0].x = 3;
	sprite->sprites[0].y = 3;
	sprite->sprites[0].texture = 6;
	sprite->sprites[1].x = 4;
	sprite->sprites[1].y = 3;
	sprite->sprites[1].texture = 7;
	sprite->sprites[2].x = 5;
	sprite->sprites[2].y = 3;
	sprite->sprites[2].texture = 8;
	while (i < numSprites)
	{
		sprite->sprite_order[i] = i;
		sprite->sprite_dist[i] = ((ray->pos.x - sprite->sprites[i].x)
			* (ray->pos.x - sprite->sprites[i].x)
			+ (ray->pos.y - sprite->sprites[i].y)
			* (ray->pos.y - sprite->sprites[i].y));
		i++;
	}
	sort_sprites(sprite->sprite_order, sprite->sprite_dist, numSprites);
}

void	line_drawer(t_data *data, t_ray *ray, t_var *v, int i)
{
	t_s_caster	*sprite;

	sprite = &ray->sprite;
	sprite->stripe = sprite->draw_start.x;
	v->width = SPRITEHEIGHT;
	v->height = SPRITEWIDTH;
	while (sprite->stripe < sprite->draw_end.x)
	{
		sprite->tex.x = (int)(256 * (sprite->stripe - (-sprite->sprite_width / 2
			+ sprite->sprite_screen_x)) * v->width / sprite->sprite_width) / 256;
		if (sprite->transform.y > 0 && sprite->stripe > 0 && sprite->stripe < WIDTH
			&& sprite->transform.y < sprite->z_buffer[sprite->stripe])
		for (int y = sprite->draw_start.y; y < sprite->draw_end.y; y++)
		{
			sprite->d = (y) * 256 - HEIGHT * 128 + sprite->sprite_height * 128;
			sprite->tex.y = ((sprite->d * v->height) / sprite->sprite_height) / 256;
			v->color = ray->tex_buf[sprite->sprites[sprite->sprite_order[i]].texture]
				[v->width * sprite->tex.y + sprite->tex.x];
			if ((v->color & 0xFFFFFF00) != 0)
				mlx_put_pixel(data->screen.display.img, sprite->stripe, y, v->color);
		}
		sprite->stripe++;
	}
}

void	points_lines_designer(t_ray *ray)
{
	t_s_caster	*sprite;

	sprite = &ray->sprite;
	if (sprite->draw_start.y < 0)
		sprite->draw_start.y = 0;
	sprite->draw_end.y = sprite->sprite_height / 2 + HEIGHT / 2;
	if (sprite->draw_end.y >= HEIGHT)
		sprite->draw_end.y = HEIGHT - 1;
	sprite->sprite_width = abs((int)(HEIGHT / (sprite->transform.y)));
	sprite->draw_start.x = -sprite->sprite_width / 2 + sprite->sprite_screen_x;
	if (sprite->draw_start.x < 0)
		sprite->draw_start.x = 0;
	sprite->draw_end.x = sprite->sprite_width / 2 + sprite->sprite_screen_x;
	if (sprite->draw_end.x >= WIDTH)
		sprite->draw_end.x = WIDTH - 1;
}

void	doing_some_math(t_ray *ray, int i)
{
	t_s_caster	*sprite;

	sprite = &ray->sprite;
	sprite->sprite.x = sprite->sprites[sprite->sprite_order[i]].x - ray->pos.x;
	sprite->sprite.y = sprite->sprites[sprite->sprite_order[i]].y - ray->pos.y;
	sprite->inv_det = 1.0 / (ray->plane.x * ray->dir.y - ray->dir.x * ray->plane.y);
	sprite->transform.x = sprite->inv_det * (ray->dir.y * sprite->sprite.x - ray->dir.x
		* sprite->sprite.y);
	sprite->transform.y = sprite->inv_det * (-ray->plane.y * sprite->sprite.x
		+ ray->plane.x * sprite->sprite.y);
	sprite->sprite_screen_x = (int)((WIDTH / 2) * (1 + sprite->transform.x / sprite->transform.y));
	sprite->sprite_height = abs((int)(HEIGHT / (sprite->transform.y)));
	sprite->draw_start.y = -sprite->sprite_height / 2 + HEIGHT / 2;
}

void	sprite_caster(t_data *data, t_ray *ray, t_var *v)
{
	int	i;

	i = 0;
	while (i < numSprites)
	{
		doing_some_math(ray, i);
		points_lines_designer(ray);
		line_drawer(data, ray, v, i);
		i++;
	}
}

void	ray_casting(t_data *data)
{
	t_ray	*ray;
	t_var	var;

	ft_bzero(&var, sizeof(var));
	var.x = 0;
	ray = &data->ray_data;
	ray->map = data->map;
	sprite_casting_init(ray);
//	if ()	
		floor_casting(data, ray);
	while (var.x < ray->resolution.x)
	{
		ray_data_init(ray, var.x);
		rayside_calculator(ray);
		ray_launcher(ray);
		wall_distance_calculator(ray);
		wall_line_calculator(ray);
		texture_x_pos_calculator(data, ray);
		texture_y_pos_calculator(data, ray);
//		if ()
//			draw_ceiling(data, x);
		draw_walls(data, var.x);
//		if ()
//			draw_floor(data, x);
		ray->sprite.z_buffer[var.x] = ray->wall_distance;
		++var.x;
	}
	sprite_caster(data, ray, &var);
}
