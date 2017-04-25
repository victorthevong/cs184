
vis_osx: Particles.h
	g++ -std=c++0x -I./glm main.cpp Particles.cpp -o sim -framework GLUT -framework OpenGL -lopencv_core -lopencv_highgui
