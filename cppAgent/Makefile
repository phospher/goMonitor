all: monitorAgent

monitorAgent: libutils.a
	cd ./monitorAgent && make

libutils.a:
	cd ./utils && make

clean:
	cd ./monitorAgent && make clean
	cd ./utils && make clean