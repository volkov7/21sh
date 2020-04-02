#include "lexer.h"

char	*get_login(t_ast *node, size_t i)
{
	size_t	login_len;

	i++;
	login_len = 0;
	while (node->str[i] != '\0' && node->str[i] != '/')
	{
		i++;
		login_len++;
	}
	if (login_len == 0)
		return (ft_strnew(0));
	return (ft_strsub(node->str, i - login_len, login_len));
}

int		get_user_home_path(char *login, char **home_path, t_envlist *envlst)
{
	struct passwd	*user_info;

	if (login[0] == '\0')
	{
		*home_path = get_env_value("HOME", envlst);
		if (*home_path == NULL)
			return (shell_err(E_HOME_NOT_SET, NULL, EXIT_FAILURE));
	}
	else
	{
		user_info = getpwnam(login);
		if (user_info == NULL)
			return (shell_err(E_NO_SUCH_USRDIR, login, EXIT_FAILURE));
		*home_path = user_info->pw_dir;
	}
	return (FUNC_SUCCESS);
}

int		tilde_expansion(t_ast *node, size_t *i, t_envlist *envlst)
{
	char	*login;
	char	*home_path;
	int		ret;

	home_path = NULL;
	if (node->type == WORD && *i == 0)
	{
		if ((login = get_login(node, *i)) == NULL)
			return (shell_err(E_ALLOC_MEMORY, NULL, EXIT_FAILURE));
		if (get_user_home_path(login, &home_path, envlst) == FUNC_ERROR)
		{
			ft_strdel(&login);
			return (FUNC_ERROR);
		}
		ret = replace_value(&node->str, home_path, *i, ft_strlen(login) + 1);
		ft_strdel(&login);
		return (ret);
	}
	else
		(*i)++;
	return (FUNC_SUCCESS);
}
