/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 17:58:12 by ebaudet           #+#    #+#             */
/*   Updated: 2019/02/13 23:27:59 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "libft.h"

/*
** This function find the last numeric char of chained numeric chars in <str>.
*/

char	*find_last_number(const char *str)
{
	int		i;

	i = 0;
	while (str && str[i] && str[i] >= '0' && str[i] <= '9')
		i++;
	return ((char *)&str[i]);
}

/*
** This function search the first occurance of one of the caraters of needle in
** heystack.
*/

char	*ft_strstrchr(const char *haystack, const char *needle)
{
	while (*haystack && ft_strchr(needle, haystack[0]) == NULL)
		haystack++;
	if (!*haystack)
		return (NULL);
	else
		return ((char *)haystack);
}

/*
** Fill the string <str> to fit the size <len> with the charact <c>
** at position <pos right:0,left:1>
*/

void	fill_string(t_params *params, int c, size_t len, int pos)
{
	char	*str_tmp;
	char	*str;

	str = (params->size) >= BUFF_PARAMS ? params->buf_extra : params->buf;
	if ((int)len <= (int)params->size)
		return ;
	str_tmp = (char *)ft_memalloc((len + 1) * sizeof(char));
	if (pos == 0)
	{
		str_tmp = ft_memset(str_tmp, c, len - params->size);
		ft_memcpy(str_tmp + len - params->size, str, params->size);
	}
	else
	{
		ft_memcpy(str_tmp, str, params->size);
		ft_memset(str_tmp + params->size, c, len - params->size);
	}
	put_in_buff(params, str_tmp, len, 1);
}

/*
** Fill the string <str> to fit the size <len> with zero before numbers.
*/

void	fill_zero(t_params *params, size_t len)
{
	char	*str_tmp;
	char	*str;
	int		i;
	int		j;

	str = (params->size) >= BUFF_PARAMS ? params->buf_extra : params->buf;
	if ((int)len <= params->size)
		return ;
	str_tmp = (char *)ft_memalloc((len + 1) * sizeof(char));
	i = -1;
	while (str[++i] && !((str[i] >= '1' && str[i] <= '9')
		|| (str[i] >= 'a' && str[i] <= 'f')))
		str_tmp[i] = str[i];
	j = -1;
	while (++j < (int)(len - params->size))
		str_tmp[i + j] = '0';
	while (str[i])
	{
		str_tmp[i + j] = str[i];
		i++;
	}
	put_in_buff(params, str_tmp, len, 1);
}

/*
** Check if the flag is set.
*/

int		check_flag(t_params *params, t_flag flag)
{
	if ((params->flag | flag) == params->flag)
		return (1);
	return (0);
}
