/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 14:21:13 by ebaudet           #+#    #+#             */
/*   Updated: 2019/02/11 22:23:08 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "libft.h"

/*
** Add the string <str> to the buffer <params->{buf|buf_extra}>
** If the total length >= BUFF_PARAMS, <params->buf_extra> is used instead of
** <params->buf>
*/

int		add_to_buff(t_params *params, char *str, int len)
{
	char	*tmp;
	char	*buf_ptr;

	len = (len >= 0) ? len : ft_strlen(str);
	buf_ptr = (params->size >= BUFF_PARAMS) ? params->buf_extra : params->buf;
	if ((params->size + len) >= BUFF_PARAMS)
	{
		tmp = ft_memalloc((params->size + len + 1) * sizeof(char));
		ft_memcpy(tmp, buf_ptr, params->size);
		if (params->size >= BUFF_PARAMS)
			ft_memdel((void **)&(params->buf_extra));
		ft_memcpy(tmp + params->size, str, len);
		params->buf_extra = tmp;
	}
	else
		ft_memcpy(&params->buf[params->size], str, len);
	params->size += len;
	return (params->size);
}

/*
** Put the string <str> in the buffer <params->{buf|buf_extra}> and set
** the size <params->size> to <len>
** <alloc> define if <str> has been malloc. (0:no)
*/

void	put_in_buff(t_params *params, char *str, size_t len, int alloc)
{
	if (len >= BUFF_PARAMS)
	{
		if (params->size >= BUFF_PARAMS)
			free(params->buf_extra);
		if (alloc)
			params->buf_extra = str;
		else
		{
			params->buf_extra = (char *)ft_memalloc(len * sizeof(char));
			ft_memcpy(params->buf_extra, str, len);
		}
	}
	else
	{
		ft_memcpy(params->buf, str, len);
		ft_memset(&params->buf[len], 0, BUFF_PARAMS - len);
		if (alloc)
			free(str);
	}
	params->size = len;
}

/*
** Set the precision for the current <params>
** exemple :  "42"  with precision 4 =>  "0042"
**           "-42"  with precision 4 =>  "-0042"
**           " 42"  with precision 4 =>  " 0042"
*/

void	precision(t_params *params, int shift)
{
	char	*buf_ptr;
	int		i;
	int		len;
	char	*tmp;

	if (params->precision < 0)
		return ;
	buf_ptr = (params->size >= BUFF_PARAMS) ? params->buf_extra : params->buf;
	len = params->size - shift;
	tmp = (char *)ft_memalloc((ft_max(len, params->precision) + shift + 1));
	if (len > params->precision)
	{
		i = 0;
		while (buf_ptr[shift + i] == '0' && (len - i) >= params->precision)
			i++;
		ft_memcpy(tmp, buf_ptr + shift + i, ft_strlen(&buf_ptr[shift + i]));
	}
	else
	{
		ft_memset(tmp, '0', params->precision - len);
		ft_memcpy(&tmp[params->precision - len], &buf_ptr[shift], len);
	}
	put_in_buff(params, buf_ptr, shift, 0);
	add_to_buff(params, tmp, ft_strlen(tmp));
	free(tmp);
}
