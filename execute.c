#include "shell.h"

/**
 * _excute - function that excute commands
 * that's not part of builtins
 *
 * @command: command to be executed
 * Return: Nothing(void)
 */
void _excute(command_t *command)
{
	int pid, status, err;

	pid = fork();
	if (pid < 0)
	{
		perror((char *)globalistNodeates(GET_SHELL_NAME, NULL));
		statusMgt(UPDATE_STATUS, 1);
		return;
	}
	if (!pid)
	{
		execve(command->name, command->arguments, __environ);
		err = errno;
		if (errno == EACCES)
		{
			myFprint(2, "%s: %d: %s: Permission denied\n",
					 (char *)globalistNodeates(GET_SHELL_NAME, NULL),
					 *((int *)globalistNodeates(GET_LINE_NUMBER, NULL)),
					 command->name);
			err = 126;
		}
		else
			perror(globalistNodeates(GET_SHELL_NAME, NULL));
		_free_command(command);
		free(globalistNodeates(GET_LINE, NULL));
		envMgt(CLEAR_ENV, NULL, NULL);
		_exit(err);
	}
	else
	{
		waitpid(pid, &status, 0);
		statusMgt(UPDATE_STATUS, WEXITSTATUS(status));
	}
}
