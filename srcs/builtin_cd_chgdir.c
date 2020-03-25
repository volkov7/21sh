#include "lexer.h"

char	*canonical_form(char *cwd, char *argpath)
{
	char	*newpath;

	newpath = ft_strnew(ft_strlen(cwd) + ft_strlen(argpath));
	if (newpath == NULL)
		return (NULL);
	if (argpath[0] == '/')
		newpath[0] = '/';
	else
		ft_strcpy(newpath, cwd);
	create_newpath(&newpath, argpath);
	return (newpath);
}

int		update_env_var(char **cwd, char **newpath, t_envlist **envlst)
{
	if (*cwd == NULL)
		return (shell_err("cd: failed to allocate enough memory\n"));
	if ((set_env(envlst, "OLDPWD", *cwd) == FUNC_ERROR)
	|| (set_env(envlst, "PWD", *newpath) == FUNC_ERROR))
	{
		ft_strdel(cwd);
		ft_strdel(newpath);
		return (shell_err("cd: failed to allocate enough memory\n"));
	}
	ft_strdel(cwd);
	ft_strdel(newpath);
	return (FUNC_SUCCESS);
}

int		change_dir(char *argpath, int opt, t_envlist **envlst)
{
	char	*newpath;
	char	*cwd;

	newpath = NULL;
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (cd_error(NULL, argpath, NULL, NULL));
	if (opt & CD_OPT_L)
		newpath = canonical_form(cwd, argpath);
	if (newpath == NULL && chdir(argpath) == -1)
		return (cd_error(argpath, argpath, &newpath, &cwd));
	else if (newpath != NULL && chdir(newpath) == -1)
		return (cd_error(newpath, argpath, &newpath, &cwd));
	if (opt & CD_OPT_PRINT)
		ft_putendl(argpath);
	if (newpath == NULL)
		newpath = getcwd(NULL, 0);
	if (update_env_var(&cwd, &newpath, envlst) == FUNC_ERROR)
		return (FUNC_ERROR);
	return (FUNC_SUCCESS);	
}
