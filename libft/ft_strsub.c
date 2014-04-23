/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 16:54:29 by ebaudet           #+#    #+#             */
/*   Updated: 2014/04/16 19:04:45 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char		*res;
	size_t		i;

	if (!s)
		return (NULL);
	res = (char *)malloc((len + 1) * sizeof(*res));
	if (res)
	{
		i = 0;
		while (i < len)
		{
			res[i] = s[start + (unsigned int)i];
			i++;
		}
		res[i] = 0;
		return (res);
	}
	else
		return (NULL);
}
