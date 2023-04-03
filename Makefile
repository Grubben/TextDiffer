NAME	= textdiffer

SRCS	= $(wildcard *.cpp)
SRCS	+= backends/imgui_impl_sdl2.cpp backends/imgui_impl_opengl2.cpp misc/cpp/imgui_stdlib.cpp
OBJS	= $(SRCS:.cpp=.o)

CXXFLAGS = -std=c++11 -I. -I./backends
CXXFLAGS += -g -Wall -Wformat
CXXFLAGS += `sdl2-config --cflags`

LIBS	= -lGL -ldl `sdl2-config --libs`

$(NAME)	: $(OBJS)
			$(CXX) -o $(NAME) $(OBJS)  $(CXXFLAGS) $(LIBS)

c		:
			$(RM) $(OBJS) $(NAME)

r		: c $(NAME)