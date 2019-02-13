/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 16:40:08 by ebaudet           #+#    #+#             */
/*   Updated: 2019/02/01 18:32:32 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** The isalpha() function tests for any character <c> for which isupper(3)
** or islower(3) is true.  The value of the argument must be representable
** as an unsigned char or the value of EOF.
**
** RETURN : The isalpha() function returns zero if the character tests
** false and returns non-zero if the character tests true.
*/

int		ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	else
		return (0);
}
