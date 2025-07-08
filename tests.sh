#!/bin/bash
# Testes automáticos para o builtin echo do minishell
# Uso: ./test_echo.sh /caminho/para/minishell

MINISHELL="$1"

if [ -z "$MINISHELL" ]; then
    echo "Uso: $0 /caminho/para/minishell"
    exit 1
fi

run_compare_test() {
    CMD="$1"
    # Run in bash
    EXPECTED=$(bash -c "$CMD")
    # Run in minishell, strip prompt and empty lines
    OUTPUT=$(echo "$CMD" | $MINISHELL 2>/dev/null | awk 'NR>1' | sed 's/gongabriela@LAPTOP-D1TGFKAQ:~\/minishell\$ $//' | awk 'NF')
    if [ "$OUTPUT" = "$EXPECTED" ]; then
        echo "[OK] $CMD"
    else
        echo "[FAIL] $CMD"
        echo "  Bash:     '$EXPECTED'"
        echo "  Minishell:'$OUTPUT'"
    fi
}

# Testes básicos
echo "Iniciando testes do echo..."
run_compare_test "echo"
run_compare_test "echo oi"
run_compare_test "echo oi tudo bem"
run_compare_test "echo 'oi tudo' bem"
run_compare_test 'echo "oi tudo" bem'
run_compare_test "echo ''"
run_compare_test "echo -n"
run_compare_test "echo -n oi"
run_compare_test "echo -n oi tudo"
run_compare_test "echo -n 'oi tudo' bem"
run_compare_test "echo -n ''"

# Edge cases
echo "Testes edge cases:"
run_compare_test "echo -n -n oi"
run_compare_test "echo -n -n -n oi"
run_compare_test "echo -n -nn oi"
run_compare_test "echo -n -n -nn oi"
run_compare_test "echo -n -n -n"
run_compare_test "echo -n -n -n"
run_compare_test "echo -n -n -n -n"
run_compare_test "echo -n -n -n -nnn oi"
run_compare_test "echo -n -n -n -n -n -n -n -n -n oi"
run_compare_test "echo -n -n -n -n -n -n -n -n -n -n oi"
run_compare_test "echo -n -n -n -n -n -n -n -n -n -n -n oi"
run_compare_test "echo -n -n -n -n -n -n -n -n -n -n -n -n oi"
run_compare_test "echo -n -n -n -n -n -n -n -n -n -n -n -n -n oi"
run_compare_test "echo -n -n -n -n -n -n -n -n -n -n -n -n -n -n oi"
run_compare_test "echo -n -n -n -n -n -n -n -n -n -n -n -n -n -n -n oi"
run_compare_test "echo -n -n -n -n -n -n -n -n -n -n -n -n -n -n -n -n oi"
run_compare_test "echo -n -n -n -n -n -n -n -n -n -n -n -n -n -n -n -n -n oi"

# Testes com espaços e aspas
run_compare_test "echo '   '"
run_compare_test "echo -n '   '"
run_compare_test "echo ''"
run_compare_test "echo -n ''"
run_compare_test "echo '"
run_compare_test "echo -n '"

# Testes de múltiplos espaços
run_compare_test "echo    oi    tudo   bem   "
run_compare_test "echo -n    oi    tudo   bem   "

# Testes de escape (se implementado)
# run_compare_test "echo oi\\n"
# run_compare_test "echo -n oi\\n"

echo "Testes finalizados."
