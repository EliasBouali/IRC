NAME        = ircserv
CXX         = c++
CXXFLAGS    = -Wall -Wextra -Werror -std=c++98

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
    # MacOS
    CXXFLAGS += -stdlib=libc++
    LDFLAGS  = -lc++
else
    # Linux
    LDFLAGS  = -lstdc++
endif


SRC         = src/main.cpp src/Channel.cpp src/Client.cpp src/Server.cpp src/Message.cpp
INCS        = -I includes


OBJ_DIR     = obj
OBJ         = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.cpp=.o)))


all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

$(OBJ_DIR)/%.o: src/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INCS) -c $< -o $@

clean:
	rm -f $(OBJ)
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
