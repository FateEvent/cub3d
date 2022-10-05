#include "mlx_utils.h"

void	fill_window(t_program *data, uint32_t color)
{
	mlx_image_t	*frame;

	frame = data->img.img;
	mlx_draw_square(frame, frame->width, frame->height, color);
}

double	degree_to_radians(double degrees)
{
	return (degrees * M_PI / 180);
}

double	vector_distance_calc(t_vector2 start, t_vector2 finish)
{
	double	distance;

	distance = sqrt(pow(start.x, finish.x) + pow(start.y, finish.y));
	return (distance);
}

void	draw_line(t_vector2 start, t_vector2 finish)
{
	double	distance;

	distance = vector_distance_calc(start, finish);


}

void	ft_update(void *param)
{
	t_program	*program;

	program = (t_program *)param;
	program->frame++;
	if (program->frame % program->render->delay == 0)
	{
		fill_window(program, 0x650000FF);
		ray_casting(program);
	}
}

void	ray_casting(t_program *data)
{
	(void)data;
}
