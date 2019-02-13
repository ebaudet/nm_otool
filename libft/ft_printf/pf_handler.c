/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 17:55:04 by ebaudet           #+#    #+#             */
/*   Updated: 2019/02/11 20:53:19 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "libft.h"

int		call_handler(const char *format, t_ftprintf *t, t_params *params)
{
	static t_call_handler	(handler[6]) = {
		{.value = P_FLAGS, .handle = flag_handler},
		{.value = P_WIDTH, .handle = width_handler},
		{.value = P_PRECISION, .handle = precision_handler},
		{.value = P_LENGTH, .handle = length_handler},
		{.value = P_TYPE, .handle = type_handler},
		{.value = P_MODULO, .handle = modulo_handler},
	};
	int						i;
	int						do_stuff;

	do_stuff = 0;
	i = -1;
	while (++i < 6)
	{
		if (format[t->i] && ft_strchr(handler[i].value, format[t->i]))
		{
			(handler[i].handle)(&format[t->i], t, params);
			do_stuff++;
			if (i == 4 || i == 5)
				return (-1);
		}
	}
	return (do_stuff);
}

void	modulo_handler(const char *format, t_ftprintf *t, t_params *params)
{
	add_to_buff(params, (char *)format, 1);
	fill_string(params, check_flag(params, ZERO) ? '0' : ' ',
		params->width, check_flag(params, MINUS));
	(t->i)++;
}

void	flag_handler(const char *format, t_ftprintf *t, t_params *params)
{
	if (format[0] == '-')
		params->flag |= MINUS;
	else if (format[0] == '+')
		params->flag |= PLUS;
	else if (format[0] == ' ')
		params->flag |= SPACE;
	else if (format[0] == '0')
		params->flag |= ZERO;
	else if (format[0] == '#')
		params->flag |= HASH;
	else
		return ;
	(t->i)++;
}

void	width_handler(const char *format, t_ftprintf *t, t_params *params)
{
	char	*last_number;
	char	number[26];

	ft_memset(number, 0, 26);
	if (format[0] == '*' && ++t->i)
	{
		params->width = (int)va_arg(t->ap, unsigned int);
		return ;
	}
	last_number = find_last_number(format);
	if (last_number == format)
	{
		params->width = 0;
		return ;
	}
	ft_strncpy(number, format, last_number - format);
	t->i += last_number - format;
	params->width = (int)ft_atoi(number);
}

void	precision_handler(const char *format, t_ftprintf *t, t_params *params)
{
	char	*last_number;
	char	number[26];

	ft_memset(number, 0, 26);
	if (format[0] != '.')
	{
		params->precision = 0;
		return ;
	}
	else if (format[1] && format[1] == '*')
	{
		params->precision = va_arg(t->ap, unsigned int);
		(t->i) += 2;
		return ;
	}
	last_number = find_last_number(&format[1]);
	if (last_number == format)
	{
		params->precision = 0;
		return ;
	}
	ft_strncpy(number, &format[1], last_number - &format[1]);
	(t->i) += last_number - format;
	params->precision = (int)ft_atoi(number);
}

void	length_handler(const char *format, t_ftprintf *t, t_params *params)
{
	if (format[0] == 'h')
	{
		if (format[1] && format[1] == 'h' && t->i++)
			params->length = params->length ? params->length : HH;
		else
			params->length = params->length ? params->length : H;
	}
	else if (format[0] == 'l')
	{
		if (format[1] && format[1] == 'l' && t->i++)
			params->length = params->length ? params->length : LL;
		else
			params->length = params->length ? params->length : L;
	}
	else if (format[0] == 'L')
		params->length = params->length ? params->length : LD;
	else if (format[0] == 'z')
		params->length = params->length ? params->length : Z;
	else if (format[0] == 'j')
		params->length = params->length ? params->length : J;
	else if (format[0] == 't')
		params->length = params->length ? params->length : T;
	else
		params->length = params->length ? params->length : NONE_LENGH;
	t->i++;
}

void	type_handler(const char *format, t_ftprintf *t, t_params *params)
{
	static t_handler	(handler[12]) = {
		{.value = 'c', .handle = type_c},
		{.value = 's', .handle = type_s},
		{.value = 'p', .handle = type_p},
		{.value = 'd', .handle = type_d},
		{.value = 'i', .handle = type_d},
		{.value = 'o', .handle = type_o},
		{.value = 'u', .handle = type_u},
		{.value = 'x', .handle = type_x},
		{.value = 'X', .handle = type_x_cap},
		{.value = 'f', .handle = type_f},
		{.value = 'k', .handle = type_k},
		{.value = 'b', .handle = type_b},
	};
	int					i;

	i = -1;
	while (++i < 12)
	{
		if (format[0] == handler[i].value)
		{
			(*handler[i].handle)(t, params);
			t->i++;
			return ;
		}
	}
}
