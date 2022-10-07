/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:13:32 by faventur          #+#    #+#             */
/*   Updated: 2022/10/07 15:11:18 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	init_texture(t_program *data)
{
	data->texture.width = 8;
	data->texture.height = 8;
	data->texture.bitmap = ft_map_reader("texture.txt");
	data->texture.colors = malloc(sizeof(t_color) * 2);
	data->texture.colors[0].r = 255;
	data->texture.colors[0].g = 241;
	data->texture.colors[0].b = 232;
	data->texture.colors[0].a = 255;
	data->texture.colors[1].r = 195;
	data->texture.colors[1].g = 194;
	data->texture.colors[1].b = 199;
	data->texture.colors[1].a = 255;
}

void	init_struct(t_program *data)
{
	data->screen.width = WIDTH;
	data->screen.height = HEIGHT;
	data->screen.scale = 1;
	data->render.delay = 30;
	data->rc.precision = 64.0f;
	data->player.fov = 60.0f;
	data->player.x = 6.0f;
	data->player.y = 2.0f;
	data->player.angle = 90.0f;
	data->screen.half_width = data->screen.width / 2;
	data->screen.half_height = data->screen.height / 2;
	data->player.half_fov = data->player.fov / 2;
	data->player.speed.movement = 0.5f;
	data->player.speed.rotation = 5.0f;
	data->proj.width = data->screen.width / data->screen.scale;
	data->proj.height = data->screen.height / data->screen.scale;
	data->proj.half_width = data->proj.width / 2;
	data->proj.half_height = data->proj.height / 2;
	data->rc.increment_angle = data->player.fov / data->proj.width;
	init_texture(data);
}

void	calculate_map_size(t_program *data)
{
	data->map.height = 0;
	while (data->map.map[data->map.height])
	{
		data->map.width = 0;
		while (data->map.map[data->map.height][data->map.width])
		{
			data->map.width++;
		}
		data->map.height++;
	}
}

int	main(int argc, char *argv[])
{
	t_program	program;
	int			i;

	i = 0;
	check(argc, argv);
//	if (!program.map.map || !ft_map_parser(program.map.map))
//		ft_puterror("Error!");
	init_struct(&program);
	program.map.map = ft_map_reader(argv[1]);
	if (!program.map.map)
		ft_puterror("Error!");
	program.frame = 0;
	program.mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	program.img.img = mlx_new_image(program.mlx, WIDTH, HEIGHT);
	if (!program.img.img) //|| (mlx_image_to_window(program.mlx,
			//	program.img.img, 0, 0) < 0))
		ft_puterror("Error!");
//	program.pixies = ft_put_sprite(&program);
//	ft_display_map(&program, program.pixies);
	mlx_image_to_window(program.mlx, program.img.img, 0, 0);
	mlx_loop_hook(program.mlx, ft_update, &program);
	mlx_key_hook(program.mlx, ft_key_input, &program);
	mlx_loop(program.mlx);
	mlx_terminate(program.mlx);
}
