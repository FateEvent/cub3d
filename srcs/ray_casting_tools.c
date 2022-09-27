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
/*
void	ray_calculator(t_program *data, t_vector *ray, uint32_t	ray_angle)
{
	uint32_t	ray_cos;
	uint32_t	ray_sin;

	ray_cos = cos(degrees_to_radians(ray_angle)) / data->rc->precision;
	ray_sin = sin(degrees_to_radians(ray_angle)) / data->rc->precision;
}
*/
void	ray_casting(t_program *data)
{
	double	ray_angle;
	double	ray_count;
	t_vector	ray;
	double		ray_cos;
	double		ray_sin;
	double	wall;
	double	distance;
	double	wall_height;

	ray_angle = data->player->angle - data->player->half_fov;
	ray_count = 0;
	wall_height = 0;
	while (ray_count < data->screen->width)
	{
		ray.x = data->player->x;
		ray.y = data->player->y;
		ray_cos = cos(degrees_to_radians(ray_angle)) / data->rc->precision;
		ray_sin = sin(degrees_to_radians(ray_angle)) / data->rc->precision;
		wall = 0;
		while (wall == 0)
		{
			ray.x += ray_cos;
			ray.y += ray_sin;

			ft_printf("%s\n", data->map[(uint32_t)floor(ray.y)]);
			wall = data->map[(uint32_t)floor(ray.y)][(uint32_t)floor(ray.x)];
		}
		distance = sqrt(pow(data->player->x - ray.x, 2) + pow(data->player->y - ray.y, 2));
		wall_height = (uint32_t)floor(data->screen->half_height / distance);
		mlx_draw_line(data->img.img, ray_count, 0, ray_count, data->screen->half_height - wall_height, 0x00FFFFFF);
		mlx_draw_line(data->img.img, ray_count, data->screen->half_height - wall_height, ray_count, data->screen->half_height + wall_height, 0xC70039FF);
		mlx_draw_line(data->img.img, ray_count, data->screen->half_height + wall_height, ray_count, data->screen->half_height,  0xDAF7A6FF);

		// Increment
		ray_angle += data->rc->increment_angle;
		ray_count++;
	}
}

uint32_t	degrees_to_radians(uint32_t degrees)
{
	return (degrees * M_PI / 180);
}
