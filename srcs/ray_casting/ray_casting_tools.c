/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:24:46 by faventur          #+#    #+#             */
/*   Updated: 2022/10/31 16:00:56 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

t_sprite	sprite[numSprites] =
			{
			{3, 3, 6},
			{4, 3, 7},
			{5, 3, 8}
			};
double		z_buffer[WIDTH];
int			sprite_order[numSprites];
double		sprite_distance[numSprites];

void	sort_sprites(int* order, double* dist, int amount)
{
	int		i;
	int		tmp;
	double	tmp_dist;

	i = 0;
	tmp = 0;
	tmp_dist = 0;
	while (i < amount - 1)
	{
		if (dist[i] < dist[i + 1])
		{
			tmp_dist = dist[i];
			tmp = order[i];
			dist[i] = dist[i + 1];
			order[i] = order[i + 1];
			dist[i + 1] = tmp_dist;
			order[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
	i = 0;
}

void	sprite_caster(t_data *data, t_ray *ray, t_var var)
{
	for(int i = 0; i < numSprites; i++)
	{
		sprite_order[i] = i;
		sprite_distance[i] = ((ray->pos.x - sprite[i].x) * (ray->pos.x - sprite[i].x) + (ray->pos.y - sprite[i].y) * (ray->pos.y - sprite[i].y)); //sqrt not taken, unneeded
	}
	sort_sprites(sprite_order, sprite_distance, numSprites);
	//after sorting the sprites, do the projection and draw them
	for(int i = 0; i < numSprites; i++)
	{
		//translate sprite position to relative to camera
		double spriteX = sprite[sprite_order[i]].x - ray->pos.x;
		double spriteY = sprite[sprite_order[i]].y - ray->pos.y;

		double invDet = 1.0 / (ray->plane.x * ray->dir.y - ray->dir.x * ray->plane.y); //required for correct matrix multiplication

		double transformX = invDet * (ray->dir.y * spriteX - ray->dir.x * spriteY);
		double transformY = invDet * (-ray->plane.y * spriteX + ray->plane.x * spriteY); //this is actually the depth inside the screen, that what Z is in 3D

		int spriteScreenX = (int)((WIDTH / 2) * (1 + transformX / transformY));

		//calculate height of the sprite on screen
		int spriteHeight = abs((int)(HEIGHT / (transformY))); //using 'transformY' instead of the real distance prevents fisheye
		//calculate lowest and highest pixel to fill in current stripe
		int drawStartY = -spriteHeight / 2 + HEIGHT / 2;
		if(drawStartY < 0) drawStartY = 0;
		int drawEndY = spriteHeight / 2 + HEIGHT / 2;
		if(drawEndY >= HEIGHT) drawEndY = HEIGHT - 1;

		//calculate width of the sprite
		int spriteWidth = abs((int)(HEIGHT / (transformY)));
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if(drawStartX < 0) drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if(drawEndX >= WIDTH) drawEndX = WIDTH - 1;

		//loop through every vertical stripe of the sprite on screen
		for(int stripe = drawStartX; stripe < drawEndX; stripe++)
		{
			int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * var.width / spriteWidth) / 256;
			if(transformY > 0 && stripe > 0 && stripe < WIDTH && transformY < z_buffer[stripe])
			for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
			{
				int d = (y) * 256 - HEIGHT * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
				int texY = ((d * var.height) / spriteHeight) / 256;
				var.color = ray->tex_buf[sprite[sprite_order[i]].texture][var.width * texY + texX]; //get current color from the texture
				if((var.color & 0xFFFFFF00) != 0)
					mlx_put_pixel(data->screen.display.img, stripe, y, var.color);
			}
		}
	}
}

void	ray_casting(t_data *data)
{
	t_ray		*ray;
	size_t		x;
	t_var	var;		// sprites

	ft_bzero(&var, sizeof(var));	// sprites
	x = 0;
	ray = &data->ray_data;
	ray->map = data->map;
	var.width = 64;	// sprites
	var.height = 64;	// sprites
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
		z_buffer[x] = ray->wall_distance;
		++x;
	}
	sprite_caster(data, ray, var);
}
