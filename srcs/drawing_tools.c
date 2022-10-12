/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:39:31 by faventur          #+#    #+#             */
/*   Updated: 2022/10/12 13:31:54 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	mlx_draw_square(mlx_image_t *img, uint32_t width, uint32_t height,
			uint32_t color)
{
	uint32_t	h;
	uint32_t	w;

	h = -1;
	while (++h < height)
	{
		w = -1;
		while (++w < width)
		{
			mlx_put_pixel(img, w, h, color);
		}
	}
}

void	draw_texture_from_img(t_program *data, float x, float wall_height,
		int texture_pos_x)
{
	float		y_incrementer;
	float		y;
	t_vector2	vec;
	t_vector2	vec2;
	t_color		rgb;
	
	y_incrementer = (wall_height * 2) / data->pixies->img->height;
	y = data->proj.half_height - wall_height;
	for (uint32_t i = 0; i < data->pixies->img->height * 4; i += 4)
	{
		vec = ft_floattovec2(x, y);
		vec2 = ft_floattovec2(x, y + (y_incrementer + 0.5));
		rgb.r = data->pixies[0].img->pixels[(i * data->pixies->img->width + texture_pos_x)];
		rgb.g = data->pixies[0].img->pixels[(i * data->pixies->img->width + texture_pos_x) + 1];
		rgb.b = data->pixies[0].img->pixels[(i * data->pixies->img->width + texture_pos_x) + 2];
		rgb.a = data->pixies[0].img->pixels[(i * data->pixies->img->width + texture_pos_x) + 3];
//		printf("%d\n", data->pixies[0].img->pixels[(i * data->pixies->img->width + texture_pos_x)]);
		draw_line(data->img.img, vec, vec2, rgb_to_hex(rgb));
		
		y += y_incrementer;
	}
}

void	draw_texture(t_program *data, float x, float wall_height,
		int texture_pos_x, t_texture texture)
{
	float		y_incrementer;
	float		y;
	t_vector2	vec;
	t_vector2	vec2;

	y_incrementer = (wall_height * 2) / texture.height;
	y = data->proj.half_height - wall_height;
	for (int i = 0; i < texture.height; i++)
	{
		vec = ft_floattovec2(x, y);
		vec2 = ft_floattovec2(x, y + (y_incrementer + 0.5));
		draw_line(data->img.img, vec, vec2,
			rgb_to_hex(texture.colors[texture.bitmap[i][texture_pos_x] + '0']));
		y += y_incrementer;
	}
}

static void	draw_line_pt2(mlx_image_t *img, t_vector2 start, t_vector2 finish,
		uint32_t color)
{
	float	w;
	float	p;
	int		y;
	float	x;

	if (start.y > finish.y)
		ft_vec2_swap(&start, &finish);
	w = (finish.x - start.x) / (finish.y - start.y);
	p = start.x - w * start.y;
	y = (int)start.y;
	while (y < (int)finish.y)
	{
		x = w * (float)y + p;
		mlx_put_pixel(img, (int)x, y, color);
		y++;
	}
}

void	draw_line(mlx_image_t *img, t_vector2 start, t_vector2 finish,
		uint32_t color)
{
	float	m;
	float	b;
	int		x;
	float	y;

	if (finish.x != start.x)
		m = (finish.y - start.y) / (finish.x - start.x);
	if (finish.x != start.x && fabsf(m) <= 1)
	{
		if (start.x > finish.x)
			ft_vec2_swap(&start, &finish);
		b = start.y - m * start.x;
		x = (int)start.x;
		while (x < (int)finish.x)
		{
			y = m * (float)x + b;
			mlx_put_pixel(img, x, (int)y, color);
			x++;
		}
	}
	else
		draw_line_pt2(img, start, finish, color);
}

void	draw_vertical_line(mlx_image_t *img, t_vector draw_start,
			uint32_t draw_end, uint32_t color)
{
	while (draw_start.y < draw_end)
	{
		mlx_put_pixel(img, draw_start.x, draw_start.y, color);
		draw_start.x++;
	}
}
