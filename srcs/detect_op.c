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

void	set_t_reg(t_asm *ass, t_arg *arg)
{
	int		n;

	++ass->x;
	if (ass->line[ass->x] >= '0' && ass->line[ass->x] <= '9')
	{
		n = ft_atoi_asm(ass, ass->line + ass->x);
		if (n >= 1 && n <= 16)
			fill_arg(arg, n, 1, REG_CODE);
		else
			error_exit(ass, 6);
	}
	else
		error_exit(ass, 4);
}

void	set_lbl(t_asm *ass, t_arg *arg, int size, int code)
{
	char	*lbl;
	int		len;
	
	++ass->x;
	len = ass->x;
	while (ass->line[len] && ft_strchr(LABEL_CHARS, ass->line[len]))
		++len;
	if (len < ass->x)
		error_exit(ass, 4);
	lbl = ft_str_sub_n(ass->line + ass->x, len - ass->x);
	arg->size = size;
	arg->code = code;
	add_lbl_arg(ass, arg, lbl);
	ass->x = len;
}

void	set_t_dir(t_asm *ass, t_arg *arg, int dir_size)
{
	++ass->x;
	if (ass->line[ass->x] == LABEL_CHAR)
		set_lbl(ass, arg, dir_size, DIR_CODE);
	else if (ass->line[ass->x] == '-' || (ass->line[ass->x] >= '0' && ass->line[ass->x] <= '9'))
		fill_arg(arg, ft_atoi_asm(ass, ass->line + ass->x), dir_size, DIR_CODE);
	else
		error_exit(ass, 4);
}

void	set_t_ind(t_asm *ass, t_arg *arg)
{
	if (ass->line[ass->x] == LABEL_CHAR)
		set_lbl(ass, arg, 2, IND_CODE);
	else if (ass->line[ass->x] == '-')
	{
		++ass->x;
		if (ass->line[ass->x] >= '0' && ass->line[ass->x] <= '9')
			fill_arg(arg, ft_atoi_asm(ass, ass->line + ass->x), 2, IND_CODE);
		else
			error_exit(ass, 4);
	}
	else if (ass->line[ass->x] >= '0' && ass->line[ass->x] <= '9')
		fill_arg(arg, ft_atoi_asm(ass, ass->line + ass->x), 2, IND_CODE);
	else
		error_exit(ass, 4);
}

void	set_arg_value(t_asm *ass, t_arg *arg, char type, int dir_size)
{
	if ((type & T_REG) == T_REG && ass->line[ass->x] == 'r')
		set_t_reg(ass, arg);
	else if ((type & T_DIR) == T_DIR && ass->line[ass->x] == DIRECT_CHAR)
		set_t_dir(ass, arg, dir_size);
	else if ((type & T_IND) == T_IND)
		set_t_ind(ass, arg);
	else
		error_exit(ass, 4);
}

void	do_with_oper(t_asm *ass, int op_num)
{
	t_oper	*oper;
	int		arg;
	int		tmp_comma;

	oper = add_oper(ass, op_num);
	arg = 0;
	tmp_comma = 0;
	while (ass->line[ass->x])
	{
		if (ass->line[ass->x] == COMMENT_CHAR || ass->line[ass->x] == ALT_COMMENT_CHAR)
			break ;
		if (ass->line[ass->x] != ' ' && ass->line[ass->x] != '\t')
		{
			if (tmp_comma < arg)
			{
				if (ass->line[ass->x] != SEPARATOR_CHAR)
					error_exit(ass, 4);
				++tmp_comma;
				++ass->x;
			}
			else if (arg < oper->ops.args_number)
			{
				set_arg_value(ass, &oper->arg[arg], oper->ops.args_type[arg], oper->ops.t_dir_size);
				++arg;
			}
			else
				error_exit(ass, 4);
		}
		else
			++ass->x;
	}
	if (arg < oper->ops.args_number)
		error_exit(ass, 5);
	if (oper->ops.args_type_code)
		oper->args_type_code = (oper->arg[0].code << 6) | (oper->arg[1].code << 4) | oper->arg[2].code;
	oper->size = (oper->ops.args_type_code ? 2 : 1) + oper->arg[0].size + oper->arg[1].size + oper->arg[2].size;
	if ((ass->current_pos += oper->size) > CHAMP_MAX_SIZE)
		error_exit(ass, 11);
}

int 	detect_op(t_asm *ass)
{
	if (!ft_strncmp(ass->line + ass->x, "live", 4))
	{
		ass->x += 4;
		do_with_oper(ass, 0);
	}
	else if (!ft_strncmp(ass->line + ass->x, "ldi", 3))
	{
		ass->x += 3;
		do_with_oper(ass, 9);
	}
	else if (!ft_strncmp(ass->line + ass->x, "ld", 2))
	{
		ass->x += 2;
		do_with_oper(ass, 1);
	}
	else if (!ft_strncmp(ass->line + ass->x, "sti", 3))
	{
		ass->x += 3;
		do_with_oper(ass, 10);
	}
	else if (!ft_strncmp(ass->line + ass->x, "st", 2))
	{
		ass->x += 2;
		do_with_oper(ass, 2);
	}
	else if (!ft_strncmp(ass->line + ass->x, "add", 3))
	{
		ass->x += 3;
		do_with_oper(ass, 3);
	}
	else if (!ft_strncmp(ass->line + ass->x, "sub", 3))
	{
		ass->x += 3;
		do_with_oper(ass, 4);
	}
	else if (!ft_strncmp(ass->line + ass->x, "and", 3))
	{
		ass->x += 3;
		do_with_oper(ass, 5);
	}
	else if (!ft_strncmp(ass->line + ass->x, "or", 2))
	{
		ass->x += 2;
		do_with_oper(ass, 6);
	}
	else if (!ft_strncmp(ass->line + ass->x, "xor", 3))
	{
		ass->x += 3;
		do_with_oper(ass, 7);
	}
	else if (!ft_strncmp(ass->line + ass->x, "zjmp", 4))
	{
		ass->x += 4;
		do_with_oper(ass, 8);
	}
	else if (!ft_strncmp(ass->line + ass->x, "fork", 4))
	{
		ass->x += 4;
		do_with_oper(ass, 11);
	}
	else if (!ft_strncmp(ass->line + ass->x, "lldi", 4))
	{
		ass->x += 4;
		do_with_oper(ass, 13);
	}
	else if (!ft_strncmp(ass->line + ass->x, "lld", 3))
	{
		ass->x += 3;
		do_with_oper(ass, 12);
	}
	else if (!ft_strncmp(ass->line + ass->x, "lfork", 5))
	{
		ass->x += 5;
		do_with_oper(ass, 14);
	}
	else if (!ft_strncmp(ass->line + ass->x, "aff", 3))
	{
		ass->x += 3;
		do_with_oper(ass, 15);
	}
	else
		return (0);
	return (1);
}
