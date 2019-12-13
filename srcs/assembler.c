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

	// now i don't spot comments => add later
	get_name_and_comment(ass);
	while (get_next_line(ass->fd, &ass->line) > 0)
	{
		// printf("y = %d\n", ass->y);
		ass->x = 0;
		while (ass->line[ass->x])
		{
			// printf("x = %d\n", ass->x);
			if (ass->line[ass->x] == ' ' || ass->line[ass->x] == '\t')
				++ass->x;
			else if (!detect_op(ass))
			{
				// detect_lbl
				// error
				// ass->err_token = s1_before_spaces_in_input_s2(line + ass->x);
				// error_exit(ass, 4);
				++ass->x;
			}
		}
		++ass->y;
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
	// if ((ass->fd = open("/Users/pnita/my_work/corewar/assembler/my_champ.s", O_RDONLY)) == -1)
	// 	error_exit(ass, 1);
	if ((ass->fd = open("/home/lev/mywork/asm_for_corewar/my_champ.s", O_RDONLY)) == -1)
		error_exit(ass, 1);
	reading(ass);
	return (0);
}
