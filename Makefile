F_NAME =  server.cpp   client.cpp  channel.cpp main.cpp command.cpp
		 
NAME = ircserv
CXX = c++
CXXFLAGS =  -std=c++11 -Wall -Wextra -Werror 

O_FILE = $(F_NAME:.cpp=.o)

all: $(NAME)

$(NAME) : $(O_FILE)
	c++ $(CXXFLAGS)  $(O_FILE) -o $(NAME)

%.o: %.cpp *.hpp
	c++ $(CXXFLAGS) -c $< -o $@

re: fclean all
clean:
	rm -rf $(O_FILE)

fclean: clean
	rm -rf $(NAME)