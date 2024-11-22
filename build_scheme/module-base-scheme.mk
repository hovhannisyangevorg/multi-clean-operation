ROOT_DIRECTORY = $(shell git rev-parse --show-toplevel)

include $(ROOT_DIRECTORY)/build_scheme/module-flags.mk

SOURCES		:= $(wildcard *.c)
HEADERS		:= $(wildcard *.h)
OBJECTS		:= $(patsubst %.c, $(OBJECTS_DIR)/%.o, $(SOURCES))
LIBRARY 	:= $(OBJECTS_DIR)/$(NAME)

ALL_HEADERS 		:= $(shell find $(ROOT_DIRECTORY)/sources -type d)
ALL_HEADERS_FLAGS 	:= $(addprefix -I, $(ALL_HEADERS))

.DEFAULT_GOAL := all

all: $(LIBRARY)

$(LIBRARY): $(OBJECTS_DIR) $(OBJECTS)
	ar rcs $(LIBRARY) $(OBJECTS)

$(OBJECTS_DIR)/%.o: %.c $(UTILS_HEDRS)
	$(CC) $(CFLAGS) $(ALL_HEADERS_FLAGS) -c $< -o $@

$(OBJECTS_DIR):
	$(MK) $(OBJECTS_DIR)

clean:
	$(RM) $(OBJECTS)

fclean:
	$(RM) $(OBJECTS_DIR)

.PHONY: clean all clean