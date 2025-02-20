# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aoutumur <aoutumur@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/19 11:59:17 by aoutumur          #+#    #+#              #
#    Updated: 2025/02/20 14:06:53 by aoutumur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Fichiers sources
SRCS = ft_server.c ft_client.c
OBJS = $(SRCS:.c=.o)

# Compilation
CC = gcc
CFLAGS = -Wall -Werror -Wextra -Ift_printf

# Noms des exécutables
NAME_SERVER = server
NAME_CLIENT = client

# Dossier de ft_printf
FT_PRINTF_DIR = ft_printf
FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a

# Compilation des binaires
all: $(FT_PRINTF) $(NAME_SERVER) $(NAME_CLIENT)

# Compilation de ft_printf qui contient aussi libft
$(FT_PRINTF):
	make -C $(FT_PRINTF_DIR)

# Compilation du serveur
$(NAME_SERVER): ft_server.o $(FT_PRINTF)
	$(CC) $(CFLAGS) ft_server.o -o $(NAME_SERVER) -L$(FT_PRINTF_DIR) -lftprintf

server.o: server.c
	$(CC) $(CFLAGS) -c ft_server.c -o ft_server.o

# Compilation du client
$(NAME_CLIENT): ft_client.o $(FT_PRINTF)
	$(CC) $(CFLAGS) ft_client.o -o $(NAME_CLIENT) -L$(FT_PRINTF_DIR) -lftprintf

client.o: client.c
	$(CC) $(CFLAGS) -c ft_client.c -o ft_client.o

# Compilation des fichiers .c en .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage des fichiers compilés
clean:
	rm -f $(OBJS)
	make -C $(FT_PRINTF_DIR) clean

# Nettoyage total
fclean: clean
	rm -f $(NAME_SERVER) $(NAME_CLIENT) $(FT_PRINTF)
	make -C $(FT_PRINTF_DIR) fclean

# Recompilation complète
re: fclean all

# Règles phony
.PHONY: all clean fclean re

