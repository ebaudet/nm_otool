/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ot_binary_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 13:34:46 by ebaudet           #+#    #+#             */
/*   Updated: 2019/09/30 16:57:30 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

int		ot_binary_handler(t_otool *otool)
{
	struct mach_header	*mh;
	struct load_command	*lc;
	char				*addr;
	unsigned int		i;

	mh = (struct mach_header *)otool->ptr;
	if (!set_arch(otool, mh->magic))
		return (-1);
	addr = otool->ptr + sizeof_mach_header(otool->arch);
	i = 0;
	while (i < obed(mh->ncmds, otool))
	{
		lc = (struct load_command *)addr;
		if (obed(lc->cmd, otool) == otool->segment)
			loop_lc_segment(otool, addr);
		addr = (char *)lc + obed(lc->cmdsize, otool);
		if (sec_ptr(addr))
		{
			return (file_error("truncated or malformed object (load commands ex\
tend past the end of the file)", otool->file));
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
