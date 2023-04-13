#!/bin/bash

# List of commands to test
commands=(
#nonbuiltin
"ls"
#builtin
"echo 'Hello, World!'"
"pwd"
#pipe
"echo 'Hello, World!' > a | cat a"
)

# Color codes
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No color

# Function to run commands in minishell and bash, then compare the output and exit status
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
