/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 16:48:34 by ebaudet           #+#    #+#             */
/*   Updated: 2019/02/01 18:51:48 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** The strcat() function append a copy of the null-terminated
** string <s2> to the end of the null-terminated string <s1>, then add a
** terminating `\0'.  The string <s1> must have sufficient space to hold the
** result.
**
** RETURN : The strcat() function return the pointer <s1>.
*/

char	*ft_strcat(char *s1, const char *s2)
{
	int			i;
	size_t		lenght;

	lenght = ft_strlen(s1);
	i = 0;
	while (s2[i])
	{
		s1[i + lenght] = s2[i];
		i++;
	}
	s1[i + lenght] = 0;
	return (s1);
}
