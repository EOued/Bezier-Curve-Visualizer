visualizer: visualizer.o display.o bezier.o
	g++ -O0 visualizer.o display.o bezier.o -g -Wall -Wextra -Wvla -Werror -fsanitize=address,undefined -o visualizer -lsfml-graphics -lsfml-window -lsfml-system -lm

visualizer.o: visualizer.cpp
	g++ -c visualizer.cpp

display.o: Display/display.cpp
	g++ -c Display/display.cpp

bezier.o: Maths/bezier.cpp
	g++ -c Maths/bezier.cpp

clean:
	rm visualizer && rm *.o && echo "Cleaned executable"
