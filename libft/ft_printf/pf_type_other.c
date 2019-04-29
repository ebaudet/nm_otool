/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_type_other.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 15:02:09 by ebaudet           #+#    #+#             */
/*   Updated: 2019/04/29 18:59:52 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "libft.h"

void	type_o(t_ftprintf *t, t_params *params)
{
	char					*str;
	unsigned long long int	value;

	value = (params->length == 0)
		? va_arg(t->ap, unsigned long long int)
		: (unsigned long long int)get_signed_int_handler(t, params->length);
	str = ft_lutooct(value);
	if (check_flag(params, HASH))
	{
		add_to_buff(params, "0", -1);
		add_to_buff(params, str, -1);
		precision(params, 1);
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

void	type_b(t_ftprintf *t, t_params *params)
{
	char			*str;
	long long int	value;

	value = (params->length == 0)
		? va_arg(t->ap, long long int)
		: (long long int)get_signed_int_handler(t, params->length);
	str = ft_lutobin(value);
	if (check_flag(params, HASH))
	{
		add_to_buff(params, "b", -1);
		add_to_buff(params, str, -1);
		precision(params, 1);
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

/*
** Option for color : k
** - width define the color code. Between 0 and 255.
**   <K_BLACK, K_RED, K_GREEN, K_YELLOW, K_BLUE, K_ROSE, K_CYAN, K_WHITE>
** - MINUS flag for underline (;4)
** - PLUS flag for bold (;1)
** - HASH flag for backgroud-color (7 ou +10)
** - ZERO flag for italic (;3)
** - No flags and width define an End of color. (\e[0m)
*/

void	type_k(t_ftprintf *t, t_params *params)
{
	char	*str;
	int		have_flag;

	t->size = t->size;
	have_flag = 0;
	add_to_buff(params, "\e[", -1);
	if (params->width && ++have_flag)
	{
		params->width += check_flag(params, HASH) ? 10 : 0;
		str = ft_itoa(params->width);
		add_to_buff(params, str, -1);
		free(str);
	}
	else if (check_flag(params, HASH) && ++have_flag)
		add_to_buff(params, "7", -1);
	if (check_flag(params, PLUS) && ++have_flag)
		add_to_buff(params, ";1", -1);
	else if (check_flag(params, ZERO) && ++have_flag)
		add_to_buff(params, ";3", -1);
	else if (check_flag(params, MINUS) && ++have_flag)
		add_to_buff(params, ";4", -1);
	if (!have_flag)
		add_to_buff(params, "0", -1);
	add_to_buff(params, "m", -1);
}
