/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/21 20:45:55 by ebaudet           #+#    #+#             */
/*   Updated: 2019/04/29 20:01:10 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "libft.h"

t_ftsprintf	*ft_sprintf(const char *format, ...)
{
	t_ftprintf	t;
	char		*str;
	t_ftsprintf	*out;

	t.size = 0;
	va_start(t.ap, format);
	str = pf_getsstr(&t, format);
	va_end(t.ap);
	out = ft_memalloc(sizeof(*out));
	out->len = t.size;
	out->str = t.str;
	return (out);
}

int			ft_printf(const char *format, ...)
{
	t_ftprintf	t;

	t.size = 0;
	va_start(t.ap, format);
	pf_getsstr(&t, format);
	va_end(t.ap);
	write(STDOUT_FILENO, t.str, t.size);
	free(t.str);
	return (t.size);
}

int			ft_printf_fd(int fd, const char *format, ...)
{
	t_ftprintf	t;

	t.size = 0;
	va_start(t.ap, format);
	pf_getsstr(&t, format);
	va_end(t.ap);
	write(fd, t.str, t.size);
	free(t.str);
	return (t.size);
}
