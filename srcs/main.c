/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:13:32 by faventur          #+#    #+#             */
/*   Updated: 2022/10/15 22:29:04 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"
/*
void	init_texture(t_data *data)
{
	data->textures.width = 8;
	data->textures.height = 8;
	data->textures.bitmap = ft_map_reader("texture.txt");
	data->textures.colors = malloc(sizeof(t_color) * 2);
	data->textures.colors[0].r = 255;
	data->textures.colors[0].g = 241;
	data->textures.colors[0].b = 232;
	data->textures.colors[0].a = 255;
	data->textures.colors[1].r = 195;
	data->textures.colors[1].g = 194;
	data->textures.colors[1].b = 199;
	data->textures.colors[1].a = 255;
}
*/
/*
void	init_struct(t_program *data)
{
	data->screen.width = WIDTH;
	data->screen.height = HEIGHT;
	data->screen.scale = 1;
	data->render.delay = 1;
	data->rc.precision = 64.0f;
	data->player.fov = 60.0f;
	data->player.x = 16.0f;
	data->player.y = 4.0f;
	data->player.angle = 90.0f;
	data->screen.half_width = data->screen.width / 2;
	data->screen.half_height = data->screen.height / 2;
	data->player.half_fov = data->player.fov / 2;
	data->player.speed.movement = 0.05f;
	data->player.speed.rotation = 3.0f;
	data->proj.width = data->screen.width / data->screen.scale;
	data->proj.height = data->screen.height / data->screen.scale;
	data->proj.half_width = data->proj.width / 2;
	data->proj.half_height = data->proj.height / 2;
	data->rc.increment_angle = data->player.fov / data->proj.width;
	data->player.radius = 10;
	init_texture(data);
}
*/

void	init_struct(t_data *data)
{
	data->ray_data.pos_x = 16.0;
	data->ray_data.pos_y = 4.0;
	data->ray_data.dir_x = -1.0;
	data->ray_data.dir_y = 0.0;
	data->ray_data.plane_x = 0.0;
	data->ray_data.plane_y = 0.66;
	data->move_speed = 0.05;
	data->rotate_speed = 2;
	data->frame = 0;
	data->render_delay = 30;
}

int	main(int argc, char *argv[])
{
	t_data	program;
	int		i;

	i = 0;
	program.map = check(argc, argv);
	if (!program.map->map)
		ft_puterror("Error!");
	init_struct(&program);
	program.mlx = mlx_init();
	program.window = ft_new_window(program.mlx, WIDTH, HEIGHT, "cub3d");
	if (!program.window.reference)
		throw_err_ex("Error: Failed to create a new MLX image.");
	program.img = ft_new_image(program.mlx, WIDTH, HEIGHT);
	program.textures = NULL;
	program.textures = ft_load_textures(&program);
	if (!program.textures)
		throw_err_ex("Error: Failed to load texture.");
	mlx_put_image_to_window(program.mlx, program.window.reference,
		program.img.reference, 0, 0);
	mlx_key_hook(program.window.reference, ft_key_input, &program);
	mlx_loop_hook(program.mlx, ft_update, &program);
	mlx_loop(program.mlx);
}
