/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dec_lenght.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 16:10:50 by ebaudet           #+#    #+#             */
/*   Updated: 2019/02/05 17:42:03 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

intmax_t	get_signed_int_handler(t_ftprintf *t, t_length length)
{
	if (length == NONE_LENGH)
		return (va_arg(t->ap, int));
	if (length == HH)
		return ((char)va_arg(t->ap, int));
	if (length == H)
		return ((short)va_arg(t->ap, int));
	if (length == L)
		return (va_arg(t->ap, long int));
	if (length == LL)
		return (va_arg(t->ap, long long int));
	if (length == LD)
		return ((intmax_t)va_arg(t->ap, double));
	if (length == Z)
		return (va_arg(t->ap, size_t));
	if (length == J)
		return (va_arg(t->ap, intmax_t));
	return (va_arg(t->ap, int));
}

uintmax_t	get_usigned_int_handler(t_ftprintf *t, t_length length)
{
	if (length == NONE_LENGH)
		return (va_arg(t->ap, unsigned int));
	if (length == HH)
		return ((unsigned char)va_arg(t->ap, unsigned int));
	if (length == H)
		return ((unsigned short)va_arg(t->ap, unsigned int));
	if (length == L)
		return (va_arg(t->ap, unsigned long int));
	if (length == LL)
		return (va_arg(t->ap, unsigned long long int));
	if (length == LD)
		return ((uintmax_t)va_arg(t->ap, double));
	if (length == Z)
		return (va_arg(t->ap, size_t));
	if (length == J)
		return (va_arg(t->ap, uintmax_t));
	return (va_arg(t->ap, unsigned int));
}
