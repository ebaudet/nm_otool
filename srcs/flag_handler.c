/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 03:03:08 by ebaudet           #+#    #+#             */
/*   Updated: 2019/04/29 16:14:05 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "nm.h"
#include "libftprintf.h"

static int		flag_help(char **av)
{
	ft_printf("%+kUSAGE%k: ");
	ft_putstr(av[0]);
	ft_printf(" [-pPr][-arch] <input files>\n\n%+kOPTIONS%k:\n\n\
%-kGeneral options%k:\n\
-%+khelp%k\t- Display available options\n\
-%+kp%k\t- Don't sort; display in symbol-table order.\n\
-%+kP%k\t- Don't sort inverse; display in symbol-table inverse order.\n\
-%+kr%k\t- Sort in reverse order.\n\
-%+karch%k\t- Display symbole for all architectures contained in the \
binary.\n");
	return (-1);
}

static void		add_flag(char *av, int *flag)
{
	int		i;

	if (ft_strcmp(av, "arch") == 0)
	{
		*flag |= FLAG_ARCH;
		return ;
	}
	i = -1;
	while (av[++i])
	{
		if (av[i] == 'p')
			*flag = (*flag & ~FLAG_PCAPS & ~FLAG_R & ~FLAG_N) | FLAG_P;
		if (av[i] == 'P')
			*flag = (*flag & ~FLAG_P & ~FLAG_R & ~FLAG_N) | FLAG_PCAPS;
		if (av[i] == 'r')
			*flag = (*flag & ~FLAG_P & ~FLAG_PCAPS & ~FLAG_N) | FLAG_R;
		if (av[i] == 'n')
			*flag = (*flag & ~FLAG_P & ~FLAG_PCAPS & ~FLAG_R) | FLAG_N;
	}
}

int				nm_flag_handler(char **av, int *flag)
{
	int		i;

	i = 0;
	while (av[++i])
	{
		if (ft_strcmp(av[i], "-help") == 0)
			return (flag_help(av));
		if (av[i][0] != '-')
			break ;
		if (ft_strcmp(av[i], "--") == 0)
		{
			i++;
			break ;
		}
		if (av[i][0] == '-' && av[i][1])
			add_flag(&av[i][1], flag);
		else
			break ;
		if (i < 0)
			break ;
	}
	return (i - 1);
}
