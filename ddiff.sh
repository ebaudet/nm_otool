#!/bin/zsh
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
		# CMD_EXEC="$CMD1 $ARGS"
		echo "\033[33m> $CMD_EXEC\033[0m"
		sh -c $CMD_EXEC
		CMD_EXEC="$CMD2 $ARGS > ~/.ddiff/dif2"
		echo "\033[33m> $CMD_EXEC\033[0m"
		sh -c $CMD_EXEC
		CMD_EXEC="git --no-pager diff --no-index ~/.ddiff/dif1 ~/.ddiff/dif2"
		echo "\033[33m> $CMD_EXEC\033[0m"
		sh -c $CMD_EXEC
	fi
}
ddiff $@
