/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 16:53:20 by ebaudet           #+#    #+#             */
/*   Updated: 2014/01/04 18:45:50 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char		**create_string(char **strnew, char const *s, char c)
{
	unsigned int	i;
	int				j;
	size_t			len;

	i = 0;
	j = 0;
	len = 0;
	while (s[i])
	{
		while ((s[i] != c) && s[i])
		{
			len++;
			i++;
			if ((s[i] == c) || !s[i])
			{
				strnew[j] = ft_strsub(s, (size_t)i - len, len);
				j++;
				len = 0;
			}
		}
		if (s[i])
			i++;
	}
	strnew[j] = '\0';
	return (strnew);
}

char			**ft_strsplit(char const *s, char c)
{
	int			i;
	int			nbstr;
	char		**strnew;

	i = 0;
	nbstr = 0;
	if (!s)
		return (NULL);
	if (s[0] != c && s[0])
		nbstr++;
	while (s[i])
	{
		if (s[i] == c)
		{
			if ((s[i + 1] != c) && s[i + 1])
				nbstr++;
		}
		i++;
	}
	if (!(strnew = (char **)malloc(sizeof(char *) * (nbstr + 1))))
		return (NULL);
	return (create_string(strnew, s, c));
}
