#include "monitoring.h"

int	main(void)
{
	int fd;
	t_list *parsed_configs;

	fd = open("monitoring.db", O_RDONLY);
	if (fd < 0)
	{
		fprintf(stderr, "monitoring: monitoring.db: %s\n", strerror(errno));
		return (EXIT_FAILURE);
	}
	parsed_configs = parse_config_file(fd);
	if (parsed_configs)
		ft_lstclear(&parsed_configs, free_protocol_node);
	close(fd);
	return (0);
}
