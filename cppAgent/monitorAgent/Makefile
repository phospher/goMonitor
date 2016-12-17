all: monitorAgent

BIN_DIR = ../bin
OUT_DIR = ../out

monitorAgent: main.o monitorAgent.o
	g++ -o $(BIN_DIR)/monitorAgent $(OUT_DIR)/main.o $(OUT_DIR)/monitorAgent.o

monitorAgent.o: monitorAgent.h monitorAgent.cpp
	g++ -c -o $(OUT_DIR)/monitorAgent.o monitorAgent.cpp

main.o: main.cpp monitorAgent.h init_dir
	g++ -c -o $(OUT_DIR)/main.o main.cpp

init_dir: 
	-mkdir $(BIN_DIR)
	-mkdir $(OUT_DIR)