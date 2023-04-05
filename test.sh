#!/bin/bash

RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
MAGENTA="\033[35m"
UNDERLINE="\033[4m"
BOLD="\033[1m"
RESET="\033[0m"
OK=$GREEN"OK"$RESET
NG=$RED"NG"$RESET

# # Generate Executable
# # -xc このオプションに続く入力ファイルの言語をcであると明示的に指定します
# # -o 名前をつける
# cat <<EOF | gcc -xc -o a.out -
# #include <stdio.h>
# int main() { printf("hello from a.out\n"); }
# EOF

# cat <<EOF | gcc -xc -o print_args -
# #include <stdio.h>
# int main(int argc, char *argv[]) {
# 	for (int i = 0; argv[i]; i++)
# 		printf("argv[%d] = %s\n", i, argv[i]);
# }
# EOF

cleanup() {
	rm -f cmp out a.out print_args hello.txt pwd.txt file print_args 'f1>'
}

# assert - 診断が偽の時にプログラムを中止する
assert() {
	COMMAND="$1"
	shift
	# コマンドをprint
	# - 変換値をフィールド境界で左揃えにする
	printf '%-60s:' "[$COMMAND]"

	# bashの出力をcmpに保存
	echo -n -e "$COMMAND" | bash >cmp 2>&-
	# bashのexit statusをexpectedに代入
	expected=$?
	# for arg in "$@"
	# do
	# 	mv "$arg" "$arg"".cmp"
	# done

	# minishellの出力をoutに保存
	echo -n -e "$COMMAND" | ./minishell >out 2>&-
	# minishellのexit statusをactualに代入
	actual=$?
	# for arg in "$@"
	# do
	# 	mv "$arg" "$arg"".out"
	# done

	# bashとminishellの出力を比較
	diff cmp out >/dev/null && echo -e -n "  diff $OK" || echo -e -n "  diff $NG"
	# diff cmp out && echo -e -n "  diff $OK" || echo -e -n "  diff $NG"

	# bashとminishellのexit statusを比較
	if [ "$actual" = "$expected" ]; then
		echo -e -n "  status $OK"
	else
		echo -e -n "  status $NG, expected $expected but got $actual"
	fi
	# for arg in "$@"
	# do
	# 	echo -n "  [$arg] "
	# 	diff "$arg"".cmp" "$arg"".out" >/dev/null && echo -e -n "$OK" || echo -e -n "$NG"
	# 	rm -f "$arg"".cmp" "$arg"".out"
	# done
	echo
}

# # REVIEW # #####################################
assert '/bin/pwd'
assert '/bin/ls'
assert '/bin/filethatdoesntexist'
assert '' #empty
assert ' ' #space
assert '	' #tab

# argumant
assert 'cat Makefile'

# echo
assert 'echo aa'
assert 'echo -n aa'

# exit command
assert 'exit'
assert 'exit 42'
assert 'exit 99999999999999999999' #numeric argument required
assert 'exit hello' #numeric argument required
assert 'exit 42Tokyo' #numeric argument required
assert 'exit 42 41 40' #too many arguments
assert 'exit 42 hello' #too many arguments
assert 'exit hello 42' #numeric argument required

# signal
## empty prompt
# ctrl-C → 新しいプロンプト、新しい行
# ctrl-\ → 何も実行されない
# ctrl-D → ミニシェルが終了

## written prompt
# ctrl-C → 新しいプロンプト、新しい行
# → Enterを押しても何も実行されない
# ctrl-\ → 何も実行されない
# ctrl-D → 何も実行されない

## Brock command (cat / grep a)
# ctrl-C → 新しいプロンプト、新しい行 (今：改行されない)
# ctrl-\ → 新しいプロンプト、新しい行　(今：改行されない)
# ctr-D → 新しいプロンプト、新しい行

# double quote
assert 'echo "cat main.c | cat > main.c"'
assert 'echo "hello   world" "42Tokyo"'
assert 'echo "'hello   world'" "42Tokyo"'

# single quote
assert 'echo '''
assert 'echo '$USER''
assert 'echo ' ''
assert 'echo '|''
assert 'echo '>''
assert 'echo 'hello   world' '42Tokyo''
assert 'echo '\"hello   world\"' '42Tokyo''

# env
assert 'env'

# export
assert 'export $KEY="hoge fuga"'
# assert 'env'

# unset
assert 'export $KEY="hoge"'
# assert 'env'
assert 'unset $KEY'
# assert 'env'

# cd & pwd
assert 'cd'
# assert 'pwd'
assert 'cd srcs'
# assert 'pwd'
assert 'cd .'
# assert 'pwd'
assert 'cd ..'
# assert 'pwd'
assert 'cd /../../../././.././'

# relative path
assert 'cat srcs/builtin/ft_cd.c'

# environment path
assert 'unset $PATH'
assert 'ls'
assert 'export PATH=/Library/Frameworks/Python.framework/Versions/3.9/bin:/usr/local/bin:/System/Cryptexes/App/usr/bin:/usr/bin:/bin:/usr/sbin:/sbin:/opt/X11/bin:/Library/Apple/usr/bin:/usr/local/share/dotnet:~/.dotnet/tools:/Library/Frameworks/Mono.framework/Versions/Current/Commands:/Library/Frameworks/Python.framework/Versions/3.9/bin'
assert 'ls'

# Redirect
## Redirecting output
assert 'echo hello >hello.txt' 'hello.txt'
assert 'echo hello >f1>f2>f3' 'f1' 'f2' 'f3'

## Redirecting input
assert 'cat <Makefile'
echo hello >f1
echo world >f2
echo 42Tokyo >f3
assert 'cat <f1<f2<f3'
rm -f f1 f2 f3
assert 'cat <hoge'

## Appending Redirected output
assert 'pwd >>pwd.txt' 'pwd.txt'
assert 'pwd >>pwd.txt \n pwd >>pwd.txt' 'pwd.txt'

## Here Document
# assert 'cat <<EOF\nhello\nworld\nEOF\nNOPRINT'
# assert 'cat <<EOF<<eof\nhello\nworld\nEOF\neof\nNOPRINT'
# assert 'cat <<EOF\nhello\nworld'
# assert 'cat <<E"O"F\nhello\nworld\nEOF\nNOPRINT'

# Pipe
assert 'cat Makefile | grep minishell > file'

# GoCrazy & History
# $ ./minishell
# $ hogehoge
# Ctrl-C
# return

# UP
# DOWN

assert 'dsbksdgbksdghsd'
assert 'cat | cat | cat | ls'

# Expand Variable
assert 'echo $USER'
assert 'echo $PATH'
assert 'echo $USER$PATH$TERM'
assert 'echo "$USER"'

# BONUS
assert 'echo "'$USER'"'
assert 'echo '"$USER"''

cleanup

##################################################
# # Empty line (EOF)
# assert ''

# assert '/bin/pwd'
# assert '/bin/ls'
# assert '/bin/echo'

# # Search command path without args
# assert 'pwd'
# assert 'echo'
# assert 'ls'
# assert './a.out'

# # no such command
# assert 'a.out'
# assert 'nosuchfile'

# # exit command
# assert 'exit'
# assert 'exit 42'
# assert 'exit 256'
# assert 'exit 999'
# assert 'exit 99999999999999999999'
# assert 'exit hello'
# assert 'exit 42Tokyo'
# assert 'exit 42 41 40'
# assert 'exit 42 hello'
# assert 'exit hello 42'

# # Tokenize
# ## unquoted word
# assert 'ls /'
# assert 'echo hello    world     '
# assert 'nosuchfile\n\n'

# ## single quote
# assert "./print_args 'hello   world' '42Tokyo'"
# assert "echo 'hello   world' '42Tokyo'"
# assert "echo '\"hello   world\"' '42Tokyo'"

# ## double quote
# assert './print_args "hello   world" "42Tokyo"'
# assert 'echo "hello   world" "42Tokyo"'
# assert "echo \"'hello   world'\" \"42Tokyo\""

# ## combination
# assert "echo hello'      world'"
# assert "echo hello'  world  '\"  42Tokyo  \""

# # Redirect
# ## Redirecting output
# assert 'echo hello >hello.txt' 'hello.txt'
# assert 'echo hello >f1>f2>f3' 'f1' 'f2' 'f3'

# ## Redirecting input
# assert 'cat <Makefile'
# echo hello >f1
# echo world >f2
# echo 42Tokyo >f3
# assert 'cat <f1<f2<f3'
# rm -f f1 f2 f3
# assert 'cat <hoge'

# ## Appending Redirected output
# assert 'pwd >>pwd.txt' 'pwd.txt'
# assert 'pwd >>pwd.txt \n pwd >>pwd.txt' 'pwd.txt'

# ## Here Document
# assert 'cat <<EOF\nhello\nworld\nEOF\nNOPRINT'
# assert 'cat <<EOF<<eof\nhello\nworld\nEOF\neof\nNOPRINT'
# assert 'cat <<EOF\nhello\nworld'
# assert 'cat <<E"O"F\nhello\nworld\nEOF\nNOPRINT'

# # Pipe
# assert 'cat Makefile | grep minishell'
# assert 'cat | cat | ls\n\n'

# # Expand Variable
# assert 'echo $USER'
# assert 'echo $USER$PATH$TERM'
# assert 'echo "$USER  $PATH   $TERM"'
#################################################