all: monitorAgent

monitorAgent: libutils.a
	-mkdir ./monitorAgent/build
	cd ./monitorAgent/build && cmake ..
	cd ./monitorAgent/build && make && make install

libutils.a:
	-mkdir ./utils/build
	cd ./utils/build && cmake ..
	cd ./utils/build && make && make install

clean:
	cd ./monitorAgent && make clean
	cd ./utils && make clean