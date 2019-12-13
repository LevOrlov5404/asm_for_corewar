/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_s1_end_with_s2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnita <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 22:40:54 by pnita             #+#    #+#             */
/*   Updated: 2019/12/10 22:40:56 by pnita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int     ft_check_s1_end_with_s2(char *s1, char *s2)
{
	int	len1;
	int	len2;
	int	i1;
	int	i2;
	
	if (!s1 || !s2 || (len1 = ft_strlen(s1)) < (len2 = ft_strlen(s2)))
		return (0);
	i1 = len1;
	i2 = len2;
	while (i2 >= 0)
	{
		if (s1[i1--] != s2[i2--])
			return (0);
	}
	return (1);
}
