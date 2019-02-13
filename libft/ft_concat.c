/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_concat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 16:39:49 by ebaudet           #+#    #+#             */
/*   Updated: 2019/01/29 17:59:17 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdarg.h>
#include "libft.h"

char		*ft_concat2(const char *s1, const char *s2)
{
	char *res;

	res = ft_memalloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (res)
	{
		ft_strcpy(res, s1);
		ft_strcat(res, s2);
	}
	return (res);
}

char		*ft_concat2c(const char *s1, const char *s2, char c)
{
	char *res;

	res = ft_memalloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	if (res)
	{
		ft_strcpy(res, s1);
		res[ft_strlen(s1)] = c;
		ft_strcat(res, s2);
	}
	return (res);
}

char		*ft_concat2endl(const char *s1, const char *s2)
{
	return (ft_concat2c(s1, s2, '\n'));
}

/*
** The function ft_concat takes 1 mandatory argument :
**     int nb_elem : it is the number of params of the function
**
**     The function is called like that :
**     ft_concatc(2, "hello", "world");
**     and return : "helloworld"
*/

char		*ft_concat(int nb_elem, ...)
{
	va_list		ap;
	char		*res;
	char		*tmp;
	int			i;
	int			cpt;

	res = ft_memalloc(1);
	va_start(ap, nb_elem);
	cpt = nb_elem;
	i = -1;
	while (++i < cpt)
	{
		tmp = va_arg(ap, char*);
		tmp = ft_concat2(res, tmp);
		free(res);
		res = tmp;
	}
	va_end(ap);
	return (res);
}

/*
** The function ft_concatc takes 2 mandatory arguments :
**     int nb_elem : it is the number of params of the function
**     char c : the glue element.
**
**     The function is called like that :
**     ft_concatc(2, '|', "hello", "world");
**     and return : "hello|world"
*/

char		*ft_concatc(int nb_elem, ...)
{
	va_list		ap;
	char		*res;
	char		*tmp;
	int			cpt[2];
	char		c;

	res = ft_memalloc(1);
	va_start(ap, nb_elem);
	c = (char)va_arg(ap, int);
	cpt[0] = nb_elem;
	cpt[1] = -1;
	while (++cpt[1] < cpt[0])
	{
		tmp = va_arg(ap, char*);
		if (cpt[1] == 0)
			tmp = ft_strdup(tmp);
		else
			tmp = ft_concat2c(res, tmp, c);
		free(res);
		res = tmp;
	}
	va_end(ap);
	return (res);
}
