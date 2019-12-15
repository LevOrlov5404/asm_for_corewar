/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnita <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 22:29:13 by pnita             #+#    #+#             */
/*   Updated: 2019/12/11 22:29:14 by pnita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/assembler.h"

void	error_exit(t_asm *ass, int error_num)
{
	if (!error_num)
		printf("ERROR. Can be only one file and it's name must end with \".s\"\n");
	else if (error_num == 1)
	{
		printf("ERROR. Can't open %s\n", ass->file_name);
	}
	else if (error_num == 2)
	{
		printf("ERROR. Can't read %s\n", ass->file_name);
	}
	else if (error_num == 3)
	{
		printf("ERROR. Not correct champion name or champion comment\n");
	}
	else if (error_num == 4)
	{
		printf("ERROR. Unexpected symbol \"%c\" at [%.3i:%.3i]\n", ass->line[ass->x], ass->y + 1, ass->x + 1);
	}
	else if (error_num == 5)
	{
		printf("ERROR. Not full operation at [%.3i:%.3i]\n", ass->y + 1, ass->x + 1);
	}
	else if (error_num == 6)
	{
		printf("ERROR. T_REG can be only from 1 to 16\n");
	}
	else if (error_num == 7)
	{
		printf("ERROR. Incorrect label starting with \"%c\" at [%.3i:%.3i]\n", ass->line[ass->x], ass->y + 1, ass->x + 1);
	}
	else if (error_num == 8)
	{
		printf("ERROR. Label %s not found\n", ass->error_str);
	}
	else if (error_num == 9)
	{
		printf("ERROR. Size of champion name = %d > %d\n", ass->name_len, PROG_NAME_LENGTH);
	}
	else if (error_num == 10)
	{
		printf("ERROR. Size of champion comment = %d > %d\n", ass->comment_len, COMMENT_LENGTH);
	}
	else if (error_num == 11)
	{
		printf("ERROR. Size of champion code = %d > %d\n", ass->current_pos, CHAMP_MAX_SIZE);
	}
	else
		printf("ERROR\n");
	if (ass)
		delete_all(ass);
	exit(1);
}
