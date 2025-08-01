/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniema3 <daniema3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 18:29:55 by daniema3          #+#    #+#             */
/*   Updated: 2025/08/01 21:47:43 by daniema3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	build_philosophers(t_philo_info *info)
{
	int	id;

	id = 1;
	while (id <= info->philo_n)
	{
		info->philo_lst[id - 1] = init_philo(info, (unsigned int) id);
		id++;
	}
}

int	main(int argc, char **argv)
{
	t_philo_info	*info;

	info = parse_arguments(argc, argv);
	if (info == NULL)
		return (EXIT_FAILURE);
	build_philosophers(info);
	free_info(info);
	return (EXIT_SUCCESS);
}
