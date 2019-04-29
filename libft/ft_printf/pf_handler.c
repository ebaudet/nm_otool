/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_handler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 17:55:04 by ebaudet           #+#    #+#             */
/*   Updated: 2019/04/29 20:27:09 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "libft.h"

static const t_call_handler	g_call_handler[] = {
	{.value = P_FLAGS, .handle = flag_handler},
	{.value = P_WIDTH, .handle = width_handler},
	{.value = P_PRECISION, .handle = precision_handler},
	{.value = P_LENGTH, .handle = length_handler},
	{.value = P_TYPE, .handle = type_handler},
	{.value = P_MODULO, .handle = modulo_handler},
	{.value = NULL, .handle = NULL}
};

int		call_handler(const char *format, t_ftprintf *t, t_params *params)
{
	int						i;
	int						do_stuff;

	do_stuff = 0;
	i = -1;
	while (g_call_handler[++i].value != NULL)
	{
		if (format[t->i] && ft_strchr(g_call_handler[i].value, format[t->i]))
		{
			(g_call_handler[i].handle)(&format[t->i], t, params);
			do_stuff++;
			if (!ft_strcmp(g_call_handler[i].value, P_TYPE)
				|| !ft_strcmp(g_call_handler[i].value, P_MODULO))
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
