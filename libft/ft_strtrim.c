/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 16:54:42 by ebaudet           #+#    #+#             */
/*   Updated: 2014/04/16 19:03:19 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_is_space(char c)
{
	return (c == ' ' || c == '\n' || c == '\t' || c == '\r' || c == '\f'
	|| c == '\v');
}

char		*ft_strtrim(char const *s)
{
	char	*res;
	int		start;
	int		end;
	int		i;

	start = 0;
	while (s && ft_is_space(s[start]))
		start++;
	end = ft_strlen(s) - 1;
	res = (char *)malloc((end - start + 1) * sizeof(*res));
	while (s && ft_is_space(s[end]))
		end--;
	if (res && s)
	{
		i = 0;
		while ((i + start) <= end)
		{
			res[i] = s[start + i];
			i++;
		}
		res[i] = 0;
		return (res);
	}
	else
		return (NULL);
}
