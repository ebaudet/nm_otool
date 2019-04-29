/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_type_float.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 18:58:11 by ebaudet           #+#    #+#             */
/*   Updated: 2019/04/29 18:59:59 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "libft.h"

void	type_f(t_ftprintf *t, t_params *params)
{
	char		*str;
	long double	value;

	if (params->length == LD)
	{
		value = va_arg(t->ap, long double);
		str = (params->precision == -1)
			? ft_ldtoa(value, 6)
			: ft_ldtoa(value, params->precision);
	}
	else
	{
		value = va_arg(t->ap, double);
		str = (params->precision == -1)
			? ft_dtoa(value, 6)
			: ft_dtoa(value, params->precision);
	}
	if (check_flag(params, PLUS) && (value > 0))
		add_to_buff(params, "+", -1);
	if (!check_flag(params, PLUS) && check_flag(params, SPACE) && (value > 0))
		add_to_buff(params, " ", -1);
	add_to_buff(params, str, -1);
	if (check_flag(params, ZERO) && !check_flag(params, MINUS))
		fill_zero(params, params->width);
	fill_string(params, ' ', params->width, check_flag(params, MINUS));
	free(str);
}
