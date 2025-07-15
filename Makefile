# Compilador e flags
CC = g++
CXFLAGS = -Wall -Wextra -Wpedantic -Wconversion -Wformat-security -Werror
CXDEBUG = -g
CXVER = -std=c++17

# Diretórios
SRC_DIR = src
INC_DIR = include
EXEC = tp2.out

# Arquivos fonte e cabeçalhos
SRCS = $(SRC_DIR)/grafo.cpp $(SRC_DIR)/auxs.cpp $(SRC_DIR)/main.cpp
HDRS = $(INC_DIR)/grafo.hpp $(INC_DIR)/auxs.hpp 

# Regra padrão
all: compile

# Compilação normal
compile: $(SRCS) $(HDRS)
	$(CC) $(CXFLAGS) $(CXVER) -I$(INC_DIR) $(SRCS) -o $(EXEC)

# Compilação em modo de depuração
debug: $(SRCS) $(HDRS)
	$(CC) $(CXFLAGS) $(CXVER) $(CXDEBUG) -I$(INC_DIR) $(SRCS) -o $(EXEC)

# Limpeza de arquivos compilados
clean:
	rm -f $(EXEC)

.PHONY: all clean debug compile
