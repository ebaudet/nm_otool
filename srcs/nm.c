/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/23 12:32:36 by ebaudet           #+#    #+#             */
/*   Updated: 2014/04/23 23:40:14 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*

int		main(int ac, char **av)
{
	(void)av;
	char	*file;

	if (ac == 1)
	{
		file = ft_strdup("a.out");
		ft_putstr(file);
	}
}*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mach-o/loader.h>
#include <sys/mman.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
	(void)argc;
	int fd;
	struct stat stat_buf;
	size_t size;

	char *addr = NULL;
	struct mach_header_64 *mh;
	struct load_command *lc;
	struct segment_command_64 *sc;
	struct section_64 *section;

	// Open the file and get its size
	fd = open(argv[1], O_RDONLY);
	fstat(fd, &stat_buf);
	size = stat_buf.st_size;

	// Map the file to memory
	addr = mmap(0, size, PROT_READ | PROT_WRITE, MAP_FILE | MAP_PRIVATE, fd, 0);

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

		ft_putnbr(i);
		ft_putchar('\n');
		if (lc->cmdsize == 0)
			continue;

		// If the load command is a (64-bit) segment,
		// print  about the segment
		if (lc->cmd == LC_SEGMENT_64)
		{
			sc = (struct segment_command_64 *)addr;

			ft_putstr("test0");
			if (ft_strcmp(sc->segname, "__TEXT") == 0)
			{
				unsigned int		i;

				i = 0;
				addr += sizeof(struct segment_command_64);
				section = (struct section_64 *)addr;
				while (i < sc->nsects)
				{
					section = (struct section_64 *)addr;
					addr += sizeof(struct section_64);
					///section += section->offset;
					ft_putstr("sectname : ");
					ft_putstr(section->sectname);
					ft_putstr("\n");
					if (ft_strcmp(section->sectname, "__text") == 0)
					{
						ft_putstr("coucou");
						char	*val = (char *)section->addr;
						// unsigned int	i = 0;
						ft_putendl("texte :");
						printf("%p\n%llu\n", val, section->size);

						printf("%s\n", (char *)section->addr);
						return (0);
						/*while (i < section->size)
						{
							ft_putchar(val[i]);
							i++;
						}*/
						/*printf("\nSECTION_64:\nsectname %s\n\t"
							"segname %s\n\t"
							"addr 0x%llu\n\t"
							"size 0x%llu\n\t"
							"offset 0x%u\n\t"
							"align 0x%u\n\t"
							"reloff 0x%u\n\t"
							"nreloc 0x%u\n\t"
							"flags 0x%u\n\t"
							"reserved1 0x%u\n\t"
							"reserved2 0x%u\n\t"
							"reserved3 0x%u\n\t",
							section->sectname,
							section->segname,
							section->addr,
							section->size,
							section->offset,
							section->align,
							section->reloff,
							section->nreloc,
							section->flags,
							section->reserved1,
							section->reserved2,
							section->reserved3
						);*/
					}

					i++;
				}
			}
			/*
			printf("if : '0x%08x'\n", lc->cmd);
			printf("Segment %s\n\t"
				"vmaddr 0x%llx\n\t"
				"vmsize 0x%llx\n\t"
				"fileoff %llu\n\t"
				"filesize %llu\n\t"
				"section %u\n\t"
				"flags 0x%08x\n",
				sc->segname,
				sc->vmaddr,
				sc->vmsize,
				sc->fileoff,
				sc->filesize,
				sc->nsects,
				sc->flags);
			section = (struct section_64 *)addr;
			printf("\nSECTION_64:\nsectname %s\n\t"
				"segname %s\n\t"
				"addr 0x%llu\n\t"
				"size 0x%llu\n\t"
				"offset 0x%u\n\t"
				"align 0x%u\n\t"
				"reloff 0x%u\n\t"
				"nreloc 0x%u\n\t"
				"flags 0x%u\n\t"
				"reserved1 0x%u\n\t"
				"reserved2 0x%u\n\t"
				"reserved3 0x%u\n\t",
				section->sectname,
				section->segname,
				section->addr,
				section->size,
				section->offset,
				section->align,
				section->reloff,
				section->nreloc,
				section->flags,
				section->reserved1,
				section->reserved2,
				section->reserved3
			);
			*/
        }

        // Advance to the next load command    
        addr += lc->cmdsize;
        i++;
    }

    printf("\nDone.\n");

    munmap(addr, size);
    close(fd);

    return 0;
}