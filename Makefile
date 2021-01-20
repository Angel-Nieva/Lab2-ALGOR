SRC= src
OBJ = obj



SOURCES := $(wildcard $(SRC)/*.c)
# Se obtiene los archivos .c de la carpeta en forma de
# lista de string

OBJECTS := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))
# se cambia la lista de string por una lista de objetos
# que puede interpretar make

.PHONY: clean all debug
# PHONY se ocupa para decirle que al compilador que no
# es necesario crear los archivos clean all debug
# ya que estos son solo recetas

all: $(OBJECTS)
	echo "Generando ejecutable..."
	gcc $^ $(OPTIONS) -o goloso


$(OBJ)/%.o: $(SRC)/%.c
	@echo "Generando archivos object de $@ ...."
	gcc -I$(SRC) $(OPTIONS) -c $< -o $@ 



debug: OPTIONS := -DDEBUG
debug: all

# Una receta puede tener mas de una preparación 
# make prepara las dos.


clean :
	-rm -rfv $(OBJ)/*.o
