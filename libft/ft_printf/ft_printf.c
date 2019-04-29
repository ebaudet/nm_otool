/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/21 20:45:55 by ebaudet           #+#    #+#             */
/*   Updated: 2019/04/29 19:51:48 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "libft.h"

void		ft_concat_param(t_ftprintf *t, t_params *params)
{
	char	*tmp;

	tmp = ft_memalloc(t->size + params->size);
	ft_memcpy(tmp, t->str, t->size);
	if (params->size >= BUFF_PARAMS)
	{
		ft_memcpy(tmp + t->size, params->buf_extra, params->size);
		ft_memdel((void **)&(params->buf_extra));
	}
	else
	{
		ft_memcpy(tmp + t->size, params->buf, params->size);
	}
	free(t->str);
	t->size += params->size;
	t->str = tmp;
}

static char	*ft_getsstr(t_ftprintf *t, const char *format)
{
	t_params	params;

	params_init(&params);
	t->str = ft_memalloc(0);
	t->i = 0;
	while (format[t->i] != '\0')
	{
		if (!is_arg(t, format, &params))
		{
			params.buf[0] = format[t->i];
			params.size = 1;
			(t->i)++;
		}
		ft_concat_param(t, &params);
		params_reset(&params);
	}
	return (t->str);
}

t_ftsprintf	*ft_sprintf(const char *format, ...)
{
	t_ftprintf	t;
	char		*str;
	t_ftsprintf	*out;

	t.size = 0;
	va_start(t.ap, format);
	str = ft_getsstr(&t, format);
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
	ft_getsstr(&t, format);
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
	ft_getsstr(&t, format);
	va_end(t.ap);
	write(fd, t.str, t.size);
	free(t.str);
	return (t.size);
}
