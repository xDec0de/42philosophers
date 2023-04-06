/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:31:15 by danimart          #+#    #+#             */
/*   Updated: 2023/04/06 17:55:10 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	print_error(char *err, int ret)
{
	printf("%s", err);
	return (ret);
}

int	main(int argc, char **argv)
{
	t_philo_info	*info;

	info = parse_arguments(argc, argv);
	if (info == NULL)
		return (1);
	return (0);
}
