/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lbls.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnita <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 15:23:01 by pnita             #+#    #+#             */
/*   Updated: 2019/12/12 15:23:03 by pnita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/assembler.h"

size_t			hash(char *input)
{
	size_t	hash_num;

	hash_num = 1;
	while (*input)
	{
		hash_num = hash_num * 3 + *(input++);
	}
	return (hash_num % LBLS_SIZE);
}

t_lbl			*find_lbl(t_asm *ass, char *name)
{
	t_lbl		*tmp_lbl;

	tmp_lbl = ass->lbl[hash(name)];
	while (tmp_lbl && ft_strcmp(tmp_lbl->name, name))
		tmp_lbl = tmp_lbl->same_hash;
	return (tmp_lbl);
}
