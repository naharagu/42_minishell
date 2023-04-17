#!/bin/bash

# List of commands to test
commands=(
#nonbuiltin

#builtin
# echo
"echo"
"echo aaa"
"echo -n aaaaaa"
"echo 'Hello, World!' '42tokyo'"
"echo 'Hello, World!'     ' .   42tokyo'"
# "pwd"

# export
"export KEY="hoge fuga""
"export KEY=$USER:/bin"

# # exit command
# 'exit'
# 'exit 42'
# 'exit 99999999999999999999' #numeric argument required
# 'exit hello' #numeric argument required
# 'exit 42Tokyo' #numeric argument required
# 'exit 42 41 40' #too many arguments
# 'exit 42 hello' #too many arguments
# 'exit hello 42' #numeric argument required

# #pipe
"echo 'Hello, World!' > a | cat a"

# Redirect
## Redirecting output
"echo hello >hello.txt 'hello.txt'"
"echo hello >f1>f2>f3 'f1' 'f2' 'f3'"

## Redirecting input
"cat <Makefile"
"echo hello >f1"
"echo world >f2"
"echo 42Tokyo >f3"
'cat <f1<f2<f3'
"rm -f f1 f2 f3"
'cat <hoge'

## Appending Redirected output
"pwd >>pwd.txt 'pwd.txt'"
"pwd >>pwd.txt \n pwd >>pwd.txt 'pwd.txt'"

# # Here Document
# "echo <<EOF\nhello\nworld\nEOF'"
# "echo <<EOF<<eof\nhello\nworld\nEOF\neof\n'"
# "echo <<EOF\nhello\nworld'"
# "echo <<E"O"F\nhello\nworld\nEOF\n'"
# "echo <<$USER\nhello\nworld\n$USER\n'"

# command not found
"commandthatdoesntexist"

# # double quote
'echo "cat main.c | cat > main.c"'
'echo "hello   world" "42Tokyo"'
'echo "'helloworld'" "42Tokyo"'

# single quote
'echo '''
'echo '$USER''
'echo ' ''
'echo '|''
'echo '>''
'echo 'hello   world' '42Tokyo''

# Expand Variable
'echo $USER'
'echo $USER$PATH'
'echo "$USER  $PATH   " | cat -e'
'echo $"aaa"'
'echo "$USER=42"'
'echo'$USER''
'echo '"$USER"''
'echo "'$USER'"'

#review
'/bin/pwd'
'/bin/ls'
'/bin/filethatdoesntexist'
'' #empty
' ' #space
'	' #tab

#yokitaga
"a echo B=b"
)

# Color codes
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No color

compare_output_and_status() {
    test_number=1
    for cmd in "${commands[@]}"; do
        echo "TEST $test_number: $cmd"

        # Run the command in bash and save the output and exit status
        eval $cmd > bash_output.txt
        bash_exit_status=$?

        # Run the command in minishell and save the output and exit status
        echo $cmd | ./minishell > minishell_output.txt 2> /dev/null
        minishell_exit_status=$?

        # Compare the output of bash and minishell
        diff_result=$(diff bash_output.txt minishell_output.txt)
        if [ -z "$diff_result" ]; then
            output_result="${GREEN}Passed${NC}"
        else
            output_result="${RED}Failed${NC}"
        fi

        # Compare the exit status of bash and minishell
        if [ $bash_exit_status -eq $minishell_exit_status ]; then
            status_result="${GREEN}Passed${NC}"
        else
            status_result="${RED}Failed${NC}"
        fi

        # Print test results
        echo "Output comparison: $output_result"
        if [ "$output_result" == "${RED}Failed${NC}" ]; then
            echo "Differences:"
            echo "$diff_result"
        fi
        echo "Exit status comparison: $status_result"
        if [ "$status_result" == "${RED}Failed${NC}" ]; then
            echo "Bash exit status: $bash_exit_status"
            echo "Minishell exit status: $minishell_exit_status"
        fi
        echo "---------------------------------------"

        test_number=$((test_number + 1))
    done

    # Clean up temporary files
    rm bash_output.txt minishell_output.txt
}

# Run the comparison
compare_output_and_status
