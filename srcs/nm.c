/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/23 12:32:36 by ebaudet           #+#    #+#             */
/*   Updated: 2014/04/23 16:08:32 by ebaudet          ###   ########.fr       */
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

    for (unsigned int i = 0; i < mh->ncmds; i++) {
        lc = (struct load_command *)addr;

        ft_putnbr(i);
        ft_putchar('\n');
        if (lc->cmdsize == 0)
        	continue;

        // If the load command is a (64-bit) segment,
        // print information about the segment
        if (lc->cmd == LC_SEGMENT_64)
        {
        	printf("if : '0x%08x'\n", lc->cmd);
            sc = (struct segment_command_64 *)addr;
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
        }
        else
        {
        	printf("else : '0x%08x'\n", lc->cmd);
        	sc = (struct segment_command_64 *)addr;
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
        }

        // Advance to the next load command    
        addr += lc->cmdsize;
    }

    printf("\nDone.\n");

    munmap(addr, size);
    close(fd);

    return 0;
}