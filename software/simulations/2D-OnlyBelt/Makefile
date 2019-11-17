# Text style
RED    = \033[0;31m
GREEN  = \033[0;32m
NC     = \033[0m
BOLD   = \033[1m

BIN=bin/
SRC=src/
LIB=lib/
OBJ=obj/

FLAGS = -lGL -lGLU -lglut

all: ${BIN}mobix2D

${BIN}mobix2D: ${OBJ}parameters.o ${OBJ}robot.o ${OBJ}main.o
	@/bin/echo -e "\n${GREEN}${BOLD}----- Compiling object files -----${NC}"
	g++ -g -o ${BIN}mobix2D ${OBJ}main.o ${OBJ}robot.o ${FLAGS}

${OBJ}main.o: ${SRC}main.cpp
	g++ -g -O0 -g3 -Wall -I${LIB} -c -o ${OBJ}main.o ${SRC}main.cpp

${OBJ}robot.o: ${SRC}robot.cpp
	g++ -g -O0 -g3 -Wall -I${LIB} -c -o ${OBJ}robot.o ${SRC}robot.cpp

${OBJ}parameters.o: ${LIB}parameters.h
	g++ -g -O0 -g3 -Wall -I${LIB} -c -o ${OBJ}parameters.o ${LIB}parameters.h

clean:
	@/bin/echo -e "\n${GREEN}${BOLD}----- Cleaning project -----${NC}"
	@rm -rf ${OBJ}*.o
	@rm -f ${BIN}mobix2D

run: all
	@/bin/echo -e "\n${GREEN}${BOLD}----- Running mobix 2D simulation -----${NC}"
	./${BIN}mobix2D
