/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sizeof_mach_header.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 13:44:20 by ebaudet           #+#    #+#             */
/*   Updated: 2019/09/26 13:53:45 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

size_t	sizeof_mach_header(t_arch arch)
{
	if (arch == E_32B)
		return (sizeof(struct mach_header));
	return (sizeof(struct mach_header_64));
}
