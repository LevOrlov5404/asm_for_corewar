/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_comment.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnita <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 19:08:06 by pnita             #+#    #+#             */
/*   Updated: 2019/12/16 19:08:08 by pnita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/assembler.h"

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
			{
				++ass->x;
				ass->nc_i = 0;
				while (ass->line[ass->x] && ass->line[ass->x] != '\"')
				{
					ass->name[ass->nc_i++] = ass->line[ass->x++];
					if (ass->nc_i > PROG_NAME_LENGTH)
						error_exit(ass, 9);
				}
			}
			else
				error_exit(ass, 4);
		}
		else
			++ass->x;
	}
	while (ass->line[ass->x] != '\"' && get_next_line(ass->fd, &ass->line) > 0)
	{
		++ass->y;
		while (ass->line[ass->x] && ass->line[ass->x] != '\"')
		{
			ass->name[ass->nc_i++] = ass->line[ass->x++];
			if (ass->nc_i > PROG_NAME_LENGTH)
				error_exit(ass, 9);
		}
	}
	if (!ass->name[0] || ass->line[ass->x] != '\"')
		error_exit(ass, 3);
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
			{
				++ass->x;
				ass->nc_i = 0;
				while (ass->line[ass->x] && ass->line[ass->x] != '\"')
				{
					ass->comment[ass->nc_i++] = ass->line[ass->x++];
					if (ass->nc_i > COMMENT_LENGTH)
						error_exit(ass, 9);
				}
			}
			else
				error_exit(ass, 4);
		}
		++ass->x;
	}
	while (ass->line[ass->x] != '\"' && get_next_line(ass->fd, &ass->line) > 0)
	{
		++ass->y;
		while (ass->line[ass->x] && ass->line[ass->x] != '\"')
		{
			ass->comment[ass->nc_i++] = ass->line[ass->x++];
			if (ass->nc_i > COMMENT_LENGTH)
				error_exit(ass, 9);
		}
	}
	if (!ass->comment[0] || ass->line[ass->x] != '\"')
		error_exit(ass, 3);
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
			{
				if (!ft_strncmp(ass->line + ass->x, NAME_CMD_STRING,
						ass->cmd_name_len) && !ass->name[0])
					get_name(ass);
				else if (!ft_strncmp(ass->line + ass->x, COMMENT_CMD_STRING,
						ass->cmd_comment_len) && !ass->comment[0])
					get_comment(ass);
				else
					error_exit(ass, 4);
			}
			else
				++ass->x;
		}
		++ass->y;
		ass->x = 0;
		ft_strdel(&ass->line);
	}
	if (!ass->name[0] || !ass->comment[0])
		error_exit(ass, 3);
}
