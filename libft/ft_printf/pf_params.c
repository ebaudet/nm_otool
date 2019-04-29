/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_params.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 23:00:30 by ebaudet           #+#    #+#             */
/*   Updated: 2019/04/29 18:59:57 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "libft.h"

t_params	*params_init(t_params *params)
{
	ft_memset(params, 0, sizeof(*params));
	params->size = 0;
	params->precision = -1;
	params->width = 0;
	params->buf_extra = NULL;
	ft_memset(params->buf, 0, BUFF_PARAMS);
	return (params);
}

t_params	*params_reset(t_params *params)
{
	ft_memdel((void **)&(params->buf_extra));
	ft_memset(params, 0, sizeof(*params));
	params->size = 0;
	params->precision = -1;
	params->width = 0;
	params->buf_extra = NULL;
	ft_memset(params->buf, 0, BUFF_PARAMS);
	return (params);
}
