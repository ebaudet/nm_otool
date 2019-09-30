/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 16:37:38 by ebaudet           #+#    #+#             */
/*   Updated: 2019/09/30 19:03:44 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "nm.h"
#include "libft.h"
#include "libftprintf.h"

static int		nm_error_handle(t_nm *nm, int code_error)
{
	if (code_error == ERROR_LC_PTR)
		nm_error("truncated or malformed object (load commands ex\
tend past the end of the file)", nm);
	else
		nm_error("The file was not recognized as a valid objec\
t file\n", nm);
	return (EXIT_FAILURE);
}

int				handle_file(t_nm *nm)
{
	int				fd;
	struct stat		buf;
	int				return_value;
	char			*ptr;

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
	if ((return_value = handle_type(nm, ptr, NULL)) != EXIT_SUCCESS)
		return_value = nm_error_handle(nm, return_value);
	if (munmap(ptr, buf.st_size) < 0)
		return_value = nm_error("Error munmap.", nm);
	close(fd);
	return (return_value);
}
