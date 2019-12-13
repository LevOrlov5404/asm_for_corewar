/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnita <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 19:00:30 by pnita             #+#    #+#             */
/*   Updated: 2019/12/12 19:00:32 by pnita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/assembler.h"

void	fill_arg(t_arg *arg, /*unsigned*/ int val, int size)
{
	int	i;
	
	arg->size = size;
	if (size == 1)
	{
		arg->bytes[0] = val;
		// printf("%.2x\n", arg->bytes[0]);
	}
	else if (size == 2)
	{
		arg->bytes[1] = val;
		arg->bytes[0] = val >> 8;
		// printf("%.2x %.2x\n", arg->bytes[0], arg->bytes[1]);
	}
	else if (size == 4)
	{
		arg->bytes[3] = val;
		arg->bytes[2] = val >> 8;
		arg->bytes[1] = val >> 16;
		arg->bytes[0] = val >> 24;
		printf("%.2x %.2x %.2x %.2x\n", arg->bytes[0], arg->bytes[1], arg->bytes[2], arg->bytes[3]);
	}
}
