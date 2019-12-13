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

void	delete_all(t_asm *ass)
{
	free(ass);
	ass = NULL;
}

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
	else
		printf("ERROR\n");
	if (ass)
		delete_all(ass);
	exit(1);
}
