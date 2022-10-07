/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:24:46 by faventur          #+#    #+#             */
/*   Updated: 2022/10/07 18:41:49 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

float	degrees_to_radians(float degrees)
{
	return (degrees * M_PI / 180);
}

void	ft_update(void *param)
{
	t_program	*program;

	program = (t_program *)param;
	program->frame++;
	if (program->frame % program->render.delay == 0)
	{
		fill_window(program, 0x650000FF);
		ray_casting(program);
	}
}

void	ray_casting(t_program *data)
{
	float	ray_angle = data->player.angle - data->player.half_fov;
	for(uint32_t ray_count = 0; ray_count < data->proj.width; ray_count++) {
		
		// Ray data
		t_vector2	ray = ft_floattovec2(data->player.x, data->player.y);

		// Wall finder
		char wall = 48;
		while (wall == 48) {
			ray.x += cosf(degrees_to_radians(ray_angle)) / data->rc.precision;
			ray.y += sinf(degrees_to_radians(ray_angle)) / data->rc.precision;
			wall = data->map.map[(int)floorf(ray.y)][(int)floorf(ray.x)];
		}

		// Pythagoras theorem
		float distance = sqrtf(powf(data->player.x - ray.x, 2) + powf(data->player.y - ray.y, 2));

		// Fish eye fix
		distance = distance * cosf(degrees_to_radians(ray_angle - data->player.angle));

		// Wall height
		float	wall_height = floorf((float)data->proj.half_height / distance);

		// Get texture
		t_texture	texture = data->textures;	//the guy uses an array of textures, wall - 1 is used 'cause the wall types range from 1 to 3 in the map, so from 0 to 2 in the array

		// Calcule texture position
		int	texture_pos_x = floorf((texture.width * (int)(ray.x + ray.y)) % texture.width);

		// Draw
		t_vector2	vec = ft_floattovec2(ray_count, 0);
		t_vector2	vec2 = ft_floattovec2(ray_count, (float)(data->proj.half_height - wall_height));
		t_vector2	vec3 = ft_floattovec2(ray_count, (float)(data->proj.half_height + wall_height));
		t_vector2	vec4 = ft_floattovec2(ray_count, (float)(data->proj.height));
		draw_line(data->img.img, vec, vec2, 0x000000FF);
		draw_texture(data, ray_count, wall_height, texture_pos_x, texture);
		draw_line(data->img.img, vec3, vec4, 0x5F574FFF);

		// Increment
		ray_angle += data->rc.increment_angle;
	}
}

/*
void	ray_casting(t_program *data)
{
	t_vector2	vec;
	t_vector2	vec2;
	t_vector2	vec3;
	t_vector2	vec4;

	vec = ft_floattovec2(480, 0);
	vec2 = ft_floattovec2(480, 0);
	vec3 = ft_floattovec2(480, 240);
	vec4 = ft_floattovec2(480, 63);
	draw_line(data->img.img, vec, vec2, 0x00FFFFFF);
	draw_line(data->img.img, vec2, vec3, 0xFF0000FF);
	draw_line(data->img.img, vec3, vec4, 0x00FF00FF);
}
*/