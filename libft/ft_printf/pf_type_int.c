/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_type_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 18:52:47 by ebaudet           #+#    #+#             */
/*   Updated: 2019/04/29 18:59:59 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "libft.h"

void	type_d(t_ftprintf *t, t_params *params)
{
	char			*str;
	long long int	value;

	if (params->length)
		value = get_signed_int_handler(t, params->length);
	else
		value = va_arg(t->ap, int);
	str = ft_itoa(value);
	if (check_flag(params, PLUS) && (value >= 0))
		add_to_buff(params, "+", -1);
	if (!check_flag(params, PLUS) && check_flag(params, SPACE) && (value >= 0))
		add_to_buff(params, " ", -1);
	add_to_buff(params, str, -1);
	if (ft_strchr(" +-", params->buf[0]))
		precision(params, 1);
	else
		precision(params, 0);
	if (check_flag(params, ZERO) && !check_flag(params, MINUS))
		fill_zero(params, ft_min(params->width, params->precision));
	fill_string(params, ' ', params->width, check_flag(params, MINUS));
	free(str);
}

void	type_u(t_ftprintf *t, t_params *params)
{
	char		*str;
	uintmax_t	value;

	value = (params->length == 0)
		? va_arg(t->ap, unsigned int)
		: get_usigned_int_handler(t, params->length);
	str = ft_itoa(value);
	add_to_buff(params, str, -1);
	precision(params, 0);
	if (check_flag(params, ZERO) && !check_flag(params, MINUS))
		fill_zero(params, ft_min(params->width, params->precision));
	fill_string(params, ' ', params->width, check_flag(params, MINUS));
	free(str);
}
