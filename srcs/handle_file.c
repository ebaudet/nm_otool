/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 16:37:38 by ebaudet           #+#    #+#             */
/*   Updated: 2019/05/09 19:32:47 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "nm.h"
#include "libft.h"
#include "libftprintf.h"

int		handle_file(t_nm *nm)
{
	int				fd;
	struct stat		buf;
	int				return_value;
	char			*ptr;

	nm->flag |= FLAG_PRINT;
	return_value = EXIT_SUCCESS;
	if ((fd = open(nm->file, O_RDONLY)) < 0)
		return (nm_error("No such file or directory.", nm));
	if (fstat(fd, &buf) < 0)
		return (nm_error("Error fstat.", nm));
	if (S_ISDIR(buf.st_mode))
		return (nm_error(": Is a directory.", nm));
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
				== MAP_FAILED)
		return (nm_error("Error mmap.", nm));
	get_ptr(ptr);
	get_size(buf.st_size);
	if (handle_type(nm, ptr, NULL) == 0)
		return_value = nm_error("The file was not recognized as a valid objec\
t file\n", nm);
	if (munmap(ptr, buf.st_size) < 0)
		return_value = nm_error("Error munmap.", nm);
	close(fd);
	return (return_value);
}
