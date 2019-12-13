/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnita <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 14:40:05 by pnita             #+#    #+#             */
/*   Updated: 2019/12/11 14:40:06 by pnita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/assembler.h"
#include "../include/operations.h"

int main()
{
    unsigned char reg = 1;
    unsigned char dir = 2;
    unsigned char ind = 3;
    unsigned char arg_types_code;

    // arg_types_code = reg << 6 | dir << 4 | dir << 2;
    // printf("%x\n", arg_types_code);

    // unsigned short code;
    // code = -5;
    // printf("%x\n", code);

    // printf("%.3i\n", 1);

    char    bytes[4];
    bytes[0] = '1';
    bytes[1] = '2';
    // printf("%s\n", bytes);
    int i = 0;
    while (bytes[i])
    {
        printf("%c", bytes[i]);
        ++i;
    }
    return (0);
}