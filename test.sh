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

cat <<EOF | gcc -xc -o exit42 -
int main() { return 42; }
EOF

print_desc() {
	echo -e $BLUE$BOLD"$1"$RESET
}

cleanup() {
	rm -f cmp out a.out print_args hello.txt pwd.txt exit42 infinite_loop no_exec_perm no_read_perm
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
assert 'a.out'
assert 'nosuchfile'

## command not found
assert '""'

# # assert '.' # . is a builtin command in bash
# assert '..'

# ## is a directory
# assert './'
# assert '/'
# assert '/etc'
# assert '/etc/'
# assert '////'

# ## Permission denied
# echo "int main() { }" | gcc -xc -o no_exec_perm -
# chmod -x no_exec_perm
# assert 'no_exec_perm'
# assert './no_exec_perm'
# echo "int main() { }" | gcc -xc -o no_read_perm -
# chmod -r no_read_perm
# assert 'no_read_perm'
# assert './no_read_perm'

# mkdir -p /tmp/a /tmp/b
# echo "int main() { return 1; }" | gcc -xc -o /tmp/a/simple_test -
# echo "int main() { return 2; }" | gcc -xc -o /tmp/b/simple_test -
# print_desc "/tmp/a /tmp/b both with permission"
# assert 'unset PATH\nexport PATH="/tmp/a:/tmp/b"\nsimple_test'
# assert 'unset PATH\nexport PATH="/tmp/b:/tmp/a"\nsimple_test'
# print_desc "/tmp/a /tmp/b both without permission"
# chmod -x /tmp/a/simple_test; chmod -x /tmp/b/simple_test;
# assert 'unset PATH\nexport PATH="/tmp/a:/tmp/b"\nsimple_test'
# assert 'unset PATH\nexport PATH="/tmp/b:/tmp/a"\nsimple_test'
# print_desc "a with permission, b without permission"
# chmod +x /tmp/a/simple_test; chmod -x /tmp/b/simple_test;
# assert 'unset PATH\nexport PATH="/tmp/a:/tmp/b"\nsimple_test'
# assert 'unset PATH\nexport PATH="/tmp/b:/tmp/a"\nsimple_test'
# print_desc "a without permission, b with permission"
# chmod -x /tmp/a/simple_test; chmod +x /tmp/b/simple_test;
# assert 'unset PATH\nexport PATH="/tmp/a:/tmp/b"\nsimple_test'
# assert 'unset PATH\nexport PATH="/tmp/b:/tmp/a"\nsimple_test'

# # Tokenize
# ## unquoted word
print_desc "unquoted"
assert 'ls /'
assert 'echo hello    world     '
assert 'nosuchfile\n\n'

# ## single quote
print_desc "single quote"
assert "./print_args 'hello   world' '42Tokyo'"
assert "echo 'hello   world' '42Tokyo'"
assert "echo '\"hello   world\"' '42Tokyo'"

# ## double quote
print_desc "double quote"
assert './print_args "hello   world" "42Tokyo"'
assert 'echo "hello   world" "42Tokyo"'
assert "echo \"'hello   world'\" \"42Tokyo\""

# ## combination
print_desc "combination"
assert "echo hello'      world'"
assert "echo hello'  world  '\"  42Tokyo  \""

# # Redirect
print_desc "Redirect"
# ## Redirecting output
print_desc "output"
assert 'echo hello >hello.txt' 'hello.txt'
assert 'echo hello >f1>f2>f3' 'f1' 'f2' 'f3'

# ## Redirecting input
print_desc "input"
assert 'cat <Makefile'
echo hello >f1
echo world >f2
echo 42Tokyo >f3
assert 'cat <f1<f2<f3'
rm -f f1 f2 f3
assert 'cat <hoge'

# ## Appending Redirected output
print_desc "append"
assert 'pwd >>pwd.txt' 'pwd.txt'
assert 'pwd >>pwd.txt \n pwd >>pwd.txt' 'pwd.txt'

# ## Here Document
print_desc "Here Document"
assert 'cat <<EOF\nhello\nworld\nEOF\nNOPRINT'
assert 'cat <<EOF<<eof\nhello\nworld\nEOF\neof\nNOPRINT'
assert 'cat <<EOF\nhello\nworld'
assert 'cat <<E"O"F\nhello\nworld\nEOF\nNOPRINT'
# assert 'cat <<EOF   \n$USER\n$NO_SUCH_VAR\n$FOO$BAR\nEOF'
# assert 'cat <<"EOF" \n$USER\n$NO_SUCH_VAR\n$FOO$BAR\nEOF'
# assert 'cat <<EO"F" \n$USER\n$NO_SUCH_VAR\n$FOO$BAR\nEOF'
# export EOF="eof"
# assert 'cat <<$EOF         \neof\n$EOF\nEOF'
# assert 'cat <<"$EOF"       \neof\n$EOF\nEOF'

# # Pipe
print_desc "Pipe"
assert 'cat Makefile | grep minishell'
assert 'cat | cat | ls\n\n'

# # Expand Variable
# assert 'echo $USER'
# assert 'echo $USER$PATH$TERM'
# assert 'echo "$USER  $PATH   $TERM"'

# Special Parameter $?
print_desc "\$?"
assert 'echo $?'
assert 'invalid\necho $?\necho $?'
assert 'exit42\necho $?\necho $?'
assert 'exit42\n\necho $?\necho $?'

# Signal handling
echo "int main() { while (1) ; }" | gcc -xc -o infinite_loop -

## Signal to shell processes
print_desc "SIGTERM to SHELL"
(sleep 0.01; pkill -SIGTERM bash;
 sleep 0.01; pkill -SIGTERM minishell) &
assert './infinite_loop' 2>/dev/null # Redirect stderr to suppress signal terminated message

print_desc "SIGQUIT to SHELL"
(sleep 0.01; pkill -SIGQUIT bash; # SIGQUIT should not kill the shell
 sleep 0.01; pkill -SIGTERM bash;
 sleep 0.01; pkill -SIGQUIT minishell; # SIGQUIT should not kill the shell
 sleep 0.01; pkill -SIGTERM minishell) &
assert './infinite_loop' 2>/dev/null # Redirect stderr to suppress signal terminated message
print_desc "SIGINT to SHELL"
(sleep 0.01; pkill -SIGINT bash; # SIGINT should not kill the shell
 sleep 0.01; pkill -SIGTERM bash;
 sleep 0.01; pkill -SIGINT minishell; # SIGINT should not kill the shell
 sleep 0.01; pkill -SIGTERM minishell) &
assert './infinite_loop' 2>/dev/null # Redirect stderr to suppress signal terminated message
## Signal to child processes
# print_desc "SIGTERM to child process"
# (sleep 0.01; pkill -SIGTERM infinite_loop;
#  sleep 0.01; pkill -SIGTERM infinite_loop) &
# assert './infinite_loop'
# print_desc "SIGINT to child process"
# (sleep 0.01; pkill -SIGINT infinite_loop;
#  sleep 0.01; pkill -SIGINT infinite_loop) &
# assert './infinite_loop'
# print_desc "SIGQUIT to child process"
# (sleep 0.01; pkill -SIGQUIT infinite_loop;
#  sleep 0.01; pkill -SIGQUIT infinite_loop) &
# assert './infinite_loop'
# print_desc "SIGUSR1 to child process"
# (sleep 0.01; pkill -SIGUSR1 infinite_loop;
#  sleep 0.01; pkill -SIGUSR1 infinite_loop) &
# assert './infinite_loop'

# Manual Debug
# $ ./minishell
# $ 
# 1. Ctrl-\ 
# 2. Ctrl-C
# 3. Ctrl-D
#
# $ ./minishell
# $ hogehoge
# 1. Ctrl-\ 
# 2. Ctrl-C
# 3. Ctrl-D
#
# $ ./minishell
# $ cat <<EOF
# >
# 1. Ctrl-\ 
# 2. Ctrl-C
# 3. Ctrl-D
#
# $ ./minishell
# $ cat <<EOF
# > hoge
# > fuga
# 1. Ctrl-\ 
# 2. Ctrl-C
# 3. Ctrl-D

# Builtin
## echo
print_desc "echo"
assert 'echo'
assert 'echo hello'
assert 'echo hello "    " world'
assert 'echo -n'
assert 'echo -n hello'
assert 'echo -n hello world'
assert 'echo hello -n'

## cd
print_desc "cd"
assert 'cd'
assert 'cd .'
assert 'cd ..'
assert 'cd ///'
assert 'cd /tmp'
assert 'cd /tmp/'
assert 'cd /tmp///'
assert 'cd /../../../././.././'
assert 'cd src'
assert 'unset HOME\ncd'
# assert 'cd \n echo $PWD'
# assert 'cd .\n echo $PWD'
# assert 'cd ..\n echo $PWD'
# assert 'cd ///\n echo $PWD'
# assert 'cd /tmp\n echo $PWD'
# assert 'cd /tmp/\n echo $PWD'
# assert 'cd /tmp///\n echo $PWD'
# assert 'cd /../../../././.././\n echo $PWD'
# assert 'cd src\n echo $PWD'
# assert 'unset HOME\ncd \n echo $PWD'

## pwd
print_desc "pwd"
assert 'pwd'
assert 'cd\npwd'
assert 'cd src\npwd'
assert 'cd /etc\npwd'
# assert 'cd . \n pwd \n echo $PWD $OLDPWD'
# assert 'cd .. \n pwd \n echo $PWD $OLDPWD'
# assert 'cd /// \n pwd \n echo $PWD $OLDPWD'
# assert 'cd /tmp/// \n pwd \n echo $PWD $OLDPWD'
# assert 'unset PWD\npwd\ncd /etc\npwd'

## export
print_desc "export"
print_desc "Output of 'export' differs, but it's ok."
assert 'export' # order of variables, default variables differs...
assert 'export | grep nosuch | sort'
assert 'export nosuch\n export | grep nosuch | sort'
assert 'export nosuch=fuga\n export | grep nosuch | sort'
assert 'export nosuch=fuga hoge=nosuch\n export | grep nosuch | sort'
assert 'export [invalid]'
assert 'export [invalid_nosuch]\n export | grep nosuch | sort'
assert 'export [invalid]=nosuch\n export | grep nosuch | sort'
assert 'export [invalid] nosuch hoge=nosuch\n export | grep nosuch | sort'
assert 'export nosuch [invalid] hoge=nosuch\n export | grep nosuch | sort'
assert 'export nosuch hoge=nosuch [invalid]\n export | grep nosuch | sort'
# assert 'export nosuch="nosuch2=hoge"\nexport $nosuch\n export | grep nosuch | sort'

## unset
print_desc "unset"
export hoge fuga=fuga
assert 'unset'
assert 'unset hoge'
assert 'unset fuga'
assert 'unset nosuch'
assert 'unset [invalid]'
assert 'unset hoge fuga'
assert 'unset hoge nosuch fuga'
# assert 'unset fuga \n export | echo $fuga'
# assert 'unset [invalid] fuga \n echo $fuga'

## env
print_desc "env"
print_desc "Output of 'env' differs, but it's ok."
assert 'env' # order of variables, default variables differs...
assert 'env | grep hoge | sort'

## exit
print_desc "exit"
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

cleanup
