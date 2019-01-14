/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 16:49:47 by ebaudet           #+#    #+#             */
/*   Updated: 2019/01/14 16:04:18 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*scopy;

	i = -1;
	if ((scopy = (char *)malloc((ft_strlen(s1) + 1) * sizeof(char))) == NULL)
		return (NULL);
	while (s1[++i])
		scopy[i] = s1[i];
	scopy[i] = s1[i];
	return (scopy);
}
