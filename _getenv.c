#include "holberton.h"

/**
 * _getenv - retrieves env variable that matches input string
 * @input: input string
 * @environ: local environmental variables
 * Return: string of env variable
 */
char *_getenv(char *input, char **environ)
{
	register int i = 0;
	char *tok, *right;

	while (environ[i])
	{
		tok = _strtok(environ[i], "=");
		if (_strcmp(tok, input) == 0)
		{
			right = _strtok(NULL, "=");
			return (right);
		}
		i++;
	}
	return (NULL);
}


/**
 * get_env - finds a copy of the environmental variable
 *
 * @env: list of enviromental variable
 * @str: string to store the variable
 * Return: copy of requested environmental variable
 */
char *get_env(char *str, linked_l *env)
{
	int i_list, len_variable;
	char *var, *tmp_var = NULL;

	i_list = len_variable = 0;
	var = NULL;

	while (env != NULL)
	{
		for (i_list = 0; (env->string)[i_list] == str[i_list]; i_list++)
			;
		if (str[i_list] == '\0' && (env->string)[i_list] == '=')
			break;
		env = env->next;
	}

	len_variable = _strlen(str);

	tmp_var = env->string;
	while ((len_variable + 1) > 0)
	{
		tmp_var++;
		len_variable--;
	}
	var = _strdup(tmp_var);

	return (var);
}
