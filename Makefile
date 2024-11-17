ROOT_DIRECTORY = $(shell git rev-parse --show-toplevel)

include $(ROOT_DIRECTORY)/build_scheme/module-flags.mk


OBJECTS_DIRECTORY 			:= $(ROOT_DIRECTORY)/objects
SOURCES_DIRECTORY 			:= $(ROOT_DIRECTORY)/sources/

ALL_SERVER_LIBRARIES 		:= $(filter-out $(OBJ_DIR)/client/client.a $(OBJ_DIR)/entry-points/client/entry-points-client.a, $(shell find $(OBJECTS_DIRECTORY) -name "*.a" ))
ALL_CLIENT_LIBRARIES		:= $(filter-out $(OBJ_DIR)/server/server.a $(OBJ_DIR)/entry-points/server/entry-points-server.a, $(shell find $(OBJECTS_DIRECTORY) -name "*.a" ))

ALL_HEADERS 				:= $(shell find $(ROOT_DIRECTORY)/sources -type d)
ALL_HEADERS_FLAGS 			:= $(addprefix -I, $(ALL_HEADERS))

.DEFAULT_GOAL := all

all:
	@for dir in $(shell find $(SOURCES_DIRECTORY) -type d); do \
		if [ -f $$dir/Makefile ]; then \
			echo "Found Makefile in $$dir, running 'make'..."; \
			$(MAKE) -C $$dir; \
		else \
			echo "No Makefile in $$dir"; \
		fi; \
	done

server: all $(ALL_SERVER_LIBRARIES)
	$(CC) $(CFLAGS) $(ALL_HEADERS_FLAGS) -o server $(ALL_SERVER_LIBRARIES)

client: all $(ALL_CLIENT_LIBRARIES)
	$(CC) $(CFLAGS) $(ALL_HEADERS_FLAGS) -o client $(ALL_CLIENT_LIBRARIES)

clean:
	$(RM) $(OBJECTS_DIRECTORY)

fclean:
	$(RM) $(OBJECTS_DIRECTORY) ./server ./client

.PHONY: server clean fclean client all