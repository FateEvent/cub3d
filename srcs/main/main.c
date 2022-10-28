/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:13:32 by faventur          #+#    #+#             */
/*   Updated: 2022/10/28 16:48:00 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

static void	init_direction_child(t_data *data, t_ray *ray)
{
	if (data->map->dir == 'E')
	{
		ray->dir.x = 1;
		ray->dir.y = 0;
		ray->plane.x = 0;
		ray->plane.y = (double)data->player.fov / 100;
	}
	if (data->map->dir == 'W')
	{
		ray->dir.x = -1;
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
	t_ray	*ray;

	ray = &data->ray_data;
	ft_bzero(ray, sizeof(*ray));
	ray->pos.x = 0.5 + data->map->spawn_pos.x;
	ray->pos.y = 0.5 + data->map->spawn_pos.y;
	data->player.speed.movement = 0.2;
	data->player.speed.rotation = 0.3;
	ray->k.pcos = cos(data->player.speed.rotation);
	ray->k.psin = sin(data->player.speed.rotation);
	ray->k.ncos = cos(-data->player.speed.rotation);
	ray->k.nsin = sin(-data->player.speed.rotation);
	ray->m.pcos = cos(data->player.speed.rotation / 2);
	ray->m.psin = sin(data->player.speed.rotation / 2);
	ray->m.ncos = cos(-data->player.speed.rotation / 2);
	ray->m.nsin = sin(-data->player.speed.rotation / 2);
	ray->half_width = WIDTH / 2;
	data->render_delay = 1;
	ray->text_select = 0;
	data->refresh = 1;
	data->screen.resolution.x = WIDTH;
	data->screen.resolution.y = HEIGHT;
	data->screen.display.size.x = WIDTH;
	data->screen.display.size.y = HEIGHT;
	data->screen.map_display.size.x = MAPWIDTH;
	data->screen.map_display.size.y = MAPHEIGHT;
	ray->resolution.x = data->screen.display.size.x;
	ray->resolution.y = data->screen.display.size.y;
	data->player.fov = 70;
	ray->tex_buf = malloc(sizeof(uint32_t *) * 6);
	init_direction(data);
	ray->m.focus = 0;
}

int	main(int argc, char *argv[])
{
	t_data	program;

	ft_bzero(&program, sizeof(program));
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
	program.textures = NULL;
	program.textures = ft_load_textures(&program);
	if (!program.textures)
		throw_err_ex("Error : Loading texture failed.");
	program.map->minimap = malloc(sizeof(t_minimap));
	program.map->minimap->img = NULL;
	program.map->minimap->img = mlx_new_image(program.mlx, 210, 150);
	program.map->minimap->pos.x = program.ray_data.pos.x;
	program.map->minimap->pos.y = program.ray_data.pos.y;
	get_map_size(&program);
	get_map_str(&program);
	mlx_set_cursor_mode(program.mlx, MLX_MOUSE_HIDDEN);
	mlx_image_to_window(program.mlx, program.screen.display.img, 0, 0);
	mlx_loop_hook(program.mlx, ft_update, &program);
	mlx_key_hook(program.mlx, ft_key_input, &program);
	mlx_cursor_hook(program.mlx, ft_mouse_input, &program);
	mlx_loop_hook(program.mlx, ft_update, &program);
	mlx_loop(program.mlx);
}
