/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 17:03:57 by faventur          #+#    #+#             */
/*   Updated: 2022/10/06 16:30:20 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	check_args(char argc)
{
	if (argc != 2)
		ft_puterror("error: invalid number of arguments");
}

void	check_map_extension(char *argv[])
{
	int	fd;

	if (!ft_strstr(argv[1], ".cub\0"))
		ft_puterror("error: invalid map extension");
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_puterror("error: the file doesn't exist");
	close(fd);
}

void	check(int argc, char **argv)
{
	check_args(argc);
	check_map_extension(argv);
}
