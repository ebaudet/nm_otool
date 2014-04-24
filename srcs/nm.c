/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/23 12:32:36 by ebaudet           #+#    #+#             */
/*   Updated: 2014/04/24 19:53:52 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mach-o/loader.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include "math.h"



void	ft_otool(char *av)
{
	int fd;
	struct stat stat_buf;
	size_t size;

	char *addr = NULL;
	struct mach_header_64 *mh;
	struct load_command *lc;
	struct segment_command_64 *sc;
	struct section_64 *section;
	char	*copy;

	// Open the file and get its size
	fd = open(av, O_RDONLY);
	fstat(fd, &stat_buf);
	size = stat_buf.st_size;

	// Map the file to memory
	addr = mmap(0, size, PROT_READ | PROT_WRITE, MAP_FILE | MAP_PRIVATE, fd, 0);
	copy = addr;
	// The first bytes of a Mach-O file comprise its header
	mh = (struct mach_header_64 *)addr;

	// Load commands follow the header
	addr += sizeof(struct mach_header_64);

	printf("There are %d load commands\n", mh->ncmds);

	unsigned int	i;

	i = 0;
	while (i < mh->ncmds)
	{
		lc = (struct load_command *)addr;
		
		if (lc->cmdsize == 0)
		{
			i++;
			continue;
		}
		if (lc->cmd == LC_SEGMENT_64)
		{
			sc = (struct segment_command_64 *)addr;
			if (ft_strcmp(sc->segname, "__TEXT") == 0)
			{
				unsigned int		k;

				k = 0;
				addr += sizeof(struct segment_command_64);
				section = (struct section_64 *)addr;
				while (k < sc->nsects)
				{
					section = (struct section_64 *)addr;
					addr += sizeof(struct section_64);
					///section += section->offset;
					if (ft_strcmp(section->sectname, "__text") == 0)
					{
						unsigned int		j;

						j = 0;
						while (j < section->size)
						{
							if (!(j % 16))
							{
								ft_putchar('\n');
								ft_puthex(section->addr + j, 16);
							}
							ft_putchar(' ');
							ft_puthex(copy[section->offset + j] & 0xFF, 2);
								//printf("\n%x ", (unsigned int)section->addr + j);
							// printf("| %p (%u)- ", copy, section->offset);
							/*printf("%02x ", copy[section->offset + j] & 0xFF);*/
							j++;
						}
					}
					k++;
				}
			}
		}
		addr += lc->cmdsize;
		i++;
	}
	munmap(addr, size);
	close(fd);
}

int		main(int ac, char **av)
{
	int		i;

	i = 0;
	if (ac == 1)
		ft_otool("a.out");
	else
	{
		while (av[++i])
			ft_otool(av[i]);
	}
	return (0);
}
