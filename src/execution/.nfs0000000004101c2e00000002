/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 10:04:39 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/07/09 10:04:39 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


	/*printf("PRE_EXECUTION COMPLETED!---------------------------\n");
	printf("Total commands: %d\n", shell->cmd_total);
	if (shell->pipe_fds[0] != 0)
		printf("Pipe created: %d\n", shell->pipe_fds[0][0]);
	if (shell->pids[0] != 0 && shell->pids[1] != 0)
		printf("PIDs created: %d\n & %d\n", shell->pids[0], shell->pids[1]);*/


void	execution(t_exec *tree, t_shell *shell)
{
	if (tree->type == CMD)
	{
		if (is_builtin(tree->cmd))
			execute_builtin(shell, tree, tree->cmd);
		else
			execute_external_cmd(tree, shell);
	}
}
/*
cat Makefile | grep "NAME" | sorte > outfile

OP: >
  OP: |
    OP: |
      CMD: cat Makefile
      CMD: grep "NAME"
    CMD: sort
  CMD: outfile

chegou no > (operador vem sempre antes do arquivo!)
	//exec tree->left (recursivo)
	//redir fd tree->right (quando tiver voltando a recursao, ele vai dar o redir. ta certo? nao tem que ser antes de executar o comando?)

//exec tree->left (|)
	//criar pipe
	//se exec->left for OPRT, executar recursivo
	//exec comando right na volta da recursao (?) (sort)

// exec tree->left (|)
	//criar pipe
	//se nao, exec cmd left pq o o left e NULL
	//exec comando right

//como conectar todos os fds???? e redirecionar tudo pros pipes e pro >? eu quero um codigo que seja universal, funcione em todas as linhas de comando, e nao so essa em especifico
*/

/*
pre_execution()
	//verificar se tem heredoc, se sim, executa-los
	//fazer calculo: pipes = cmds - 1;
	//criar todos os pipes -> fd[][] e pipe()
	//verificar todos os redirs, guardar info dos fds stdin e stdout no node de cada cmd

execution()
	//cria um pid_t pid[(numero de comandos)];
	//atravessa a arvore, e a partir das folhas, cada vez que encontra um comando, faz um fork(), e chama a funcao exec_cmd
	//exec_cmd()
		//redireciona stdin e stdout conforme info pegada da funcao pre_execution
		//se for builtin, executa fora de um execve
		//se for externo, executa num execve
	//waitpid em formato while()
*/

/* ls | wc -l

minishell()
while (1)
{
	if (get_input(shell))
		shell->tokens = tokenize(shell->input);
	shell->cmd_total = get_cmd_total(shell->tokens);
	create_ast(shell, shell->tokens);
	pre_execution(shell->tree, shell);
	execution(shell->tree, shell);
	wait_pids();
	ft_free_shell(shell);
}
---------------------------------
pre_execution()
ver total de comandos para criar o numero de pipes
criar array 2d para guardar o fd de todos os pipes
	int pipes[cmd_total - 1][2]; //NMAO PQ PODE SER 1 CMD SO
criar os pipes e guardar os fds no array
guardar info de redirecionamento de cada comando no no da arvore
	ver se funcao funciona bem com mais de 2 pipes
criar array de pids para guardar os pids de cada comando e usar no waitpid depois
	int pids[cmd_total]; PODE SER 1 CMD SO E SER BUILTIN!
----------------------------------
execution()
if (!tree)
	return ;

if (tree->type == PIPE)
	execution(tree->left);
	execution(tree->right);
if (tree->type == CMD)
	exec_cmd;
----------------------------------
exec_cmd() - fazer como no pipex
pid = fork()
if (pid == 0)
	//pegar path
	//dup2 e close pipes
	if (is builtin)
		exec_builtin()
	else
		//execve(path, cmd, shell->envp) //precisa mandar a envp?

-----------------------------------------
o que falta:
	fechar pipes
	entender como passar os indices de pipe_fds e pids corretamente
*/

/*void	debug_pipes_pids(t_shell *shell)
{
	int	i;

	printf("cmd total: %d\n", shell->cmd_total);
	i = 0;
	while(i < shell->cmd_total - 1)
	{
		printf("pipe %d - fd[0] = %d; fd[1] = %d\n", i + 1, shell->pipe_fds[i][0], shell->pipe_fds[i][1]);
		i++;
	}
}

void	debug_ast(t_exec *tree, t_shell *shell)
{
	if (!tree)
		return ;
	if (tree)
	{
		debug_ast(tree->left, shell);
		debug_ast(tree->right, shell);
	}
	printf("type: %d\n", tree->type);
	if (tree->oprt)
		printf("oprt: %s\n", tree->oprt);
	if (tree->cmd)
		printf("cmd: %s\n", tree->cmd[0]);
	printf("STDIN: %d\n", tree->stdin);
	printf("STDOUT: %d\n", tree->stdout);
}*/