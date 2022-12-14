/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stacksize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:13:51 by faventur          #+#    #+#             */
/*   Updated: 2022/10/11 16:42:12 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The ft_stacksize() function counts the number of elements of the stack
** passed as a parameter.
*/

#include "libft.h"

int	ft_stacksize(t_stack *stack)
{
	t_node	*current;
	int		counter;

	if (stack != NULL)
	{
		current = stack->top;
		counter = 0;
		while (current != NULL)
		{
			counter++;
			current = current->next;
		}
		return (counter);
	}	
	return (0);
}
