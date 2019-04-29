/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_handler_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 17:55:04 by ebaudet           #+#    #+#             */
/*   Updated: 2019/04/29 19:51:58 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "libft.h"

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

static const t_handler	g_type_handler[] = {
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
	{.value = 0, .handle = NULL}
};

void	type_handler(const char *format, t_ftprintf *t, t_params *params)
{
	int		i;

	i = -1;
	while (g_type_handler[++i].value != 0)
	{
		if (format[0] == g_type_handler[i].value)
		{
			(*g_type_handler[i].handle)(t, params);
			t->i++;
			return ;
		}
	}
}
