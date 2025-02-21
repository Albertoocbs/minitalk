/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_server.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoutumur <aoutumur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:32:02 by aoutumur          #+#    #+#             */
/*   Updated: 2025/02/21 08:46:35 by aoutumur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ft_printf/ft_printf.h"

/*
Reçoi le signal, le traite et garde l'info entre appels jusqua arriver a 8 bits
- bit_received = compteur bits recus
- i = ou stcoker les bits recus
- i = i << 1; -> decale a gauche tous les bits 1 fois.Fait la place au nouveaux
- i = i | 1; place le bit recu a la fin
*/
static void	ft_signal_handler(int signal)
{
	static int	bit_received;
	static int	i;

	i = i << 1;
	if (signal == SIGUSR1)
		i = i | 1;
	bit_received++;
	if (bit_received == 8)
	{
		if (i == '\0')
			write(1, "\n", 1);
		else
			write(1, &i, 1);
		bit_received = 0;
		i = 0;
	}
}

/* Print le pid du serveur. Recoi le signal et appel la fonction handler pour
obtenir chaque bit a chaque appel et chaque caractere une fois 8 bits recu
jusqua avoir recu toute la chaine passe en argument dans ./client */
int	main(void)
{
	int					pid;
	struct sigaction	sa;

	sa.sa_handler = ft_signal_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	pid = getpid();
	ft_printf("Server PID: %d\n", pid);
	while (1)
		pause();
	return (0);
}
