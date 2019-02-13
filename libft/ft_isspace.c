/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 16:39:09 by ebaudet           #+#    #+#             */
/*   Updated: 2019/02/01 18:37:26 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>

/*
** The isspace() function tests for the white-space characters.
** For any locale, this includes the following standard characters:
** \t \n \v \f \r space
*/

int		ft_isspace(int c)
{
	static char	search[7] = " \t\n\v\f\r\0";

	if (ft_strchr(search, c) == NULL)
		return (0);
	return (1);
}
