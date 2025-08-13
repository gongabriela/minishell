#!/bin/bash
# Automated test script for minishell
# Compares output of ./minishell and bash, runs valgrind, and logs results

MINISHELL=./minishell
BASH=/bin/bash
VALGRIND_FLAGS="--leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp"
LOGFILE="test_results.log"
VALGRIND_LOG="valgrind.log"

# Color codes
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# List of test commands
TESTS=(
    # cd tests
    "cd"
    "cd ."
    "cd."
    "unset HOME; cd"
    "cd src a"
    "cd ../../../.."
    "cd /usr/bin"
    "cd  ls"
    "cd nonexistent"
    "cd \"\""
    "cd .."
    "mkdir test; cd test; mkdir test2; cd test2; rm -rf ../../test; cd"

    # export/unset/path/ls tests
    "export a=-l ; ls $a"
    "unset PATH; ls"

    # echo tests
    "echo"
    "echo -n"
    "echo -nnnnn"
    "echo -nnnnnnnnnnnnnnnnnnnnn -n -n oi"
    "echo -nnnnnnnnnnnnnnnnnnnnn -nz -n oi"
    "echo -nz oi"
    "echo This is a test"
    "echo -n This is a test"
    "echo -nnnn This is a test"
    "echo This is a test -nnnn"
    "echo hello > 'FILENAME WITH SPACE'"
    "echo 42' '42"
    "echo hello\"\"world"
    "echo -n “12””34”"
    "echo hi |  \"|”\""

    # env tests
    "env"
    "env PATH"
    "env -i ./minishell; env"

    # exit tests
    "exit"
    "exit 300"
    "exit -300"
    "exit +300"
    "exit 2 3"
    "exit abc"
    "exit 99999999999999999999999"
    "exit 999999999999999999999999999"

    # export tests
    "export"
    "export ="
    "export _a"
    "export_"
    "export n_value"
    "export TEST=kaija 12 TEST2=papaija"
    "export = a=2 b='4' c=\"10\""
    "export test=\"   abc\""
    "export test=\"ls -l\"; $test"
    "export test=\"o hello\" ; ech$testexport test=\"| wc \" ; ls $test"
    "export ABC=$USER"
    "export test=\"a  bc        def\" ; echo $test"
    "export test; export test=hello; echo $test"
    "export test=\"a        b         c\""
    "export ZZ\"Y=aaa\"bb"
    "export USER=bubu LAST='quote'"
    "export WWW=\"     -aaa |  \""
    "export te$st=lala"
    "export $lalal=hahhaa"
    "export user=dq\"$USER\""
    "export user=mq$\"U\"S\"E\"R"
    "export us$er=blabla"
    "export=zzzzzz"
    "export fdgsdfhb="
    "export HELLO=123"
    "export HELLO=\"beautiful world\""
    "export a="
    "export=a"
    "export a"

    # unset tests
    "unset nonexistentvariable"
    "unset HOME"
    "unset"
    "unset weird@%chars"
    "unset -n HOME"
    "unset EMA\"IL\""
    "export a ; unset a"

    # env | sort | grep -v SHLVL | grep -v ^_
    "env | sort | grep -v SHLVL | grep -v ^_"

    # PWD and cd tests
    "echo \"$PWD” and cd $PWD in a different folder\""
    "pwd"
    "PWD"
    "pwd args"
    "$PWD numa pasta diferente"
)

# Clean up old logs
rm -f "$LOGFILE" "$VALGRIND_LOG" outfile

echo "Starting tests..." | tee -a "$LOGFILE"

for TEST in "${TESTS[@]}"; do
    echo "\n===== TEST: $TEST =====" | tee -a "$LOGFILE"

    # Run in minishell
    echo "$TEST" | $MINISHELL > minishell_out.txt 2> minishell_err.txt
    # Run in bash
    echo "$TEST" | $BASH > bash_out.txt 2> bash_err.txt

    # Compare outputs
    diff minishell_out.txt bash_out.txt > diff_out.txt
    diff minishell_err.txt bash_err.txt > diff_err.txt

    if [ -s diff_out.txt ] || [ -s diff_err.txt ]; then
        echo -e "${RED}KO${NC} $TEST" | tee -a "$LOGFILE"
        cat diff_out.txt diff_err.txt | tee -a "$LOGFILE"
    else
        echo -e "${GREEN}OK${NC} $TEST" | tee -a "$LOGFILE"
    fi

    # Run valgrind (ignore readline leaks)
    echo "$TEST" | valgrind $VALGRIND_FLAGS $MINISHELL > /dev/null 2>> "$VALGRIND_LOG"
    echo "Valgrind run complete." | tee -a "$LOGFILE"
done

echo "\nAll tests complete. See $LOGFILE and $VALGRIND_LOG for details."