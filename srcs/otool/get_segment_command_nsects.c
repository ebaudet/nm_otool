/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_segment_command_nsects.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 13:46:27 by ebaudet           #+#    #+#             */
/*   Updated: 2019/09/26 13:51:21 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

uint32_t	get_segment_command_nsects(char *ptr, t_arch arch)
{
	if (arch == E_32B)
		return (((struct segment_command *)ptr)->nsects);
	return (((struct segment_command_64 *)ptr)->nsects);
}
