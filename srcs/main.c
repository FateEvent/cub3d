/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:13:32 by faventur          #+#    #+#             */
/*   Updated: 2022/10/19 16:11:32 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	init_struct(t_data *data)
{
	data->ray_data.pos.x = 16.0;
	data->ray_data.pos.y = 4.0;
	data->ray_data.dir.x = -1.0;
	data->ray_data.dir.y = 0.0;
	data->ray_data.plane.x = 0.0;
	data->ray_data.plane.y = 0.66;
	data->player.speed.movement = 0.3;
	data->player.speed.rotation = 0.05;
	data->frame = 0;
	data->render_delay = 30;
	data->ray_data.text_select = 0;
	data->refresh = 1;
}

int	main(int argc, char *argv[])
{
	t_data	program;

	program.map = check(argc, argv);
	if (!program.map->map)
		ft_puterror("Error!");
	init_struct(&program);
	program.mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	program.img.img = mlx_new_image(program.mlx, WIDTH, HEIGHT);
	if (!program.img.img)
		throw_err_ex("Error : Creating new MLX image failed.");
	program.textures = NULL;
	program.textures = ft_load_textures(&program);
	//if (!program.pixies)
	//	throw_err_ex("Error : Loading texture failed.");
	mlx_image_to_window(program.mlx, program.img.img, 0, 0);
	mlx_loop_hook(program.mlx, ft_update, &program);
	mlx_key_hook(program.mlx, ft_key_input, &program);
	mlx_loop(program.mlx);
	mlx_terminate(program.mlx);
}
