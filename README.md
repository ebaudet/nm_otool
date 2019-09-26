# NM / OTOOL


## NM :
`ddiff ./ft_nm nm bin-tests/f*`<br>
=>
```
@@ -1,5 +1,3 @@
-
-bin-tests/ffff:
 0000000100009560 s _.str
 00000001000095e0 s _.str
```

```
$ ddiff ./ft_nm nm bin-tests/ar_name_chiant
$ ./ft_nm bin-tests/ar_name_chiant > ~/.ddiff/dif1
$ nm bin-tests/ar_name_chiant > ~/.ddiff/dif2
/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/nm: Mach-O universal file: bin-tests/ar_name_chiant for architecture x86_64 is not a Mach-O file or an archive file.
```

```
$ ddiff ./ft_nm nm bin-tests/ffff
$ ./ft_nm bin-tests/ffff > ~/.ddiff/dif1
$ nm bin-tests/ffff > ~/.ddiff/dif2
/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/nm: bin-tests/ffff truncated or malformed object (load commands extend past the end of the file)
```

`segfault` sur `./ft_nm bin-tests/ahah_gotcha.o`<br>

OK<br>

## OTOOL :
```
$ ./ft_otool bin-tests/ffff
bin-tests/ffff:
Contents of (__TEXT,__text) section
0000000100000ef0	00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
0000000100000f00	00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
0000000100000f10	00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
0000000100000f20	00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
0000000100000f30	00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
0000000100000f40	00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
0000000100000f50	00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
0000000100000f60	00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
0000000100000f70	00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
0000000100000f80	00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
0000000100000f90	00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
0000000100000fa0	00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
0000000100000fb0	00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
0000000100000fc0	00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
0000000100000fd0	00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
0000000100000fe0	00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
0000000100000ff0	00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
0000000100001000	ASAN:DEADLYSIGNAL
=================================================================
==38543==ERROR: AddressSanitizer: SEGV on unknown address 0x00010aa4c000 (pc 0x0001078594d9 bp 0x7fff583a8780 sp 0x7fff583a8760 T0)
==38543==The signal is caused by a READ memory access.
    #0 0x1078594d8 in print_section_64 (ft_otool:x86_64+0x1000024d8)
    #1 0x10785926e in print_section (ft_otool:x86_64+0x10000226e)
    #2 0x1078591fb in loop_lc_segment (ft_otool:x86_64+0x1000021fb)
    #3 0x107859706 in ot_binary_handler (ft_otool:x86_64+0x100002706)
    #4 0x107858fe6 in ot_type_handler (ft_otool:x86_64+0x100001fe6)
    #5 0x107859c9f in treatment_file (ft_otool:x86_64+0x100002c9f)
    #6 0x1078590eb in main (ft_otool:x86_64+0x1000020eb)
    #7 0x7fff8f302234 in start (libdyld.dylib:x86_64+0x5234)

==38543==Register values:
rax = 0x000000010aa4b000  rbx = 0x0000000000000000  rcx = 0x0000000000001000  rdx = 0x0000000000001000
rdi = 0x0000000000000001  rsi = 0x0000000000000002  rbp = 0x00007fff583a8780  rsp = 0x00007fff583a8760
 r8 = 0x0000000000000001   r9 = 0x0000200000000000  r10 = 0x0000000000000001  r11 = 0x0000000000000246
r12 = 0x0000000000000000  r13 = 0x0000000000000000  r14 = 0x0000000000000000  r15 = 0x0000000000000000
AddressSanitizer can not provide additional info.
SUMMARY: AddressSanitizer: SEGV (ft_otool:x86_64+0x1000024d8) in print_section_64
==38543==ABORTING
[1]    38543 abort      ./ft_otool bin-tests/ffff
```
OK<br>
A little slow<br>

## DDIFF :
Script pour faire la comparaison entre la sortie de deux commandes

#### NAME
	ddiff - make a diff between two commands

#### USAGE
	ddiff <cmd1> <cmd2> [arguments]

#### SOURCES

```
ddiff () {
	mkdir -p ~/.ddiff
	if [ $# -lt 2 ]
	then
		echo "DDIFF\n\n"
		echo "\033[;1mNAME\033[0m"
		echo "\tddiff - make a diff between two commands\n"
		echo "\033[;1mUSAGE\033[0m"
		echo "\t\033[;1mddiff\033[0m <\033[;4mcmd1\033[0m> <\033[;4mcmd2\033[0m> [\033[;4marguments\033[0m]\n"
	else
		CMD1=$1
		CMD2=$2
		if [ $# -eq 2 ]
		then
			ARGS=""
		else
			shift
			shift
			ARGS=$@
		fi
		CMD_EXEC="$CMD1 $ARGS > ~/.ddiff/dif1"
		echo "\033[33m$ $CMD_EXEC\033[0m"
		sh -c $CMD_EXEC
		CMD_EXEC="$CMD2 $ARGS > ~/.ddiff/dif2"
		echo "\033[33m$ $CMD_EXEC\033[0m"
		sh -c $CMD_EXEC
		CMD_EXEC="git --no-pager diff --no-index ~/.ddiff/dif1 ~/.ddiff/dif2"
		echo "\033[33m$ $CMD_EXEC\033[0m"
		sh -c $CMD_EXEC
	fi
}
```