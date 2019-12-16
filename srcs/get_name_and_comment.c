/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_name_and_comment.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnita <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 22:31:37 by pnita             #+#    #+#             */
/*   Updated: 2019/12/11 22:31:38 by pnita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/assembler.h"

void	get_name_and_comment_part2(t_asm *ass)
{
	if (!ft_strncmp(ass->line + ass->x, NAME_CMD_STRING,
			ass->cmd_name_len))
		get_name(ass);
	else if (!ft_strncmp(ass->line + ass->x, COMMENT_CMD_STRING,
			ass->cmd_comment_len))
		get_comment(ass);
	else
		error_exit(ass, 4);
}

void	get_name_and_comment(t_asm *ass)
{
	while ((!ass->name || !ass->comment)
			&& get_next_line(ass->fd, &ass->line) > 0)
	{
		while (ass->line[ass->x])
		{
			if (ass->line[ass->x] == COMMENT_CHAR
					|| ass->line[ass->x] == ALT_COMMENT_CHAR)
				break ;
			if (ass->line[ass->x] != ' ' && ass->line[ass->x] != '\t')
				get_name_and_comment_part2(ass);
			else
				++ass->x;
		}
		++ass->y;
		ass->x = 0;
		ft_strdel(&ass->line);
	}
	if (!ass->comment || !ass->name)
		error_exit(ass, 3);
}
