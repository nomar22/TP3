# Compile/Link 
GCC = gcc 
OPTMIZE = -g -O3 -w
LIBS = -lm
#Objetos 
OBJS =  tp3.c lista.c 
# Nome do aplicativo 
APPNAME = tp3
release : ; $(GCC) $(OPTMIZE) $(OBJS) -o $(APPNAME)  $(LIBS)
clean : rm -rf *.o 
run :
	make 
	./tp3 input.txt output.txt debug
