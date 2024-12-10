CC 							:= gcc
CFLAGS 						:= -Wall -Wextra -Werror -g3 -fsanitize=address
MK							:= mkdir -p
RM							:= rm -rf
FOR_L						:= lib

# Define the linker flags for grouping libraries
WL							:= -Wl
LDFLAG_START 				:= $(WL),--start-group
LDFLAG_END   				:= $(WL),--end-group


#-g3 -fsanitize=address