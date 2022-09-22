/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:13:32 by faventur          #+#    #+#             */
/*   Updated: 2022/09/22 16:09:17 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

static void ft_hook(void* param)
{
	const mlx_t* mlx;

	mlx = param;
//	ft_printf("WIDTH: %d | HEIGHT: %d\n", mlx->width, mlx->height);
}

int	main(int argc, char *argv[])
{
	t_program	program;
	int			i;

	i = 0;
	check_args(argc);
//	check_map_extension(argv);
	program.map = ft_map_reader(argv[1]);
//	if (!program.map || !ft_map_parser(program.map))
//		ft_puterror("Error!");
	if (!program.map)
		ft_puterror("Error!");
	program.frame = 0;
	program.mlx = mlx_init(HEIGHT, WIDTH, "cub3d", true);
	program.img.img = mlx_new_image(program.mlx, HEIGHT, WIDTH);
	if (!program.img.img) //|| (mlx_image_to_window(program.mlx,
			//	program.img.img, 0, 0) < 0))
		ft_puterror("Error!");
	ft_display_map(&program);
	mlx_image_to_window(program.mlx, program.img.img, 0, 0);
	mlx_loop_hook(program.mlx, ft_hook, program.mlx);
	mlx_loop(program.mlx);
	mlx_terminate(program.mlx);
}
