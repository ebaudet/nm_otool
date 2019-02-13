/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 16:44:39 by ebaudet           #+#    #+#             */
/*   Updated: 2019/02/01 18:51:31 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

/*
** The putchar() function writes the character <c> (converted to an
** "unsigned char") to the output stream of stdout.
*/

void	ft_putchar(char c)
{
	write(1, &c, 1);
}
