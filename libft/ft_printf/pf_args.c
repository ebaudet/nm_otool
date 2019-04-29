/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/21 20:45:55 by ebaudet           #+#    #+#             */
/*   Updated: 2019/04/29 19:51:54 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "libft.h"

char		*found_arg(const char *needle)
{
	char	*found;

	found = ft_strstrchr(needle, P_TYPE);
	if (!found)
		found = ft_strstrchr(needle, P_FLAGS);
	if (!found)
		found = ft_strstrchr(needle, P_WIDTH);
	if (!found)
		found = ft_strstrchr(needle, P_PRECISION);
	if (!found)
		found = ft_strstrchr(needle, P_LENGTH);
	return (found);
}

int			is_arg(t_ftprintf *t, const char *format, t_params *params)
{
	char			*next_modulo;
	char			*end_arg;

	if (format[t->i] && format[t->i] == '%' && ++(t->i))
	{
		if (!format[t->i])
			return (1);
		next_modulo = ft_strchr(&format[t->i], '%');
		end_arg = found_arg(&format[t->i]);
		if (end_arg == NULL && next_modulo == NULL)
			return (1);
		while (format[t->i] && call_handler(format, t, params) > 0)
			;
		return (1);
	}
	return (0);
}
