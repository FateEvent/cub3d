/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ret_null.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 21:26:05 by albaur            #+#    #+#             */
/*   Updated: 2022/07/20 22:07:14 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ret_null(char *str, char *str2)
{
	if (str2)
		ft_printf("%s %s\n", str, str2);
	else
		ft_printf("%s\n", str);
	return ;
}
