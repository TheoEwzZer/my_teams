##
## EPITECH PROJECT, 2024
## myteams
## File description:
## Makefile
##

NAME_SERVER	=	myteams_server
NAME_CLIENT	=	myteams_cli

WARN1	= 	-W -Wall -Wextra -pedantic -Wformat-nonliteral \
			-Wundef -Wwrite-strings -Wcast-align \
			-Wstrict-overflow=5 -Wdeclaration-after-statement -Wvla \
			-Wpointer-arith -Winit-self -Wmissing-include-dirs \
			-Wdate-time -Wduplicated-branches -Wnull-dereference \
			-Wstack-usage=1024 -Winline -Wunsafe-loop-optimizations \
			-Wvla-larger-than=65536 -Wjump-misses-init \
			-Wlogical-not-parentheses -Wunused-result \
			-Wformat-security -Wformat-overflow=2 -Wdangling-else \
			-Wmissing-braces -Wtype-limits -Wshift-overflow=1 \
			-Wmissing-field-initializers -Wsync-nand \
			-Wpacked-not-aligned -Wmissing-parameter-type \
			-Warray-bounds=2

WARN2	= 	-Wconversion -Wunsuffixed-float-constants -Wmissing-prototypes \
			-Wcast-qual -Wswitch-default -Wswitch-enum -Wunreachable-code \
			-Wmissing-declarations -Wsequence-point -Waggregate-return \
			-Wstrict-prototypes -Wstringop-overflow=4 \
			-Wbool-operation -Wshift-overflow=2 \
			-Wsizeof-pointer-memaccess -Waddress \
			-Wdouble-promotion -Wformat-truncation=1 \
			-Wimplicit-fallthrough=5 -Wstrict-aliasing=2

WARN3	= 	-Wunused-macros -Warith-conversion \
			-Wunused-parameter -Wuninitialized -Wduplicated-branches \
			-Wparentheses -Wlogical-op -Wpacked \
			-Wmissing-noreturn -Wmissing-format-attribute -Wformat-signedness \
			-Wsizeof-pointer-memaccess -Wmemset-transposed-args \
			-Wshadow=compatible-local -Wclobbered -Wswitch-bool \
			-Wshift-negative-value -Wrestrict

WARN4	= 	-Wduplicated-cond -Wshadow -Wformat-overflow -Wformat-security \
			-Wnull-dereference -Wold-style-definition -Wredundant-decls \
			-Wnested-externs -Wbad-function-cast -Wcast-qual \
			-Wdisabled-optimization -Wshift-overflow=2 -Wdate-time \
			-Wvla-larger-than=65536 -Wformat -Wsuggest-final-methods \
			-Wsuggest-final-types -Wcast-function-type \
			-Wmaybe-uninitialized -Wstrict-overflow=4 -Wtrampolines \
			-Wvector-operation-performance -Walloc-zero \
			-Wsuggest-attribute=const -Wsuggest-attribute=noreturn \
			-Wsuggest-attribute=malloc -Wsuggest-attribute=pure \
			-Wsuggest-attribute=format

CC		=	gcc
CFLAGS	+=	$(WARN1) $(WARN2) $(WARN3) $(WARN4) -Ilibs/myteams -Iinclude -g3
LDFLAGS += -L./libs/myteams -lmyteams -luuid

RM		=	rm -rf

SERVER_SRC	=	$(shell find src/server -type f -name "*.c")
CLIENT_SRC	=	$(shell find src/client -type f -name "*.c")

all:	$(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER):
	@$(CC) $(SERVER_SRC) -o $(NAME_SERVER) $(LDFLAGS) $(CFLAGS)

$(NAME_CLIENT):
	@$(CC) $(CLIENT_SRC) -o $(NAME_CLIENT) $(LDFLAGS) $(CFLAGS)

clean:
	@$(RM) vgcore.*

fclean:	clean
	@$(RM) $(NAME_SERVER) $(NAME_CLIENT)

re:		fclean all

.PHONY: all clean fclean re
