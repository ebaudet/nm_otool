/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_type_text.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 18:57:20 by ebaudet           #+#    #+#             */
/*   Updated: 2019/04/29 18:59:58 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "libft.h"

void	type_c(t_ftprintf *t, t_params *params)
{
	char	c;

	if (params)
		params->size = params->size;
	c = (char)(va_arg(t->ap, int));
	add_to_buff(params, &c, 1);
	fill_string(params, check_flag(params, ZERO) ? '0' : ' ',
		params->width, check_flag(params, MINUS));
}

void	type_s(t_ftprintf *t, t_params *params)
{
	char	*str;

	str = va_arg(t->ap, char *);
	if (str == NULL)
		add_to_buff(params, "(null)", -1);
	else
		add_to_buff(params, str, ft_min(params->precision, ft_strlen(str)));
	fill_string(params, check_flag(params, ZERO) ? '0' : ' ',
		params->width, check_flag(params, MINUS));
}
