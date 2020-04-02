#include "lexer.h"

int		handle_exit_status(int exit_status)
{
	static int	last_exit_status;

	if (exit_status == GET_EXIT_STATUS)
		return (last_exit_status);
	last_exit_status = exit_status;
	return (last_exit_status);
}
