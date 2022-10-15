/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:24:46 by faventur          #+#    #+#             */
/*   Updated: 2022/10/15 19:08:43 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	ft_update(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	data->frame++;
	if (data->frame % 30 == 0)	// 30 is the render delay
	{
		fill_window(data, 0x650000FF);
		ray_casting(data);
	}
}

void	ray_casting(t_data *data)
{
	for(int x = 0; x < WIDTH; x++)
	{
		//calculate ray position and direction
		data->ray_data.camera_x = 2 * x / (double)WIDTH - 1; //x-coordinate in camera space
		data->ray_data.raydir_x = data->ray_data.dir_x + data->ray_data.plane_x * data->ray_data.camera_x;
		data->ray_data.raydir_y = data->ray_data.dir_y + data->ray_data.plane_y * data->ray_data.camera_x;
		//which box of the map we're in
		data->ray_data.map_x = (int)data->ray_data.pos_x;
		data->ray_data.map_y = (int)data->ray_data.pos_y;

		data->ray_data.ray_delta_x = (data->ray_data.raydir_x == 0) ? 1e30 : fabs(1 / data->ray_data.raydir_x);
		data->ray_data.ray_delta_y = (data->ray_data.raydir_y == 0) ? 1e30 : fabs(1 / data->ray_data.raydir_y);

		//what direction to step in x or y-direction (either +1 or -1)
		data->ray_data.hit = 0; //was there a wall hit?
		if (data->ray_data.raydir_x < 0)
		{
			data->ray_data.step_x = -1;
			data->ray_data.ray_side_x = (data->ray_data.pos_x - data->ray_data.map_x) * data->ray_data.ray_delta_x;
		}
		else
		{
			data->ray_data.step_x = 1;
			data->ray_data.ray_side_x = (data->ray_data.map_x + 1.0 - data->ray_data.pos_x) * data->ray_data.ray_delta_x;
		}
		if (data->ray_data.raydir_y < 0)
		{
			data->ray_data.step_y = -1;
			data->ray_data.ray_side_y = (data->ray_data.pos_y - data->ray_data.map_y) * data->ray_data.ray_delta_y;
		}
		else
		{
			data->ray_data.step_y = 1;
			data->ray_data.ray_side_y = (data->ray_data.map_y + 1.0 - data->ray_data.pos_y) * data->ray_data.ray_delta_y;
		}
		//perform DDA
		while (data->ray_data.hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if (data->ray_data.ray_side_x < data->ray_data.ray_side_y)
			{
				data->ray_data.ray_side_x += data->ray_data.ray_delta_x;
				data->ray_data.map_x += data->ray_data.step_x;
				data->ray_data.side = 0;
			}
			else
			{
				data->ray_data.ray_side_y += data->ray_data.ray_delta_y;
				data->ray_data.map_y += data->ray_data.step_y;
				data->ray_data.side = 1;
			}
			//Check if ray has data->ray_data.hit a wall
			if (data->map->map[data->ray_data.map_y][data->ray_data.map_x] > 48)
			{
				data->ray_data.hit = 1;	
			}
		}
		if (data->ray_data.side == 0)
			data->ray_data.walldistance = data->ray_data.ray_side_x - data->ray_data.ray_delta_x;
		else
			data->ray_data.walldistance = data->ray_data.ray_side_y - data->ray_data.ray_delta_y;

		//Calculate height of line to draw on screen
		data->ray_data.lineheight = (int)(HEIGHT / data->ray_data.walldistance);

		//calculate lowest and highest pixel to fill in current stripe
		data->ray_data.drawstart = -data->ray_data.lineheight / 2 + HEIGHT / 2;
		if(data->ray_data.drawstart < 0) data->ray_data.drawstart = 0;
		data->ray_data.drawend = data->ray_data.lineheight / 2 + HEIGHT / 2;
		if(data->ray_data.drawend >= HEIGHT) data->ray_data.drawend = HEIGHT - 1;

		if (data->textures)
		{
		
			//texturing calculations
			data->ray_data.text_select = data->map->map[data->ray_data.map_y][data->ray_data.map_x] - 49; //1 subtracted from it so that texture 0 can be used!

			//calculate value of data->ray_data.wall_x
	 		if (data->ray_data.side == 0) data->ray_data.wall_x = data->ray_data.pos_y + data->ray_data.walldistance * data->ray_data.raydir_y;
			else           data->ray_data.wall_x = data->ray_data.pos_x + data->ray_data.walldistance * data->ray_data.raydir_x;
			data->ray_data.wall_x -= floor((data->ray_data.wall_x));

	 		//x coordinate on the texture
	 		data->ray_data.texx = (int)(data->ray_data.wall_x * (double)texWidth);
	 		if(data->ray_data.side == 0 && data->ray_data.raydir_x > 0) data->ray_data.texx = texWidth - data->ray_data.texx - 1;
			if(data->ray_data.side == 1 && data->ray_data.raydir_y < 0) data->ray_data.texx = texWidth - data->ray_data.texx - 1;

			// How much to increase the texture coordinate per screen pixel
			data->ray_data.step = 1.0 * (double)data->textures[data->ray_data.text_select].img->height / (double)data->ray_data.lineheight;
			// Starting texture coordinate
			data->ray_data.texpos = (data->ray_data.drawstart - HEIGHT / 2 + data->ray_data.lineheight / 2) * data->ray_data.step;
			ft_print_texture(data, x);
/*
			for (int y = data->ray_data.drawstart; y < data->ray_data.drawend; y++)
			{
				// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
				data->ray_data.texy = (int)data->ray_data.texpos & (data->textures[data->ray_data.text_select].img->height - 1);
				data->ray_data.texpos += data->ray_data.step;
				printf("col %d %d\n", data->ray_data.text_select, data->textures->img->width * data->ray_data.texy + data->ray_data.texx);
				uint32_t color = data->textures[data->ray_data.text_select].img->pixels[data->textures[data->ray_data.text_select].img->height * data->ray_data.texy + data->ray_data.texx];
				//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
				if (data->ray_data.side == 1) color = (color >> 1) & 8355711;
				
//				ft_uchar_arr_display(data->textures[data->ray_data.text_select].img->pixels, data->textures[data->ray_data.text_select].img->height * 4 * data->textures[data->ray_data.text_select].img->width);

			}
*/
		}
		else
		{
			//choose wall color
			t_color color;
			switch (data->map->map[data->ray_data.map_y][data->ray_data.map_x])
			{
				case 49:
					color.r = 255;
					color.g = 0;
					color.b = 0;
					color.a = 255;
					break ;
				default:
					color.r = 0;
					color.g = 255;
					color.b = 0;
					color.a = 255;
					break;
			}
			//give x and y sides different brightness
			if(data->ray_data.side == 1)
			{
				color.r /= 2;
				color.g /= 2;
				color.b /= 2;
				color.a /= 2;
			}
			printf("pix %d %d %d %d\n", x, data->ray_data.drawstart, data->ray_data.drawend, rgb_to_hex(color));
			//draw the pixels of the stripe as a vertical line
			t_vector	vec = ft_inttovec(x, data->ray_data.drawstart);
			draw_vertical_line(data->img.img, vec, data->ray_data.drawend, rgb_to_hex(color));
		}
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