/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_name_and_comment2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnita <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 16:44:39 by pnita             #+#    #+#             */
/*   Updated: 2019/12/16 16:44:40 by pnita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/assembler.h"

void	get_name_part2(t_asm *ass)
{
	++ass->x;
	if ((ass->name_len = ft_len_before_delim(ass->line + ass->x,
			'\"')) == -1)
		error_exit(ass, 3);
	if (ass->name_len > PROG_NAME_LENGTH)
		error_exit(ass, 9);
	ass->name = ft_str_sub_n(ass->line + ass->x, ass->name_len);
	ass->x += ass->name_len;
}

void	get_name(t_asm *ass)
{
	ass->x += ass->cmd_name_len;
	while (ass->line[ass->x])
	{
		if (ass->line[ass->x] == COMMENT_CHAR
				|| ass->line[ass->x] == ALT_COMMENT_CHAR)
			break ;
		if (ass->line[ass->x] != ' ' && ass->line[ass->x] != '\t')
		{
			if (ass->line[ass->x] == '\"' && !ass->name)
				get_name_part2(ass);
			else
				error_exit(ass, 4);
		}
		++ass->x;
	}
	if (!ass->name)
		error_exit(ass, 3);
}

void	get_comment_part2(t_asm *ass)
{
	++ass->x;
	if ((ass->comment_len = ft_len_before_delim(ass->line + ass->x,
			'\"')) == -1)
		error_exit(ass, 3);
	if (ass->comment_len > COMMENT_LENGTH)
		error_exit(ass, 10);
	ass->comment = ft_str_sub_n(ass->line + ass->x,
			ass->comment_len);
	ass->x += ass->comment_len;
}

void	get_comment(t_asm *ass)
{
	ass->x += ass->cmd_comment_len;
	while (ass->line[ass->x])
	{
		if (ass->line[ass->x] == COMMENT_CHAR
				|| ass->line[ass->x] == ALT_COMMENT_CHAR)
			break ;
		if (ass->line[ass->x] != ' ' && ass->line[ass->x] != '\t')
		{
			if (ass->line[ass->x] == '\"' && !ass->comment)
				get_comment_part2(ass);
			else
				error_exit(ass, 4);
		}
		++ass->x;
	}
	if (!ass->comment)
		error_exit(ass, 3);
}
