/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/23 12:32:36 by ebaudet           #+#    #+#             */
/*   Updated: 2019/09/30 14:03:47 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include "libftprintf.h"

int		nm_error(char *message, t_nm *nm)
{
	ft_printf_fd(2, "%s: %s %s\n", nm->command, nm->file, message);
	return (EXIT_FAILURE);
}

void	nm_init(t_nm *nm, char **av)
{
	nm->file = NULL;
	nm->command = av[0];
	nm->av = av;
	nm->flag = 0;
}

int		main(int ac, char **av)
{
	t_nm		nm;
	int			i;
	int			return_value;
	t_symtable	*list;
	static char	default_name[] = "a.out";

	return_value = EXIT_SUCCESS;
	nm_init(&nm, av);
	nm.list = &list;
	if (ac < 2 && (nm.file = default_name))
		return (handle_file(&nm));
	nm.file = av[1];
	if ((i = nm_flag_handler(av, &(nm.flag))) < 0)
		return (return_value);
	nm.flag = ((ac - i - 2) > 0) ? nm.flag | FLAG_PRINT : nm.flag;
	nm.flag_save = nm.flag;
	while (++i < ac)
	{
		nm.flag = nm.flag_save;
		nm.file = av[i];
		return_value |= handle_file(&nm);
	}
	return (return_value);
}
