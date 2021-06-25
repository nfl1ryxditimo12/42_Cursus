/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonkim <seonkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 17:38:22 by seonkim           #+#    #+#             */
/*   Updated: 2021/06/25 19:16:00 by seonkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_err(char *err)
{
	while (*err)
		write(1, err++, 1);
	write(1, "\n", 1);
	exit(-1);
}

void	print_nbr_err(char *err, void *arr)
{
	while (*err)
		write(1, err++, 1);
	write(1, "\n", 1);
	free(arr);
	exit(-1);
}

int main(int ac, char **av)
{
	t_stack	*stk_a;
	t_stack *stk_b;
	t_stack	*ps;

	if (ac <= 1)
		print_err("Argument not enough");
	stk->size = ac - 1;
	list_init(av, stk_a, stk_b, ps);
	return (0);
}
