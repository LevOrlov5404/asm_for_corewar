/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnita <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 18:59:49 by pnita             #+#    #+#             */
/*   Updated: 2019/12/12 18:59:50 by pnita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/assembler.h"

t_oper	*create_oper(int op_num, int pos_num)
{
	t_oper	*oper;

	oper = (t_oper*)ft_memalloc(sizeof(t_oper));
	oper->op_num = op_num;
	oper->pos_num = pos_num;
	return (oper);
}

t_oper	*add_oper(t_asm *ass, int op_num)
{
	if (!ass->top)
	{
		ass->top = create_oper(op_num, 0);
		ass->bot = ass->top;
	}
	else
	{
		ass->bot->next = create_oper(op_num, ass->bot->pos_num + ass->bot->size);
		ass->bot = ass->bot->next;
	}
	return (ass->bot);
}
