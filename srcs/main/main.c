/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:13:32 by faventur          #+#    #+#             */
/*   Updated: 2022/11/08 17:27:58 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

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
	init_hud(&data);
	create_door_arrays(&data);
	if (!data.ray_data.door.door_timers || !data.ray_data.door.door_offsets
		|| !data.ray_data.door.door_states)
		throw_err_ex("Error : Malloc failed.");
	mlx_set_cursor_mode(data.mlx, MLX_MOUSE_HIDDEN);
	mlx_image_to_window(data.mlx, data.screen.display.img, 0, 0);
	mlx_loop_hook(data.mlx, ft_update, &data);
	mlx_key_hook(data.mlx, ft_key_hook, &data);
	mlx_cursor_hook(data.mlx, ft_mouse_input, &data);
	mlx_loop(data.mlx);
}
