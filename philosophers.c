/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:31:15 by danimart          #+#    #+#             */
/*   Updated: 2023/09/30 18:21:28 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/philosophers.h"

void	exit_error(char *err, t_philo_info *info)
{
	printf("%s", err);
	if (info != NULL)
		free(info);
	exit(1);
}

void	leaks(void)
{
	system("leaks philo | grep 'leaks for' | awk '$1 == \"Process\" {leaks = $3} END {printf(\"\e[0;31mLeaks\e[1;30m: \e[0;33m%d\e[0m\\n\"), leaks}'");
}

int	watcher_routine(t_philo_info *info)
{
	int		id;
	int		stop;
	t_philo	philo;

	id = 0;
	stop = 1;
	while (id < info->amount && stop == 1)
	{
		philo = info->philo_lst[id];
		if (philo.state == DEAD)
			stop = 0;
	}
	return (stop);
}

int	main(int argc, char **argv)
{
	t_philo_info	*info;

	atexit(leaks);
	info = parse_arguments(argc, argv);
	if (info == NULL)
		return (1);
	info = build_philosophers(info);
	while (watcher_routine(info))
		usleep(1000);
	free(info);
	return (0);
}
