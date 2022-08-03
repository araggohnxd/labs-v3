#include "monitoring.h"

t_protocol_type	get_protocol_type(char *str)
{
	if (strcmp(str, "HTTP") == 0)
		return (HTTP);
	if (strcmp(str, "PING") == 0)
		return (PING);
	if (strcmp(str, "DNS") == 0)
		return (DNS);
	return (ERROR);
}

size_t	get_split_size(char **split)
{
	size_t size = 0;

	while (split[size])
		++size;
	return (size);
}

t_bool	is_numeric_str(char *str)
{
	for (size_t index = 0; str[index]; index++)
		if (!ft_isdigit(str[index]))
			return (FALSE);
	return (TRUE);
}

void nullify_newline(char *str)
{
	size_t index;

	for(index = 0; str[index] != '\n'; index++);
	str[index] = '\0';
}
