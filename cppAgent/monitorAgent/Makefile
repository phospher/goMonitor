all: monitorAgent

BIN_DIR = ../bin
OUT_DIR = ../out
INCLUDE = -I./include
SRC_DIR = ./src

monitorAgent: main.o monitorAgent.o
	g++ -o $(BIN_DIR)/monitorAgent $(OUT_DIR)/main.o $(OUT_DIR)/monitorAgent.o

monitorAgent.o: init_dir
	g++ -c $(INCLUDE) -o $(OUT_DIR)/monitorAgent.o $(SRC_DIR)/monitorAgent.cpp

main.o: init_dir
	g++ -c $(INCLUDE) -o $(OUT_DIR)/main.o $(SRC_DIR)/main.cpp

init_dir: 
	-mkdir $(BIN_DIR)
	-mkdir $(OUT_DIR)