/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:13:32 by faventur          #+#    #+#             */
/*   Updated: 2022/11/07 11:51:39 by albaur           ###   ########.fr       */
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
	t_data	data;

	ft_bzero(&data, sizeof(data));
	data.map = check(argc, argv);
	if (!data.map->map)
		ft_puterror("Error!");
	init_struct(&data);
	data.mlx = mlx_init(data.screen.display.size.x,
			data.screen.display.size.y, "cub3d", true);
	data.screen.display.img = mlx_new_image(data.mlx,
			data.screen.display.size.x, data.screen.display.size.y);
	if (!data.screen.display.img)
		throw_err_ex("Error : Creating new MLX image failed.");
	data.textures = NULL;
	data.textures = ft_load_textures(&data);
	if (!data.textures)
		throw_err_ex("Error : Loading texture failed.");
	init_minimap(&data);
	init_enemy(&data);
	mlx_set_cursor_mode(data.mlx, MLX_MOUSE_HIDDEN);
	mlx_image_to_window(data.mlx, data.screen.display.img, 0, 0);
	mlx_loop_hook(data.mlx, ft_update, &data);
	mlx_key_hook(data.mlx, ft_key_hook, &data);
	mlx_cursor_hook(data.mlx, ft_mouse_input, &data);
	mlx_loop_hook(data.mlx, ft_update, &data);
	mlx_loop(data.mlx);
}
