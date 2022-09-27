/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:13:32 by faventur          #+#    #+#             */
/*   Updated: 2022/09/27 10:29:09 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	ft_hook(void* param)
{
	const mlx_t* mlx;

	mlx = param;
//	ft_printf("WIDTH: %d | HEIGHT: %d\n", mlx->width, mlx->height);
}

void	init_struct_child(t_program *data, t_vector size)
{
	(void)size;
	data->screen->width = WIDTH;
	data->screen->height = HEIGHT;
	data->render->delay = 30;
	data->rc->precision = 64;
	data->player->fov = 60;
	data->player->x = 6;
	data->player->y = 2;
	data->player->angle = 90;
	data->screen->half_width = data->screen->width / 2;
	data->screen->half_height = data->screen->height / 2;
	data->rc->increment_angle = data->player->angle / data->screen->width;
	data->player->half_fov = data->player->fov / 2;
}

void	init_struct(t_program *data, t_vector size)
{
	data->screen = malloc(sizeof(*data->screen));
	data->render = malloc(sizeof(*data->render));
	data->rc = malloc(sizeof(*data->rc));
	data->player = malloc(sizeof(*data->player));
	if (!data->screen || !data->render || !data->rc || !data->player)
	{
		if (data->screen)
			free(data->screen);
		if (data->render)
			free(data->render);
		if (data->rc)
			free(data->rc);
		if (data->player)
			free(data->player);
		exit(1);
	}
	init_struct_child(data, size);
}

int	main(int argc, char *argv[])
{
	t_program	program;
	t_vector	size;
	int			i;

	i = 0;
	check_args(argc);
//	check_map_extension(argv);
	program.map = ft_map_reader(argv[1]);
//	if (!program.map || !ft_map_parser(program.map))
//		ft_puterror("Error!");
	if (!program.map)
		ft_puterror("Error!");
	size = calculate_window_size(program.map);
	init_struct(&program, size);
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
//	mlx_loop_hook(program.mlx, ft_hook, program.mlx);
	mlx_loop(program.mlx);
	mlx_terminate(program.mlx);
}
