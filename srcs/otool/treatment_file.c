/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treatment_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 13:32:36 by ebaudet           #+#    #+#             */
/*   Updated: 2019/09/30 17:22:30 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

int		treatment_file(char *file)
{
	int				fd;
	struct stat		buf;
	t_otool			otool;
	int				exit;

	otool.file = file;
	otool.is_fat = FALSE;
	otool.is_arch = FALSE;
	if ((fd = open(file, O_RDONLY)) < 0)
		return (file_error("Erreur d'ouverture du fichier ", file));
	if (fstat(fd, &buf) < 0)
		return (file_error("Erreur fstat du fichier ", file));
	if (S_ISDIR(buf.st_mode))
		return (file_error(": Is a directory", file));
	if ((otool.ptr_file = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
		== MAP_FAILED)
		return (file_error("Erreur mmap du fichier ", file));
	get_ptr(otool.ptr_file);
	get_size(buf.st_size);
	exit = ot_type_handler(&otool, NULL);
	if (munmap(otool.ptr_file, buf.st_size) < 0)
		return (file_error("Erreur munmap du fichier ", file));
	close(fd);
	return (exit);
}
