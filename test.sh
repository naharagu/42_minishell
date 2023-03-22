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

# Generate Executable
# -xc このオプションに続く入力ファイルの言語をcであると明示的に指定します
# -o 名前をつける
cat <<EOF | gcc -xc -o a.out -
#include <stdio.h>
int main() { printf("hello from a.out\n"); }
EOF

cat <<EOF | gcc -xc -o print_args -
#include <stdio.h>
int main(int argc, char *argv[]) {
	for (int i = 0; argv[i]; i++)
		printf("argv[%d] = %s\n", i, argv[i]);
}
EOF

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
	for arg in "$@"
	do
		mv "$arg" "$arg"".cmp"
	done

	# minishellの出力をoutに保存
	echo -n -e "$COMMAND" | ./minishell >out 2>&-
	# minishellのexit statusをactualに代入
	actual=$?
	for arg in "$@"
	do
		mv "$arg" "$arg"".out"
	done

	# bashとminishellの出力を比較
	diff cmp out >/dev/null && echo -e -n "  diff $OK" || echo -e -n "  diff $NG"

	# bashとminishellのexit statusを比較
	if [ "$actual" = "$expected" ]; then
		echo -e -n "  status $OK"
	else
		echo -e -n "  status $NG, expected $expected but got $actual"
	fi
	for arg in "$@"
	do
		echo -n "  [$arg] "
		diff "$arg"".cmp" "$arg"".out" >/dev/null && echo -e -n "$OK" || echo -e -n "$NG"
		rm -f "$arg"".cmp" "$arg"".out"
	done
	echo
}

# # Empty line (EOF)
assert ''

assert '/bin/pwd'
assert '/bin/ls'
assert '/bin/echo'

# # Search command path without args
assert 'pwd'
assert 'echo'
assert 'ls'
assert './a.out'

# ## no such command
# assert 'a.out'
# assert 'nosuchfile'

## exit command
assert 'exit'
assert 'exit 42'
assert 'exit 256'
assert 'exit 999'
assert 'exit 99999999999999999999'
assert 'exit hello'
assert 'exit 42Tokyo'
assert 'exit 42 41 40'
assert 'exit 42 hello'
assert 'exit hello 42'

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

cleanup
