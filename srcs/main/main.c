/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:13:32 by faventur          #+#    #+#             */
/*   Updated: 2022/10/24 17:33:11 by faventur         ###   ########.fr       */
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
		ray->plane.y = (double)data->player.fov / 100;
	}
	if (data->map->dir == 'W')
	{
		ray->dir.x = 1;
		ray->dir.y = 0;
		ray->plane.x = 0;
		ray->plane.y = -(double)data->player.fov / 100;
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
		ray->plane.x = -(double)data->player.fov / 100;
		ray->plane.y = 0;
	}
	if (data->map->dir == 'S')
	{
		ray->dir.x = 0;
		ray->dir.y = 1;
		ray->plane.x = (double)data->player.fov / 100;
		ray->plane.y = 0;
	}
	init_direction_child(data, ray);
}

void	init_struct(t_data *data)
{
	t_ray	*ray;

	ray = &data->ray_data;
	ray->pos.x = 0.5 + data->map->spawn_pos.x;
	ray->pos.y = 0.5 + data->map->spawn_pos.y;
	data->player.speed.movement = 0.2;
	data->player.speed.rotation = 0.3;
	ray->pcos = cos(data->player.speed.rotation);
	ray->psin = sin(data->player.speed.rotation);
	ray->ncos = cos(-data->player.speed.rotation);
	ray->nsin = sin(-data->player.speed.rotation);
	data->frame = 0;
	data->render_delay = 1;
	ray->text_select = 0;
	data->refresh = 1;
	data->screen.resolution.x = WIDTH;
	data->screen.resolution.y = HEIGHT + MAPHEIGHT;
	data->screen.display.size.x = WIDTH;
	data->screen.display.size.y = HEIGHT;
	data->screen.map_display.size.x = MAPWIDTH;
	data->screen.map_display.size.y = MAPHEIGHT;
	ray->resolution.x = data->screen.display.size.x;
	ray->resolution.y = data->screen.display.size.y;
	data->player.fov = 70;
	ray->tex_buf = malloc(sizeof(uint32_t *) * 4);
	init_direction(data);
}

int	main(int argc, char *argv[])
{
	t_data	program;

	program.map = check(argc, argv);
	if (!program.map->map)
		ft_puterror("Error!");
	init_struct(&program);
	program.mlx = mlx_init(program.screen.resolution.x,
			program.screen.resolution.y, "cub3d", true);
	program.screen.display.img = mlx_new_image(program.mlx,
			program.screen.display.size.x, program.screen.display.size.y);
	if (!program.screen.display.img)
		throw_err_ex("Error : Creating new MLX image failed.");
	program.screen.map_display.img = mlx_new_image(program.mlx,
			program.screen.map_display.size.x, program.screen.map_display.size.y);
	if (!program.screen.map_display.img)
		throw_err_ex("Error : Creating new MLX image failed.");
	mlx_image_to_window(program.mlx, program.screen.map_display.img,
		0, program.screen.display.size.y);
	program.textures = NULL;
	program.textures = ft_load_textures(&program);
	if (!program.textures)
		throw_err_ex("Error : Loading texture failed.");
//	ft_display_map(&program, &program.textures[4]);
	mlx_image_to_window(program.mlx, program.screen.display.img, 0, 0);
	mlx_loop_hook(program.mlx, ft_update, &program);
	mlx_key_hook(program.mlx, ft_key_input, &program);
	mlx_loop(program.mlx);
	mlx_terminate(program.mlx);
}
