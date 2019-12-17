# NM / OTOOL

## Installation :

```
make

make test
```

## Uninstall :

Please remove the `~/.ddiff` folder if you used `./ddiff.sh` as defined in the
[ddiff.sh](#ddiffsh-) part.

## NM :

usage :

```
$ ./ft_nm -h
USAGE: ./ft_nm [-pPr][-arch] <input files>

OPTIONS:

General options:
-h, --help, --usage	- Display available options
-p	- Don't sort; display in symbol-table order.
-P	- Don't sort inverse; display in symbol-table inverse order.
-r	- Sort in reverse order.
-arch	- Display symbole for all architectures contained in the binary.
```

Example :
```
$ ./ft_nm /bin/echo
                 U ___error
0000000100000000 T __mh_execute_header
                 U _exit
                 U _malloc
                 U _strcmp
                 U _strerror
                 U _strlen
                 U _write
                 U _writev
                 U dyld_stub_binder
```

Test it with ddiff :
```
$ ./ddiff.sh ./ft_nm nm /bin/ls
> ./ft_nm /bin/ls > ~/.ddiff/dif1
> nm /bin/ls > ~/.ddiff/dif2
> git --no-pager diff --no-index ~/.ddiff/dif1 ~/.ddiff/dif2
```

## OTOOL :

usage :

```
$ ./ft_nm [FILE]
```

Example :

```
$ ./ft_otool /bin/echo
/bin/echo:
Contents of (__TEXT,__text) section
0000000100000c3f	55 48 89 e5 41 57 41 56 41 55 41 54 53 48 83 ec
0000000100000c4f	18 41 89 ff 66 c7 45 d0 20 00 66 c7 45 d2 0a 00
[...]
0000000100000e5f	00 48 8d 35 44 01 00 00 bf 02 00 00 00 ba 01 00
0000000100000e6f	00 00 e8 2e 00 00 00 bf 01 00 00 00 e8 06 00 00
0000000100000e7f	00
```

Test it with ddiff :
```
$ ./ddiff.sh ./ft_otool "otool -t" /bin/ls
> ./ft_otool /bin/ls > ~/.ddiff/dif1
> otool -t /bin/ls > ~/.ddiff/dif2
> git --no-pager diff --no-index ~/.ddiff/dif1 ~/.ddiff/dif2
```

## ddiff.sh :
Script pour faire la comparaison entre la sortie de deux commandes

Will create a folder `~/.ddiff` and past the stdout of the two command as :<br>
`<cmd1> [arguments] > ~/.ddiff/dif1` and `<cmd1> [arguments] > ~/.ddiff/dif2`

```
$ ./ddiff.sh
DDIFF


NAME
	ddiff - make a diff between two commands

USAGE
	ddiff <cmd1> <cmd2> [arguments]
```

### Uninstall

```
rm -rf ~/ddiff
```
