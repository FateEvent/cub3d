#include "mlx_utils.h"

void	fill_window(t_program *data, uint32_t color)
{
	mlx_image_t	*frame;

	frame = data->img.img;
	mlx_draw_square(frame, frame->width, frame->height, color);
}

float	degree_to_radians(float degrees)
{
	return (degrees * M_PI / 180);
}

float	vector_distance_calc(t_vector2 start, t_vector2 finish)
{
	float	distance;

	distance = sqrt(pow(start.x, finish.x) + pow(start.y, finish.y));
	return (distance);
}

t_vector2	ft_floattovec2(float x, float y)
{
	t_vector2	vec;

	vec.x = x;
	vec.y = y;
	return (vec);
}

void	ft_vec2_swap(t_vector2 *start, t_vector2 *finish)
{
	t_vector2	tmp;

	tmp.x = start->x;
	tmp.y = start->y;
	start->x = finish->x;
	start->y = finish->y;
	finish->x = tmp.x;
	finish->y = tmp.y;
}
void	plot_line(mlx_image_t *img, t_vector2 start, t_vector2 finish,
		uint32_t color)
{
	int	dx = finish.x - start.x;
	int dy = finish.y - start.y;
	int D = 2*dy - dx;
	int y = start.y;

	int x = start.x;
	while (x < finish.x)
	{
		mlx_put_pixel(img, x, y, color);
		if (D > 0)
		{
			y = y + 1;
			D = D - 2*dx;
		}
		D = D + 2*dy;
		x++;
	}
}

void	draw_line_pt2(mlx_image_t *img, t_vector2 start, t_vector2 finish,
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
	while (y <= (int)finish.y)
	{
		x = w * (float)y + p;
		mlx_put_pixel(img, (int)x, y, color);
		y++;
	}
}

void	draw_line(mlx_image_t *img, t_vector2 start, t_vector2 finish,
		uint32_t color)
{
	float	distance;
	float	m;
	float	b;
	int		x;
	float	y;

	if (finish.x != start.x)
		m = (finish.y - start.y) / (finish.x - start.x);
	if (finish.x != start.x && fabsf(m) <= 1)
	{
		distance = vector_distance_calc(start, finish);
		if (start.x > finish.x)
			ft_vec2_swap(&start, &finish);
		b = start.y - m * start.x;
		x = (int)start.x;
		while (x <= (int)finish.x)
		{
			y = m * (float)x + b;
			mlx_put_pixel(img, x, (int)y, color);
			x++;
		}
	}
	else
		draw_line_pt2(img, start, finish, color);
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
	t_vector2	vec;
	t_vector2	vec2;
	t_vector2	vec3;
	t_vector2	vec4;

	vec = ft_floattovec2(45, 6);
	vec2 = ft_floattovec2(400, 90);
	vec3 = ft_floattovec2(45, 9);
	vec4 = ft_floattovec2(45, 50);
	vec5 = ft_floattovec2(45, 26);
	vec6 = ft_floattovec2(400, 110);
	draw_line(data->img.img, vec, vec2, 0xFFFFFFFF);
	draw_line(data->img.img, vec3, vec4, 0xFFFFFFFF);
}
