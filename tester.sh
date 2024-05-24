##
## EPITECH PROJECT, 2024
## rpg
## File description:
## tester
##

#!/bin/bash



print_error() {
    echo -e "\033[0;31mError: $1\033[0m"
}


print_success() {
    echo -e "\033[0;32mOK - $1\033[0m"
}


print_testname() {
    echo -e "\033[0;33m$1\033[0m"
}


test_invalid_usage() {
    print_testname "Test: Invalid usage of the program (too many arguments)"
    ./my_rpg arg1 arg2
    if [ $? -ne 84 ]; then
        print_error "The program should return exit code 84 for invalid usage"
    else
        print_success "The program returns exit code 84 for invalid usage"
    fi
}


test_missing_environment() {
    print_testname "Test: Missing environment variables"
    env -i ./my_rpg
    if [ $? -ne 84 ]; then
        print_error "The program should return exit code 84 for missing environment variables"
    else
        print_success "The program returns exit code 84 for missing environment variables"
    fi
}


test_correct_usage() {
    print_testname "Test: Correct usage of the program"
    export ENV_VAR=1
    ./my_rpg
    if [ $? -ne 0 ]; then
        print_error "The program should return exit code 0 for correct usage"
    else
        print_success "The program returns exit code 0 for correct usage"
    fi
}


test_wrong_pathfile() {
    print_testname "Test: wrong image paths"
    export ENV_VAR=1
    cd lib && ../my_rpg
    if [ $? -ne 84 ]; then
        print_error "The program should return exit code 84 for wrong paths"
    else
        print_success "The program returns exit code 84 for wrong paths"
    fi
}


test_directory_size() {
    print_testname "Test: Current directory size less than 25MB"
    directory_size=$(du -sm . | cut -f1)
    if [ $directory_size -gt 25 ]; then
        print_error "The current directory size is more than 25MB"
    else
        print_success "The current directory size is less than 25MB"
    fi
}

echo -e "\n\n"
test_invalid_usage

echo -e "\n"
test_missing_environment

echo -e "\n"
test_correct_usage

echo -e "\n"
test_wrong_pathfile

echo -e "\n"
test_directory_size

echo -e "\n\n"
echo "Tests completed."
