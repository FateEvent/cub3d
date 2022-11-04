/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:13:32 by faventur          #+#    #+#             */
/*   Updated: 2022/11/04 13:17:57 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

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
	mlx_set_cursor_mode(program.mlx, MLX_MOUSE_HIDDEN);
	mlx_image_to_window(program.mlx, program.screen.display.img, 0, 0);
	mlx_loop_hook(program.mlx, ft_update, &program);
	mlx_key_hook(program.mlx, ft_key_hook, &program);
	mlx_cursor_hook(program.mlx, ft_mouse_input, &program);
	mlx_loop_hook(program.mlx, ft_update, &program);
	mlx_loop(program.mlx);
}
