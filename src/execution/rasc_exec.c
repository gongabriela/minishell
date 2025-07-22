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

/*

	get_redir_info_pipes(shell, tree, shell->pipe_fds, shell->cmd_total);
	shell->pids = malloc(sizeof(pid_t *) * shell->cmd_total);
	if (!shell->pids)
		perror("malloc failed");
	shell->pid_index = -1;*/
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

int	calculate_cmd_total(t_exec *tree, int cmds)
{
	t_exec *temp;

	temp = tree;
	if (!temp)
		return ;
	while(temp)
	{
		if (tree->type == CMD)
			cmds = cmds + 1;
		calculate_cmd_total(temp->left, cmds);
		calculate_cmd_total(temp->right, cmds);
	}
	return (cmds);
}

void	create_pipes_pids(t_shell *shell, t_exec *tree, int	**pids, int ** pipe_fds)
{
	shell->cmd_total = calculate_cmd_total(tree, 0);
	*pids = malloc(sizeof(pid_t *) * shell->cmd_total);
	if (!(*pids))
		perror("malloc failed");
	*pipe_fds = malloc(sizeof(int *) * (shell->cmd_total - 1));
	if (!(*pipe_fds))
		perror("malloc failed");
	create_pipes(tree, pipe_fds, shell->cmd_total);
}

void	create_pipes(t_exec **tree, int *pipe_fds, int index)
{
	if (!tree)
		return ;

	while (*tree)
	{
		if (tree->type == PIPE)
		{
			pipe(pipe_fds[index]);
			if (pipe(pipe_fds[index]) > 0)
				perror("pipe failed");
			index = index - 1;
		}
		get_redirs_info((*tree)->left, pipe_fds, index);
		get_redirs_info((*tree)->right, pipe_fds, index);
	}
}

// guardar info do stdins e stdouts nos nós dos comandos!!!
void	get_redirs_info(t_exec *tree, int *pipe_fds, int cmds)
{
	while (tree)
	{
		if (tree->type == REDIR_IN)


		else if (tree->type == REDIR_OUT)

		else if (tree->type == APPEND)

		else if (tree->type == PIPE)
	}

}

void	execution(t_exec *tree, t_shell *shell, int cmds)
{
	pid_t	*pids;
	int		**pipe_fds;

	execute_heredocs(tree, shell);
	create_pipes_pids(shell, tree, &pids, &pipe_fds);
	get_redirs_info(&tree, pipe_fds, shell->cmd_total);
	get_cmd_path(tree, shell);
	exec_commands(tree, shell, shell->cmd_total);
	for (int i = 0; i < shell->pid_index; i++) {
		waitpid(shell->pids[i], &shell->exit_code, 0);
	}
}

void	exec_commands(t_exec *tree, t_shell *shell, int cmd_index)
{
	pid_t	*pid;

	if (!tree)
		return ;
	if (tree->type == REDIR_IN || tree->type == REDIR_OUT || tree->type == HEREDOC)
	{
		exec_commands(tree->left, shell, cmd_index);
		exec_commands(tree->right, shell, cmd_index);
	}
	else if (tree->type == PIPE)
	{
		create_pipe(pipe_fds[cmd_index]);
		exec_commands(tree->left, shell, cmd_index);
		exec_commands(tree->right, shell, cmd_index + 1);
	}
	else if (tree->type == CMD)
	{
		pid = fork();
		if (pid < 0)
			return ; //melhorar error handling
		if (pid == 0)
		{
			perform_redirs();
			execve();
		}
		else
			pids[] = pid; //ver index do pid para fica rdireito
	}
}

