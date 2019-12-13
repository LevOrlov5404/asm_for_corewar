/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnita <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 15:03:48 by pnita             #+#    #+#             */
/*   Updated: 2019/12/12 15:03:49 by pnita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/assembler.h"

void	set_arg_value(t_asm *ass, t_arg *arg, char type, int dir_size)
{
	char	*s;
	
	// printf("type = %d\n", type);
	// printf("T_REG = %d T_DIR = %d T_IND = %d\n", (type & T_REG) == T_REG, (type & T_DIR) == T_DIR, (type & T_REG) == T_REG);
	if ((type & T_REG) == T_REG && ass->line[ass->x] == 'r')
	{
		++ass->x; // it seens that it should be 1 <= x <= 16

	}
	else if ((type & T_DIR) == T_DIR && ass->line[ass->x] == DIRECT_CHAR)
	{
		++ass->x;
		if (ass->line[ass->x] == LABEL_CHAR)
		{
			// T_DIR do with labels
			s = get_s_before_spaces(ass->line + ass->x);
		}
		else if (ass->line[ass->x] == '-' || (ass->line[ass->x] >= '0' && ass->line[ass->x] <= '9'))
			fill_arg(arg, ft_atoi_asm(ass, ass->line + ass->x), dir_size);
		else
			error_exit(ass, 4);
	}
	else if ((type & T_REG) == T_REG)
	{
		if (ass->line[ass->x] == LABEL_CHAR)
		{
			// T_IND do with labels
			s = get_s_before_spaces(ass->line + ass->x);
		}
		else if (ass->line[ass->x] == '-' || (ass->line[ass->x] >= '0' && ass->line[ass->x] <= '9'))
			fill_arg(arg, ft_atoi_asm(ass, ass->line + ass->x), 2);
		else
			error_exit(ass, 4);
	}
	else
		error_exit(ass, 4);
}

void	do_with_live(t_asm *ass)
{
	t_oper	*oper;
	char	*s;
	int		arg_num;

	// printf("IN do_with_live\n");
	oper = add_oper(ass, 0);
	arg_num = 0;
	while (ass->line[ass->x])
	{
		if (ass->line[ass->x] != ' ' && ass->line[ass->x] != '\t')
		{
			if (arg_num < 1)
			{
				set_arg_value(ass, &oper->arg[0], T_DIR, 4);
				++arg_num;
			}
			else
				error_exit(ass, 4);
		}
		else
			++ass->x;
	}
	if (arg_num < 1)
		error_exit(ass, 5);
	oper->size = 5;
}

void	do_with_ld(t_asm *ass)
{
	t_oper	*oper;
	char	*s;

	// printf("IN do_with_ld\n");
	oper = add_oper(ass, 1);
	while (ass->line[ass->x])
	{
		if (ass->line[ass->x] != ' ' && ass->line[ass->x] != '\t')
		{
			if (ass->line[ass->x] == SEPARATOR_CHAR)
			{
				// smth about separator
			}
			else if (ass->line[ass->x] == 'r')
			{
				// smth about reg
			}
			else if (ass->line[ass->x] == DIRECT_CHAR)
			{
				++ass->x;
				if (ass->line[ass->x] == LABEL_CHAR)
				{
					// T_DIR do with labels
					s = get_s_before_spaces(ass->line + ass->x);
				}
				else if (ass->line[ass->x] == '-' || (ass->line[ass->x] >= '0' && ass->line[ass->x] <= '9'))
					fill_arg(&oper->arg[0], ft_atoi_asm(ass, ass->line + ass->x), 4);
				else
					error_exit(ass, 4);
			}
			else if (ass->line[ass->x] == LABEL_CHAR)
			{
				// T_IND do with labels
				s = get_s_before_spaces(ass->line + ass->x);
			}
			else if (ass->line[ass->x] == '-' || (ass->line[ass->x] >= '0' && ass->line[ass->x] <= '9'))
				fill_arg(&oper->arg[0], ft_atoi_asm(ass, ass->line + ass->x), 2);
			else
				error_exit(ass, 4);
		}
		else
			++ass->x;
	}
}

int 	detect_op(t_asm *ass)
{
	// printf("IN detect_op line[ass->x] = %c\n", line[ass->x]);
	if (!ft_strncmp(ass->line + ass->x, "live", 4))
	{
		ass->x += 4;
		do_with_live(ass);
	}
	else if (!ft_strncmp(ass->line + ass->x, "ld", 2))
	{
		ass->x += 2;
		do_with_ld(ass);
	}
	else if (!ft_strncmp(ass->line + ass->x, "st", 2))
	{
		// do_with_live
	}
	else if (!ft_strncmp(ass->line + ass->x, "add", 3))
	{
		// do_with_live
	}
	else if (!ft_strncmp(ass->line + ass->x, "sub", 3))
	{
		// do_with_live
	}
	else if (!ft_strncmp(ass->line + ass->x, "and", 3))
	{
		// do_with_live
	}
	else if (!ft_strncmp(ass->line + ass->x, "or", 2))
	{
		// do_with_live
	}
	else if (!ft_strncmp(ass->line + ass->x, "xor", 3))
	{
		// do_with_live
	}
	else if (!ft_strncmp(ass->line + ass->x, "zjmp", 4))
	{
		// do_with_live
	}
	else if (!ft_strncmp(ass->line + ass->x, "ldi", 3))
	{
		// do_with_live
	}
	else if (!ft_strncmp(ass->line + ass->x, "sti", 3))
	{
		// do_with_live
	}
	else if (!ft_strncmp(ass->line + ass->x, "fork", 4))
	{
		// do_with_live
	}
	else if (!ft_strncmp(ass->line + ass->x, "lld", 3))
	{
		// do_with_live
	}
	else if (!ft_strncmp(ass->line + ass->x, "lldi", 4))
	{
		// do_with_live
	}
	else if (!ft_strncmp(ass->line + ass->x, "lfork", 5))
	{
		// do_with_live
	}
	else if (!ft_strncmp(ass->line + ass->x, "aff", 3))
	{
		// do_with_live
	}
	else
		return (0);
	return (1);
}
