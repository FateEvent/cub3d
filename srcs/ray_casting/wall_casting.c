#include "mlx_utils.h"

void	wall_distance_calculator(t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_distance = (ray->ray_side.x - ray->ray_delta.x);
	else
		ray->wall_distance = (ray->ray_side.y - ray->ray_delta.y);
}

void	ray_launcher(t_ray *ray)
{
	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->ray_side.x < ray->ray_side.y)
		{
			ray->ray_side.x += ray->ray_delta.x;
			ray->map_pos.x += ray->step_coord.x;
			ray->side = 0;
		}
		else
		{
			ray->ray_side.y += ray->ray_delta.y;
			ray->map_pos.y += ray->step_coord.y;
			ray->side = 1;
		}
		if (ray->map->map[ray->map_pos.y][ray->map_pos.x] > 48)
			ray->hit = 1;
	}
}

void	rayside_calculator(t_ray *ray)
{
	if (ray->ray_dir.x < 0)
	{
		ray->step_coord.x = -1;
		ray->ray_side.x = (ray->pos.x - ray->map_pos.x) * ray->ray_delta.x;
	}
	else
	{
		ray->step_coord.x = 1;
		ray->ray_side.x = (ray->map_pos.x + 1.0 - ray->pos.x) * ray->ray_delta.x;
	}
	if (ray->ray_dir.y < 0)
	{
		ray->step_coord.y = -1;
		ray->ray_side.y = (ray->pos.y - ray->map_pos.y) * ray->ray_delta.y;
	}
	else
	{
		ray->step_coord.y = 1;
		ray->ray_side.y = (ray->map_pos.y + 1.0 - ray->pos.y) * ray->ray_delta.y;
	}
}

void	ray_delta_calculator(t_ray *ray)
{
	ray->ray_delta.x = (ray->ray_dir.x == 0) ? 1e30 : fabs(1 / ray->ray_dir.x);
	ray->ray_delta.y = (ray->ray_dir.y == 0) ? 1e30 : fabs(1 / ray->ray_dir.y);
}

void	ray_data_init(t_data *data, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)WIDTH - 1;
	ray->ray_dir.x = ray->dir.x + ray->plane.x * ray->camera_x;
	ray->ray_dir.y = ray->dir.y + ray->plane.y * ray->camera_x;
	ray->map_pos.x = (int)ray->pos.x;
	ray->map_pos.y = (int)ray->pos.y;
	ray_delta_calculator(ray);
	ray->map = data->map;
}
