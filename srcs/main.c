/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:13:32 by faventur          #+#    #+#             */
/*   Updated: 2022/10/20 17:55:42 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

static void	init_direction_child(t_data *data, t_ray *ray)
{
	 if (data->map->dir == 'E')
	{
		ray->dir.x = -1;
		ray->dir.y = 0;
		ray->plane.x = 0;
		ray->plane.y = -(double)data->player.fov / 100;
	}
	if (data->map->dir == 'W')
	{
		ray->dir.x = 1;
		ray->dir.y = 0;
		ray->plane.x = 0;
		ray->plane.y = (double)data->player.fov / 100;
	}
}

void	init_direction(t_data *data)
{
	t_ray	*ray;

	ray = &data->ray_data;
	if (data->map->dir == 'N')
	{
		ray->dir.x = 0;
		ray->dir.y = -1;
		ray->plane.x = (double)data->player.fov / 100;
		ray->plane.y = 0;
		
	}
	if (data->map->dir == 'S')
	{
		ray->dir.x = 0;
		ray->dir.y = 1;
		ray->plane.x = -(double)data->player.fov / 100;
		ray->plane.y = 0;
	}
	init_direction_child(data, ray);
		
}

void	init_struct(t_data *data)
{
	data->ray_data.pos.x = data->map->spawn_pos.x;
	data->ray_data.pos.y = data->map->spawn_pos.y;
	data->player.speed.movement = 0.3;
	data->player.speed.rotation = 0.05;
	data->frame = 0;
	data->render_delay = 30;
	data->ray_data.text_select = 0;
	data->refresh = 1;
	data->resolution.x = WIDTH;
	data->resolution.y = HEIGHT;
	data->ray_data.resolution.x = data->resolution.x;
	data->ray_data.resolution.y = data->resolution.y;
	data->player.fov = 70;
	init_direction(data);
}

int	main(int argc, char *argv[])
{
	t_data	program;

	program.map = check(argc, argv);
	if (!program.map->map)
		ft_puterror("Error!");
	init_struct(&program);
	program.mlx = mlx_init(program.resolution.x, program.resolution.y,
			"cub3d", true);
	program.img.img = mlx_new_image(program.mlx, program.resolution.x,
			program.resolution.y);
	if (!program.img.img)
		throw_err_ex("Error : Creating new MLX image failed.");
	program.textures = NULL;
	program.textures = ft_load_textures(&program);
	if (!program.textures)
		throw_err_ex("Error : Loading texture failed.");
	mlx_image_to_window(program.mlx, program.img.img, 0, 0);
	mlx_loop_hook(program.mlx, ft_update, &program);
	mlx_key_hook(program.mlx, ft_key_input, &program);
	mlx_loop(program.mlx);
	mlx_terminate(program.mlx);
}
