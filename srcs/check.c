/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 17:03:57 by faventur          #+#    #+#             */
/*   Updated: 2022/05/09 16:59:56 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	check_args(char argc)
{
	if (argc != 2)
		ft_puterror("Just, and no more than, two arguments, please!");
}

void	check_map_extension(char *argv[])
{
	int	fd;

	if (!ft_strstr(argv[1], ".ber\0"))
		ft_puterror("It seems that the map format is not correct.");
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_puterror("The file doesn't exist!");
	close(fd);
}
