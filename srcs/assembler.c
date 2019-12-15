/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnita <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:19:51 by pnita             #+#    #+#             */
/*   Updated: 2019/12/10 20:19:52 by pnita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/assembler.h"

int		create_ass(t_asm **ass)
{
	t_asm	*new;
	
	if (!(new = (t_asm*)ft_memalloc(sizeof(t_asm))))
		return (0);
	new->cmd_name_len = ft_strlen(NAME_CMD_STRING);
	new->cmd_comment_len = ft_strlen(COMMENT_CMD_STRING);
	new->lbl = (t_lbl**)ft_memalloc(sizeof(t_lbl*) * LBLS_SIZE);
	*ass = new;
	return (1);
}

void	reading(t_asm *ass)
{
	char	*str;
	int		len;
	t_lbl	*lbl;

	// now i don't spot comments => add later
	get_name_and_comment(ass);
	while (get_next_line(ass->fd, &ass->line) > 0)
	{
		// printf("y = %d\n", ass->y);
		ass->x = 0;
		while (ass->line[ass->x])
		{
			// printf("x = %d\n", ass->x);
			if (ass->line[ass->x] == COMMENT_CHAR || ass->line[ass->x] == ALT_COMMENT_CHAR)
				break ;
			if (ass->line[ass->x] == ' ' || ass->line[ass->x] == '\t')
				++ass->x;
			else
			{
				len = ass->x;
				while (ass->line[len] && ft_strchr(LABEL_CHARS, ass->line[len]))
					++len;
				if (ass->line[len] == LABEL_CHAR)
				{
					str = ft_str_sub_n(ass->line + ass->x, len - ass->x);
					
					if (!ass->lbl[hash(str)])
					{
						ass->lbl[hash(str)] = create_lbl(str, ass->current_pos);
						// printf("label = %s pos = %d\n", ass->lbl[hash(str)]->name, ass->lbl[hash(str)]->pos_num);
					}
					else
					{
						lbl = ass->lbl[hash(str)];
						while (lbl->same_hash) // add smth if the same lbl again
							lbl = lbl->same_hash;
						lbl = create_lbl(str, ass->current_pos);
						// printf("label = %s pos = %d\n", lbl->name, lbl->pos_num);
					}
					ass->x = len + 1;
					while (ass->line[ass->x])
					{
						if (ass->line[ass->x] != ' ' && ass->line[ass->x] != '\t')
							error_exit(ass, 4);
						++ass->x;
					}
				}
				else if (ass->line[ass->x] && !detect_op(ass))
					error_exit(ass, 7);
			}
		}
		++ass->y;
		ft_strdel(&ass->line);
	}
}

void	fill_lbl_arg(t_asm *ass)
{
	t_lbl_arg	*lbl_arg;
	t_lbl		*lbl;

	// printf("IN fill_lbl_arg\n");
	lbl_arg = ass->lbl_arg_top;
	while (lbl_arg)
	{
		if (!(lbl = find_lbl(ass, lbl_arg->lbl)))
		{
			ass->error_str = lbl_arg->lbl;
			error_exit(ass, 8);
		}
		else
			fill_arg(lbl_arg->arg, lbl->pos_num - lbl_arg->oper_pos, lbl_arg->arg->size, lbl_arg->arg->code);
		lbl_arg = lbl_arg->next;
	}
}

int     main(int argc, char **argv)
{
	t_asm		*ass;

	// if (argc != 2 || !ft_check_s1_end_with_s2(argv[1], ".s"))
	// 	error_exit(NULL, 0);
	if (!create_ass(&ass))
		return (0);
	ass->file_name = argv[1];
	// if ((ass->fd = open(ass->file_name, O_RDONLY)) == -1)
	// 	error_exit(ass, 1);
	// if ((ass->fd = open("/Users/pnita/my_work/asm_for_corewar/my_champ.s", O_RDONLY)) == -1)
	// 	error_exit(ass, 1);
	if ((ass->fd = open("/home/lev/mywork/asm_for_corewar/my_champ.s", O_RDONLY)) == -1)
		error_exit(ass, 1);
	reading(ass);
	fill_lbl_arg(ass);
	return (0);
}
