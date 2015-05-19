main:main.o ObjLoad.o
	g++ main.o ObjLoad.o -D_STDCALL_SUPPORTED -DGLUT_DISABLE_ATEXIT_HACK -l opengl32 -l glu32 -l glut32 -o main
main.o:main.cpp
	g++ -c main.cpp -o main.o
ObjLoad.o:ObjLoad.cpp
	g++ -c ObjLoad.cpp -o ObjLoad.o

.PHONY : clean
clean:
	rm -rf *.o

