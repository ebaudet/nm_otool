# NM / OTOOL


## NM :

```
$ ddiff ./ft_nm nm bin-tests/ar_name_chiant
$ ./ft_nm bin-tests/ar_name_chiant > ~/.ddiff/dif1
$ nm bin-tests/ar_name_chiant > ~/.ddiff/dif2
/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/nm: Mach-O universal file: bin-tests/ar_name_chiant for architecture x86_64 is not a Mach-O file or an archive file.
```

```
segfault pour : (nm aussi)
$ ddiff ./ft_nm nm bin-tests/segfault_nm
```
OK<br>

## OTOOL :
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