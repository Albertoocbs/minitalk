/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_server.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoutumur <aoutumur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:32:02 by aoutumur          #+#    #+#             */
/*   Updated: 2025/02/20 15:33:49 by aoutumur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ft_printf/ft_printf.h"

static void	ft_signal_handler(int signal)
{
	static int 	bit_received; //compteur bits recus
	static int 	i; //ou stcoker les bits recus

	i = i << 1; // decale a gauche toutes les bits une fois pour faire la place au nouveau bit, gere les 0.
	if (signal == SIGUSR1)
		i = i | 1; // place le bit recu a la fin
	bit_received++;
	if (bit_received == 8)
	{
		if (i == '\0')
			write(1, "\n", 1);
		else
			write(1, &i, 1); // i contient tous les bits qui correspond a la valeur ASCII du caractere
		bit_received = 0;
		i = 0;
	}
}

int	main(void)
{
	int	pid;
	struct sigaction sa;

	sa.sa_handler = ft_signal_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);

	pid = getpid();
	ft_printf("Server PID: %d\n", pid);
	while (1)
		pause();
	return (0);
}
