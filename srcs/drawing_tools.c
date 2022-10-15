/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:39:31 by faventur          #+#    #+#             */
/*   Updated: 2022/10/15 22:36:13 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	mlx_draw_square(t_image *img, int width, int height,
			int color)
{
	int	h;
	int	w;

	h = -1;
	while (++h < height)
	{
		w = -1;
		while (++w < width)
		{
			ft_my_mlx_pixel_put(img, w, h, color);
		}
	}
}

int get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

/*
void	ft_print_texture(t_data *data, int x)
{
	while (data->ray_data.drawstart <= data->ray_data.drawend)
	{
		data->ray_data.texy = (int)data->ray_data.texpos & (data->textures[data->ray_data.text_select].size.y - 1);
		data->ray_data.texpos += data->ray_data.step;
		ft_my_mlx_pixel_put(data, x, data->ray_data.drawstart,
			img_add[data->textures[data->ray_data.text_select].size.x * data->ray_data.texy + data->ray_data.texx]);
		data->ray_data.drawstart++;
	}
}
*/

void	ft_print_texture(t_data *data, int x)
{
	while (data->ray_data.drawstart <= data->ray_data.drawend)
	{
		data->ray_data.texy = (int)data->ray_data.texpos & (data->textures[data->ray_data.text_select].size.y - 1);
		data->ray_data.texpos += data->ray_data.step;
		int color = get_rgba(data->textures[data->ray_data.text_select].pixels[data->textures[data->ray_data.text_select].size.y * data->ray_data.texy + data->ray_data.texx],
			data->textures[data->ray_data.text_select].pixels[data->textures[data->ray_data.text_select].size.x * data->ray_data.texy + data->ray_data.texx + 1],
			data->textures[data->ray_data.text_select].pixels[data->textures[data->ray_data.text_select].size.x * data->ray_data.texy + data->ray_data.texx + 2],
			data->textures[data->ray_data.text_select].pixels[data->textures[data->ray_data.text_select].size.x * data->ray_data.texy + data->ray_data.texx + 3]);
		//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
		if (data->ray_data.side == 1) color = (color >> 1) & 8355711;
		ft_my_mlx_pixel_put(&data->img, x, data->ray_data.drawstart, color);
		data->ray_data.drawstart++;
	}
}

/*
void	draw_texture_from_img(t_data *data, float x, float wall_height,
		int texture_pos_x)
{
	float		y_incrementer;
	float		y;
	t_vector2	vec;
	t_vector2	vec2;
	t_color		rgb;
	
	y_incrementer = (wall_height * 2) / data->pixies->img->height;
	y = data->proj.half_height - wall_height;
//	data->img_index = 0;	// je le mettrai dans mon ray_casting, selon wall - 1
	for (int i = 0; i < data->pixies->img->height * 4; i += 4)
	{
		vec = ft_floattovec2(x, y);
		vec2 = ft_floattovec2(x, y + y_incrementer);
		rgb.r = data->pixies[0].pixels[(i * data->pixies->size.x + texture_pos_x)];
		rgb.g = data->pixies[0].pixels[(i * data->pixies->size.x + texture_pos_x) + 1];
		rgb.b = data->pixies[0].pixels[(i * data->pixies->size.x + texture_pos_x) + 2];
		rgb.a = data->pixies[0].pixels[(i * data->pixies->size.x + texture_pos_x) + 3];
//		printf("%d\n", data->pixies[0].pixels[(i * data->pixies->size.x + texture_pos_x)]);
		draw_line(data->img.img, vec, vec2, rgb_to_hex(rgb));
		y += y_incrementer;
	}
}

void	draw_texture(t_data *data, float x, float wall_height,
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
		vec2 = ft_floattovec2(x, y + y_incrementer);
		draw_line(data->img.img, vec, vec2,
			rgb_to_hex(texture.colors[texture.bitmap[i][texture_pos_x] + '0']));
		y += y_incrementer;
	}
}
*/
static void	draw_line_pt2(t_image *img, t_vector2 start, t_vector2 finish,
		int color)
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
//	while (y < (int)finish.y && y > 0) // a strange effect on top of a wall is provoked when the wall is getting out of the screen; and the ceiling becomes red :o
	while (y < (int)finish.y)
	{
		x = w * (float)y + p;
		ft_my_mlx_pixel_put(img, (int)x, y, color);
		y++;
	}
}

void	draw_line(t_image *img, t_vector2 start, t_vector2 finish,
		int color)
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
			ft_my_mlx_pixel_put(img, x, (int)y, color);
			x++;
		}
	}
	else
		draw_line_pt2(img, start, finish, color);
}

void	draw_vertical_line(t_image *img, t_vector draw_start,
			int draw_end, int color)
{
	while (draw_start.y < draw_end)
	{
		ft_my_mlx_pixel_put(img, draw_start.x, draw_start.y, color);
		draw_start.y++;
	}
}
