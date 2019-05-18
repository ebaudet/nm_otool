# NM / OTOOL


## NM :
diff with :<br>
`$ make && ddiff ./ft_nm nm /usr/lib/libXSEvent.dylib`<br>
=> n'affiche pas le nom de la lib nromalement.<br>
`$ make && ddiff ./ft_nm nm /usr/lib/libxcselect.dylib`<br>
=> n'affiche pas le nom de la lib nromalement.<br>
`$ make && ddiff ./ft_nm nm /usr/lib/libc++.dylib`<br>
=> I (indirect symbol)

ex error :
```
	 0000000000011248 T __ZNKSt16nested_exception14rethrow_nestedEv
	 00000000000499c4 T __ZNKSt18bad_variant_access4whatEv
	 00000000000496c4 T __ZNKSt19bad_optional_access4whatEv
	                  U __ZNKSt20bad_array_new_length4whatEv
	-000000000000021d I __ZNKSt20bad_array_new_length4whatEv
	+                 I __ZNKSt20bad_array_new_length4whatEv (indirect for __ZNKSt20bad_array_new_length4whatEv)
```
-> ne pas afficher l'adresse, mais le texte suivant : "` (indirect for %name%)`"

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