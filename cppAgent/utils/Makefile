all: libutils.a

LIB_DIR = ../lib
OUT_DIR = ../out
INCLUDE = -I./include -I../include
SRC_DIR = ./src
OBJS = iniConfig.o

libutils.a: $(OBJS)
	ar cr $(LIB_DIR)/$@ $(addprefix $(OUT_DIR)/, $(OBJS))
	cp ./include/*.h ../include/utils/

$(OBJS): %.o: $(SRC_DIR)/%.cpp init_dir
	g++ -c $(INCLUDE) -o $(OUT_DIR)/$@ $<

init_dir: 
	-mkdir $(LIB_DIR)
	-mkdir $(OUT_DIR)
	-mkdir ../include/utils

clean:
	-rm -rf $(LIB_DIR)
	-rm -rf $(OUT_DIR)
	-rm -rf ../include/utils/