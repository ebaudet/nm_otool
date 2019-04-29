/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_type_hexa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 18:55:33 by ebaudet           #+#    #+#             */
/*   Updated: 2019/04/29 18:56:31 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "libft.h"

void	type_p(t_ftprintf *t, t_params *params)
{
	char	*str;

	str = ft_lutohex(va_arg(t->ap, long unsigned int));
	add_to_buff(params, "0x", -1);
	add_to_buff(params, str, -1);
	fill_string(params, ' ', params->width, check_flag(params, MINUS));
	free(str);
}

void	type_x(t_ftprintf *t, t_params *params)
{
	char			*str;
	long long int	value;

	value = (params->length == 0)
		? va_arg(t->ap, unsigned int)
		: get_usigned_int_handler(t, params->length);
	str = ft_lutohex(value);
	if ((value != 0) && check_flag(params, HASH))
	{
		add_to_buff(params, "0x", -1);
		add_to_buff(params, str, -1);
		precision(params, 2);
	}
	else
	{
		add_to_buff(params, str, -1);
		precision(params, 0);
	}
	if (check_flag(params, ZERO) && !check_flag(params, MINUS))
		fill_zero(params, ft_min(params->width, params->precision));
	fill_string(params, ' ', params->width, check_flag(params, MINUS));
	free(str);
}

void	type_x_cap(t_ftprintf *t, t_params *params)
{
	int		i;
	char	*buf_ptr;

	type_x(t, params);
	buf_ptr = (params->size >= BUFF_PARAMS) ? params->buf_extra : params->buf;
	i = -1;
	while (++i <= params->size)
		buf_ptr[i] = ft_toupper(buf_ptr[i]);
}
