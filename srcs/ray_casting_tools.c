#include "mlx_utils.h"

void	fill_window(t_program *data, uint32_t color)
{
	mlx_image_t	*frame;

	frame = data->img.img;
	mlx_draw_square(frame, frame->width, frame->height, color);
}

void	ft_update(void *param)
{
	t_program	*program;

	program = (t_program *)param;
	program->frame++;
	if (program->frame % program->render->delay == 0)
	{
		fill_window(program, 0xFF0000FF);
		ray_casting(program);
	}
}

void	ray_casting(t_program *data)
{
	double posX = 22, posY = 12;  //x and y start position
	double dirX = -1, dirY = 0; //initial direction vector
	double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane
	for(int x = 0; x < data->map->width; x++)
	{
		//calculate ray position and direction
		double cameraX = 2 * x / (double)data->map->width - 1; //x-coordinate in camera space
		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;
		//which box of the map we're in
		int mapX = (int)posX;
		int mapY = (int)posY;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;
		double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		//calculate step and initial sideDist
		if(rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}
		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			ft_printf("%d, %d", mapX, mapY);
			if (data->map->map[mapX][mapY] > 0) hit = 1;
		}
		if (side == 0) perpWallDist = (sideDistX - deltaDistX);
		else          perpWallDist = (sideDistY - deltaDistY);
		//Calculate height of line to draw on screen
		int lineHeight = (int)(data->map->height / perpWallDist);
		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + data->map->height / 2;
		if(drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + data->map->height / 2;
		if(drawEnd >= data->map->height) drawEnd = data->map->height - 1;

		//choose wall color
		uint32_t	color;
		switch(data->map->map[mapX][mapY])
		{
			case 1:  color = 0xFF000000; break; //red
			default: color = 0xFFFF0000; break; //yellow
		}
		//give x and y sides different brightness
		if(side == 1) {color = color / 2;}
		//draw the pixels of the stripe as a vertical line
		draw_vertical_line(data->img.img, x, drawStart, drawEnd, 0xFFFFFFFF);
	}
}

uint32_t	degrees_to_radians(uint32_t degrees)
{
	return (degrees * M_PI / 180);
}
