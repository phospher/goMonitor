all: monitorAgent init_dir

BIN_DIR = ../bin
OUT_DIR = ../out
INCLUDE = -I./include -I../include
SRC_DIR = ./src
LIBS_PATH = -L../lib
LIBS = -lutils
OBJS = monitorAgent.o main.o

monitorAgent: $(OBJS)
	g++ $(LIBS_PATH) -o $(BIN_DIR)/$@ $(addprefix $(OUT_DIR)/, $(OBJS)) $(LIBS)

$(OBJS): %.o: $(SRC_DIR)/%.cpp init_dir
	g++ -c $(INCLUDE) -o $(OUT_DIR)/$@ $<

init_dir: 
	-mkdir $(BIN_DIR)
	-mkdir $(OUT_DIR)

clean:
	-rm -rf $(BIN_DIR)
	-rm -rf $(OUT_DIR)