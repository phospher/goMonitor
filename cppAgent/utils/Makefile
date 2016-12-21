all: libutils.a

LIB_DIR = ../lib
OUT_DIR = ../out
INCLUDE = -I./include -I../include
SRC_DIR = ./src

libutils.a: config.o
	ar cr $(LIB_DIR)/libutils.a $(OUT_DIR)/config.o
	-mkdir ../include/utils
	cp ./include/config.h ../include/utils/config.h

config.o: init_dir
	g++ -c $(INCLUDE) -o $(OUT_DIR)/config.o $(SRC_DIR)/iniConfig.cpp

init_dir: 
	-mkdir $(LIB_DIR)
	-mkdir $(OUT_DIR)