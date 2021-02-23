#include "holberton.h"

/**
 * shell - simple shell
 *
 * @argv: array of argument from input type
 *
 * Return: void
 */
void shell(char **argv)
{
	config build;

	build.env = generateLinkedList(environ);
	build.envList = NULL;
	build.args = NULL;
	build.buffer = NULL;
	build.path = _getenv("PATH", environ);
	build.fullPath = NULL;
	build.lineCounter = 0;
	build.errorStatus = 0;
	build.shellName = argv[0];

	for (;;)
	{
		signal(SIGINT, sigintHandler);

		if (isatty(STDIN_FILENO))
			displayPrompt();

		build.lineCounter++;

		checkAndGetLine(&build);

		if (splitString(&build) == false)
			continue;

		if (findBuiltIns(&build) == true)
			continue;

		checkPath(&build);

		forkAndExecute(&build);
	}
}

/**
 * checkAndGetLine - check stdin and retrieves next line; handles
 * prompt display
 * @build: input build
 */
void checkAndGetLine(config *build)
{
	int len = 0;
	size_t bufferSize = 0;

	build->args = NULL;
	build->envList = NULL;

	len = getline(&build->buffer, &bufferSize, stdin);
	if (len == EOF)
	{
		freeMembers(build);

		if (build->errorStatus)
			exit(build->errorStatus);

		exit(EXIT_SUCCESS);
	}

	if (_strchr(build->buffer, '\n') || _strchr(build->buffer, ' '))
		insertNullByte(build->buffer, len - 1);

	stripComments(build->buffer);
}

/**
 * stripComments - remove comments from input string
 * @str: input string
 * Return: length of remaining string
 */
void stripComments(char *str)
{
	register int i = 0;
	_Bool notFirst = false;

	while (str[i])
	{
		if (i == 0 && str[i] == '#')
		{
			insertNullByte(str, i);
			return;
		}
		if (notFirst)
		{
			if (str[i] == '#' && str[i - 1] == ' ')
			{
				insertNullByte(str, i);
				return;
			}
		}
		i++;
		notFirst = true;
	}
}

/**
 * forkAndExecute - fork current build and execute processes
 * @build: input build
 */
void forkAndExecute(config *build)
{
	int status = 0;
	pid_t f1 = fork();

	convertLLtoArr(build);
	if (f1 == -1)
		perror("error\n"), freeMembers(build), freeArgs(build->envList), exit(1);

	if (f1 == 0)
	{
		if (execve(build->fullPath, build->args, build->envList) == -1)
		{
			errorHandler(build), freeMembers(build), freeArgs(build->envList);
			if (errno == ENOENT)
				exit(127);
			if (errno == EACCES)
				exit(126);
		}
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
			build->errorStatus = WEXITSTATUS(status);
		freeArgsAndBuffer(build), freeArgs(build->envList);
	}
}

/**
 * convertLLtoArr - convert linked list to array
 * @build: input build
 */
void convertLLtoArr(config *build)
{
	int i = 0;
	size_t count = 0;
	char **envList = NULL;
	linked_l *tmp = NULL;

	count = list_len(build->env);

	envList = (char **) malloc(sizeof(char *) * (count + 1));
	if (!envList)
	{
		perror("Malloc failed\n");
		exit(1);
	}

	for (tmp = build->env; tmp; tmp = tmp->next, i++)
		envList[i] = _strdup(tmp->string);

	envList[i] = NULL;

	build->envList = envList;
}
