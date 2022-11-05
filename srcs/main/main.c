/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:13:32 by faventur          #+#    #+#             */
/*   Updated: 2022/11/05 18:35:24 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	into_the_loop(t_data *data, t_ray *ray, t_var *var)
{
	var->i = 0;
	while (var->i < var->height)
	{
		ray->door.door_timers[var->i] = ft_calloc(var->width, sizeof(double *));
		ray->door.door_offsets[var->i] = ft_calloc(var->width, sizeof(double *));
		var->j = 0;
		while (var->j < var->width)
		{
			if (data->map->map[var->i][var->j] == '2')
			{
				ray->door.door_timers[var->i][var->j] = 1;
				ray->door.door_offsets[var->i][var->j] = 1;
			}
			var->j++;
		}
		var->i++;
	}
}

void	create_door_arrays(t_data *data)
{
	t_ray	*ray;
	t_var	var;

	ft_bzero(&var, sizeof(var));
	ray = &data->ray_data;
	var.width = data->map->size.x;
	var.height = data->map->size.y;
	ray->door.door_timers = ft_calloc(var.height, sizeof(double *));
	ray->door.door_offsets = ft_calloc(var.height, sizeof(double *));
	if (!ray->door.door_timers || !ray->door.door_offsets)
		return ;
	into_the_loop(data, ray, &var);
}

int	main(int argc, char *argv[])
{
	t_data	program;

	ft_bzero(&program, sizeof(program));
	program.map = check(argc, argv);
	if (!program.map->map)
		ft_puterror("Error!");
	init_struct(&program);
	program.mlx = mlx_init(program.screen.display.size.x,
			program.screen.display.size.y, "cub3d", true);
	program.screen.display.img = mlx_new_image(program.mlx,
			program.screen.display.size.x, program.screen.display.size.y);
	if (!program.screen.display.img)
		throw_err_ex("Error : Creating new MLX image failed.");
	program.textures = NULL;
	program.textures = ft_load_textures(&program);
	if (!program.textures)
		throw_err_ex("Error : Loading texture failed.");
	init_minimap(&program);
	sprite_casting_init(&program, &program.ray_data);
	
	ft_print_map(program.map->map);
	mlx_set_cursor_mode(program.mlx, MLX_MOUSE_HIDDEN);
	mlx_image_to_window(program.mlx, program.screen.display.img, 0, 0);
	mlx_loop_hook(program.mlx, ft_update, &program);
	mlx_key_hook(program.mlx, ft_key_hook, &program);
	mlx_cursor_hook(program.mlx, ft_mouse_input, &program);
	mlx_loop_hook(program.mlx, ft_update, &program);
	mlx_loop(program.mlx);
}
