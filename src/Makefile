OBJS = *.cpp
CXX = g++
INCLUDES = -I ../resources/images -I ../resources/fonts
CPPFLAGS = -WALL
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

app: $(OBJS)
	$(CXX) -o runGame $(OBJS) $(LDLIBS) $(INCLUDES)

clean:
	$(RM) runGame

debug:
	$(CXX) -g $(OBJS) -o debugGame $(LDLIBS) $(INCLUDES)
##For Debug mode, you'll need to go into a gdb session, which can be done with this command: gbd debugGame
##Before going into gdb, you can look at the man page for commands and info, but here's a pretty standard command when your program is running through gdb: run
