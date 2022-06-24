/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 13:47:13 by danimart          #+#    #+#             */
/*   Updated: 2022/06/24 13:17:32 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <limits.h>

# define ARGC_ERR_STR "\e[0;31mError\e[1;30m: \e[0;31mInvalid input\
\e[1;30m.\e[0m\n"
# define ARGC_ERR 1

typedef struct s_philo_info {
	int	amount;
}				t_philo_info;

// philosophers.c
void			print_error(int code);

// input_parser.c
t_philo_info	*parse_arguments(int argc, char **args);

#endif