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

char	*get_s_before_spaces(char *s1)
{
	int		i;
	int		len;
	char	*s2;

	if (!s1 || !*s1)
		return (NULL);
	len = 0;
	while (s1[len] && s1[len] != ' ' && s1[len] != '\t')
		++len;
	s2 = ft_strnew(len);
	i = 0;
	while (i < len)
	{
		s2[i] = s1[i];
		++i;
	}
	return (s2);
}

void	get_name(t_asm *ass)
{
	// printf("IN GET_NAME\n");
	ass->x += ass->cmd_name_len;
	while (ass->line[ass->x])
	{
		if (ass->line[ass->x] != ' ' && ass->line[ass->x] != '\t')
		{
			if (ass->line[ass->x] == '\"' && !ass->name)
			{
				++ass->x;
				if ((ass->name_len = ft_len_before_delim(ass->line + ass->x, '\"')) == -1)
					error_exit(ass, 5);
				ass->name = ft_str_sub_n(ass->line + ass->x, ass->name_len);
				ass->x += ass->name_len;
			}
			else
				error_exit(ass, 4);
		}
		++ass->x;
	}
	// printf("x = %i\n", ass->x);
}

void	get_comment(t_asm *ass)
{
	// printf("IN GET_COMMENT\n");
	ass->x += ass->cmd_comment_len;
	while (ass->line[ass->x])
	{
		if (ass->line[ass->x] != ' ' && ass->line[ass->x] != '\t')
		{
			if (ass->line[ass->x] == '\"' && !ass->comment)
			{
				++ass->x;
				if ((ass->comment_len = ft_len_before_delim(ass->line + ass->x, '\"')) == -1)
					error_exit(ass, 5);
				ass->comment = ft_str_sub_n(ass->line + ass->x, ass->comment_len);
				ass->x += ass->comment_len;
			}
			else
				error_exit(ass, 4);
		}
		++ass->x;
	}
	// printf("x = %i\n", ass->x);
}

void	get_name_and_comment(t_asm *ass)
{
	while ((!ass->name || !ass->comment) && get_next_line(ass->fd, &ass->line) > 0)
	{
		while (ass->line[ass->x])
		{
			if (ass->line[ass->x] != ' ' && ass->line[ass->x] != '\t')
			{
				if (!ft_strncmp(ass->line + ass->x, NAME_CMD_STRING, ass->cmd_name_len))
					get_name(ass);
				else if (!ft_strncmp(ass->line + ass->x, COMMENT_CMD_STRING, ass->cmd_comment_len))
					get_comment(ass);
				else
					error_exit(ass, 4);
			}
			else
				++ass->x;
		}
		++ass->y;
		ass->x = 0;
	}
	if (!ass->comment || !ass->name)
		error_exit(ass, 3);
	// printf("name = %s	comment = %s\n", ass->name, ass->comment);
}
