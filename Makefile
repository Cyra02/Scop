NAME     = scop
CXX      = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++17 -Iincludes
LDFLAGS  = $(shell pkg-config --libs glfw3) -lGL -ldl

SRCS     = srcs/main.cpp srcs/Mat4.cpp
OBJS     = $(SRCS:srcs/%.cpp=obj/%.o)

all: deps $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

obj/%.o: srcs/%.cpp
	@mkdir -p obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

deps:
	@pkg-config --exists glfw3 || { echo "Falta GLFW: sudo apt install libglfw3-dev libgl1-mesa-dev"; exit 1; }

clean:
	rm -rf obj

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re deps