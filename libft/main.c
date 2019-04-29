/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/21 20:41:51 by ebaudet           #+#    #+#             */
/*   Updated: 2019/02/12 01:23:11 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libftprintf.h"
#include "libft.h"

#include <assert.h>
#include <fcntl.h>

#define test_printf(...) \
	capture_stdout(); \
	printf_ret = printf(__VA_ARGS__); \
	printf_out = strdup(capture_stdout_get_buffer()); \
	ft_printf_ret = ft_printf(__VA_ARGS__); \
	ft_printf_out = strdup(capture_stdout_get_buffer()); \
	capture_stdout_destroy(); \
	test++; \
	if ((printf_ret == ft_printf_ret) && !ft_strcmp(printf_out, ft_printf_out))\
		ft_putstr("TEST: \033[32;1mOK\033[0m\n"); \
	else \
	{ \
		errors++; \
		ft_printf("\033[31;1m[ERROR]\033[0m : ft_printf(\033[34;1m%s\033[0m)\n\
(%5d) -->%.s<--\n(%5d) -->%.s<--\n", #__VA_ARGS__, ft_printf_ret, ft_printf_out,\
printf_ret, printf_out); \
	} \
	free(printf_out); \
	free(ft_printf_out);

const int	READ = 0;
const int	WRITE = 1;

int	out_pipe[2];
char out_buffer[10 * 1000];

#include <unistd.h>
#define NO_FD_OPENED -1
int			saved_stdout = NO_FD_OPENED;

static void	capture_close_saved_stdout(void);
static void	capture_stdout(void);
static void	capture_unblock_fd(int fd);
static char	*capture_stdout_get_buffer(void);
static void	capture_stdout_destroy(void);

// ============== MAIN DE TEST ================================================/
/*
** MAIN DE TEST GENERAL :
*/

int			main(void)
{
	int		test = 0;
	int		errors = 0;
	int		printf_ret;
	char	*printf_out;
	int		ft_printf_ret;
	char	*ft_printf_out;
	int		i;
	char	*pointer = NULL;

	i = 12;
	ft_printf("Hello World !\n");
	// exit(0);

	ft_printf("%#k  -----------------------------------  %k\n");
	ft_printf("%#k |  ======= STARTING TESTS ========  | %k\n");
	ft_printf("%#k  -----------------------------------  %k\n\n");

	ft_printf("%#kTest buffer depassé :%k\n");
	test_printf("127 : %s\n",
"lk jdfsgks d;fgk jsd;fg kjsd;lfkg jsd;flkgjsd;lfkgjvs;dkfjg ;sdlkf jg;dslkfjgv;sdkfjgv;sdlkcfmg;skldj f;lkgjmsv;dfkjg s;dlfkgje");
	test_printf("128 : %s\n",
"lk jdfsgks d;fgk djsd;fg kjsd;lfkg jsd;flkgjsd;lfkgjvs;dkfjg ;sdlkf jg;dslkfjgv;sdkfjgv;sdlkcfmg;skldj f;lkgjmsv;dfkjg s;dlfkgje");

	test_printf("296 : %s\n",
"qweryuiopasdfghjklzxcvbnnm qweryuiopasdfghjklzxcvbnnm qweryuiopasdfghjklzxcvbnnm qweryuiopasdfghjklzxcvbnnm qweryuiopasdfghjklzxcvbnnm qweryuiopasdfghjklzxcvbnnm qweryuiopasdfghjklzxcvbnnm qweryuiopasdfghjklzxcvbnnm qweryuiopasdfghjklzxcvbnnm qweryuiopasdfghjklzxcvbnnm qweryuiopasdfghjklzxcvbnnm");

	test_printf("%300d", 42);
	test_printf("%0300d", 42);
	test_printf("%0.300d\n", 42);
	// exit(0);
	ft_printf("\n%#kTest des float :%k\n");
	test_printf("12.5 = %f", 12.5);
	test_printf("-25.744 = %f", -25.744);
	test_printf("-25.745 = %f", -25.745);
	test_printf("3.145 = %f", 3.145);
	test_printf("3.146 = %f", 3.146);
	test_printf("3.144 = %f", 3.144);
	test_printf("1111123.3456 = %f", 1111123.3456);
	test_printf("% ");
	test_printf("%f", 1126.5);
	test_printf("%70.70d", 12);
	test_printf("%150.150d", 12);
	test_printf("%250.250d", 12);
	test_printf("%250.250d", 12);
	test_printf("%254.254d", 12);
	test_printf("%250.250d", 12);
	test_printf("%888.888d", 12);
	test_printf("%250.250d", 12);

	printf("printf %f\n", 123456789123.12);
	fflush(stdout);

	// ft_printf("123456789123.12 = %Lf\n", 123456789123.12);
	// exit(0);

	// todo: handle float 2^65 -> long long
	// test_printf("36893488147419103232.0 = %Lf\n", 36893488147419103232.0);
	// test_printf("%Lf\n", 36893488147419103232.0); //14925 segmentation fault
	// => handle this
	ft_printf("%#kTest différents types :%k\n");
	test_printf("char-%c-%s-%s-%c-%s-%c-\n", 'a', "un", "deux", 'b', "trois",
	 'e');
	test_printf("char-%c-%s-%s-%c-%s-%c-%-4i\n", 'a', "un", "deux", 'b',
	            "trois", 'd', -12);
    test_printf("");
	test_printf("\n----------\n");
	test_printf("\nabcdefg\nh");
	test_printf(". .\n");
	test_printf("coucou\n");
	test_printf("\n%yla% => %\n");
	// exit(0);
	// printf("%bla% => %\n");
	test_printf("|nie% -  %d|\n");
	test_printf("Je m'appelle %s %s, et j'ai %d ans\n", "Emilien", "Baudet",
	            29);
	test_printf("\n----------\n");
	test_printf("&i = %p\n", &i);
	test_printf("%x", 1835);
	test_printf("%X", 1835);
	test_printf("%p", pointer);
	test_printf("1835 = (x)%x, (X)%X, (p)%p", 1835, 1835, pointer);
	test_printf("1835 = (x)%#x, (X)%#X, (p)%p", 1835, 1835, pointer);
	test_printf("octal 123 = %o %#o %o %#o", 123, 123, -123, -123);
	test_printf("coucou%d", i);
	test_printf("\n----------");

	ft_printf("%#k======= TEST DES FLAGS ========%k\n");
	test_printf("without any flags\n'%5d'\n'%5d'\n'%5d'\n'%5d'", 22, -42,
	            1234567, -1234567);
	test_printf("with minus flag\n'%-5d'\n'%-5d'\n'%-5d'\n'%-5d'", 22, -42,
	 1234567, -1234567);
	test_printf("with plus flag\n'%+5d'\n'%+5d'\n'%+5d'\n'%+5d'", 22, -42,
	 1234567, -1234567);
	test_printf("with plus/minus flag\n'%+-5d'\n'%+-5d'\n'%+-5d'\n'%+-5d'", 22,
	 -42, 1234567, -1234567);
	test_printf("with zero flag (ignored if minus option)\n'%05d'\n'%05d'\n'\
%05d'\n'%05d'", 22, -42, 1234567, -1234567);
	test_printf("with zero/plus flag\n'%0+5d'\n'%0+5d'\n'%0+5d'\n'%0+5d'", 22,
	            -42, 1234567, -1234567);
	test_printf("with space option (ignored with plus option)\n'% 5d'\n'% 5d'\n\
'% 5d'\n'% 5d'", 22, -42, 1234567, -1234567);
	test_printf("with space/zero option (ignored with plus option)\n'%0 5d'\n'\
%0 5d'\n'%0 5d'\n'%0 5d'", 22, -42, 1234567, -1234567);
	test_printf("%d %.*s %s", 12, 3, "abcdef", "asdfghjk");

	ft_printf("%#k======= TEST DES TYPES ========%k\n");
	test_printf("%o => %#o, %x => %#x, %X => %#X\n", 15, 15, 15, 15, 15, 15);
	test_printf("%x %x\n", 12, -12);
	test_printf("%.2f", 12.5);
	test_printf("%08.2f", 12.5);
	test_printf("%08.2f", -12.5);
	test_printf("%o %05o\n", 12, 12);
	test_printf("%hhc %hhc", 1, 'c');
	test_printf("{cyan}yolo{eoc} {red}zbra{eoc}\n");
	test_printf("\e[36;1myolo\e[0m \e[31;1mzbra\e[0m\n");
	test_printf("%f, %.1f, %.2f, %.3f, %.4f, %f\n", 123.456, 123.456, 123.456,\
 123.456, 123.456, 123.456); // can segfault
	test_printf("'%15s' '%15.3s' '%4.3s' '%.0s' '%.3s'\n", "qwertyuiop",
	            "qwertyuiop", "qwertyuiop", "qwertyuiop", "qwertyuiop");
	test_printf("'%5%'' '%-5%'\n");
	test_printf("%010x\n", 542);
	test_printf("%lx %llx", 4294967296, 4294967651465465296);
	test_printf("@moulitest: %#.x %#.0x", 0, 0);
	test_printf("@moulitest: %.x %.0x", 0, 0);
	test_printf("@moulitest: %5.x %5.0x", 0, 0);
  	test_printf("'%.x'", 0);
	test_printf("'%.0x'", 0);
	test_printf("'%#.x'", 0);
	ft_printf("t1:");
	test_printf("'%#.0x'", 0);
	ft_printf("t2:");
	test_printf("'%#.0x'", 1);
	ft_printf("t3:");
	test_printf("'%#.1x'", 1);
	test_printf( "'%#.12x'", 1);
	test_printf("'%#12x'", 1);
	test_printf("'%#12.5x'", 1);
	test_printf("'%#-12.5x'", 1);
	test_printf("'%.5x'", 1);
	test_printf("'%#.5x'", 1);
	test_printf("'%#05.12x'", 0);
  	test_printf("%.5x %#.5x %3.5x %#3.5x\n", 1,1,1,1);
  	test_printf("yop '%d' '%.0d' '%.0d' '%.12d' '%.12d'\n", 0,0,1,0,1);
  	test_printf("@moulitest: %s", NULL);
  	test_printf("%5c %-5c\n|", 42, 42);
  	test_printf("|%c|\n",0);
  	test_printf("@moulitest: %#.o %#.0o\n", 0, 0);
	test_printf("%u\n", -1);
	test_printf("%u\n", 4294967295);
	test_printf("%5u\n", 4294967295);
	test_printf("9223372036854775807 = [%lld]\n", 9223372036854775807);
	test_printf("-9223372036854775807 = [%lld]\n", -9223372036854775807);
	test_printf("-9223372036854775808 = [%lld]\n", -9223372036854775805);
	test_printf("-9223372036854775808 = [%lld]\n", -9223372036854775806);
	test_printf("-9223372036854775808 = [%lld]\n", -9223372036854775807);
	test_printf("18446744073709551574(-42) = [%lu]\n", -42);
	test_printf("18446744073709551574(-42) = [%lu]\n", -42);
	test_printf("[%015u]\n", 4294967295);
	test_printf("@moulitest: [%.5u]\n", 42);
	test_printf("%lu\n", -42);
	test_printf("%10s is a string", "");
	test_printf("%-5.2s is a string", "");
	test_printf("%-2.5s is a string", "");
	test_printf("%-.2s is a string", "");
	test_printf("%-5s is a string", "");
	test_printf("%#6o", 2500);
	test_printf("@moulitest: %5.d %5.0d", 0, 0);
	test_printf("%10s is a string", "");
	test_printf("%-5.2s is a string", "");
	test_printf("%#6o", 2500);
	test_printf("@moulitest: %5.d %5.0d", 0, 0);
	test_printf("%lu", -42);

	/*
	** Test des couleurs
	*/
	ft_printf("\n%#kTest des couleurs :%k\n");
	ft_printf("normal colors : \n");
	ft_printf("%kcolor normal%k");
	for (int color=K_BLACK; color <= K_WHITE; color++)
		ft_printf(" - %*kcolor %d%k", color, color);

	ft_printf("\n underline colors : \n");
	ft_printf("%-kcolor normal%k");
	for (int color=K_BLACK; color <= K_WHITE; color++)
		ft_printf(" - %*-kcolor %d%k", color, color);

	ft_printf("\n italic colors : \n");
	ft_printf("%0kcolor normal%k");
	for (int color=K_BLACK; color <= K_WHITE; color++)
		ft_printf(" - %*0kcolor %d%k", color, color);

	ft_printf("\n backgroud colors : \n");
	ft_printf("%#kcolor normal%k");
	for (int color=K_BLACK; color <= K_WHITE; color++)
		ft_printf(" - %*#kcolor %d%k", color, color);

	ft_printf("\n bold colors : \n");
	ft_printf("%+kcolor normal%k");
	for (int color=K_BLACK; color <= K_WHITE; color++)
		ft_printf(" - %*+kcolor %d%k", color, color);
	ft_printf("\n");

	/*
	** Test des Pointeurs
	*/
	ft_printf("\n%#kTest des pointeurs :%k\n");
	test_printf("pointeur integer : %p\n", &i);
	unsigned long l;
	test_printf("pointeur long : %p\n", &l);
	char *str;
	test_printf("pointeur char* : %p\n", &str);
	test_printf("poiteur fonction : %p\n", &strlen);
	test_printf("pointeur null : %p\n", 0);

	/*
	** Test des Modulos
	*/
	ft_printf("\n%#kTest des modulos :%k\n");
	test_printf("%%");
	test_printf("aa%%bb");
	test_printf("%%%%%%%%%%");
	test_printf(".%%.%%.%%.%%.%%.%%.%%.%%.");
	test_printf("%");
	test_printf("% Zoooo");
	test_printf("{%}");
	test_printf("{% %}");
	test_printf("%s", "salut");
	test_printf("%");

	/*
	** Unefinded behavior tests
	*/
	ft_printf("\n%#kTest des Unefinded behavior :%k\n");
	test_printf("%hhs\n", "c");
	test_printf("% ");
	test_printf("%    ");
	test_printf("% \t   ");
	test_printf("% h");
	test_printf("% hZ");
	test_printf("%05%");
	test_printf("% Z", "test");
	test_printf("% Z ", "test");
	test_printf("%010s is a string", "this");
	test_printf("%05c", 42);
	test_printf("% Z", 42);
	test_printf("%zhd", 4294967296);
	test_printf("%zd", 4294967296);
	test_printf("%jhd", 9223372036854775807);
	test_printf("%jd", 9223372036854775807);
	test_printf("%lhl", 9223372036854775807);
	test_printf("%lhlz", 9223372036854775807);
	test_printf("%zj", 9223372036854775807);
	test_printf("%lhh", 2147483647);

	/*
	** Types non gérés
	*/
	ft_printf("\n%#kTest des types non gérés :%k\n");
	// test_printf("123.37 = %g", 123.37);
	// test_printf("%00000002$d %01$d", 1, 2);
	// test_printf("%U", 4294967295);
	// test_printf("%hU", 4294967296);
	// test_printf("%U", 4294967296);

	/*
	** Test des binaires
	*/
	ft_printf("\n%#kTest des binaires :%k\n");
	for (i = -10; i <= 10; i++)
		ft_printf("% 3d = %032b\n", i, i);
	ft_printf("% 10f = %jb\n", 2.5, 2.5);
	ft_printf("% 10f = %jb\n", -2.5, -2.5);
	ft_printf("% 10f = %jb\n", 42.5, 42.5);
	ft_printf("% 10f = %jb\n", -42.5, -42.5);
	ft_printf("% 10f = %b\n", 2.5, 2.5);
	ft_printf("% 10f = %b\n", -2.5, -2.5);
	ft_printf("% 10f = %b\n", 42.5, 42.5);
	ft_printf("% 10f = %b\n", -42.5, -42.5);
	ft_printf("% 10f = %064Lb\n", 2.5, 2.5);
	ft_printf("% 10f = %064Lb\n", -2.5, -2.5);
	ft_printf("% 10f = %064Lb\n", 42.5, 42.5);
	ft_printf("% 10f = %064Lb\n", -42.5, -42.5);

	ft_printf("\n%#kTest des modulos :%k\n");
	test_printf("  ");
	test_printf(" ");
	test_printf("% ");
	test_printf("%");
	test_printf(" %");
	test_printf(" % ");
	test_printf("%    ");
	test_printf("% \t   ");
	test_printf("%d",1);

	fflush(stdout);
	ft_printf("\n\n------------------------------------\n");
	ft_printf("%d/%d tests réussi (%*k%d errors%k)\n",
	          test - errors, test, errors ? K_RED : K_GREEN, errors);

	return (0);
}
// ============== FIN MAIN DE TEST ============================================/

/*
** Fonctions de test
*/

static void	capture_close_saved_stdout(void)
{
	extern int saved_stdout;

	if (saved_stdout != NO_FD_OPENED)
	{
		// fprintf(stderr, "== close %d ==\n", saved_stdout);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout); /* important ! */
		saved_stdout = NO_FD_OPENED;
		close(out_pipe[READ]);
		close(out_pipe[WRITE]);
	}
}

static void	capture_stdout(void)
{
	capture_close_saved_stdout();
	if( pipe(out_pipe) != 0 ) {          /* make a pipe */
		assert(0);
	}
	assert(saved_stdout < 100);
	saved_stdout = dup(STDOUT_FILENO); /* save stdout for display later */
	dup2(out_pipe[WRITE], STDOUT_FILENO);   /* redirect stdout to the pipe */
}

static void	capture_unblock_fd(int fd)
{
	int flags = fcntl(fd, F_GETFL, 0);
	fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

static char	*capture_stdout_get_buffer(void)
{
	int ret;
	fflush(stdout);

	capture_unblock_fd(out_pipe[0]);
	*(out_buffer) = '\0';
	ret = read(out_pipe[READ], out_buffer, 42000); /* read from pipe into buffer */
	out_buffer[ret] = '\0';
	return (out_buffer);
}

static void	capture_stdout_destroy(void)
{
	extern int saved_stdout;
	dup2(saved_stdout, STDOUT_FILENO);  /* reconnect stdout for testing */
	capture_close_saved_stdout();

	// free(cap);
}
