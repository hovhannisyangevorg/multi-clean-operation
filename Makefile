ROOT_DIRECTORY = $(shell git rev-parse --show-toplevel)

include $(ROOT_DIRECTORY)/build_scheme/module-flags.mk

SERVER_EXECUTION_FILE_NAME				= server
CLIENT_EXECUTION_FILE_NAME				= client

OBJECTS_DIRECTORY 						:= $(ROOT_DIRECTORY)/objects
SOURCES_DIRECTORY 						:= $(ROOT_DIRECTORY)/sources

ALL_DIRECTORY_SRC						:= $(shell find $(SOURCES_DIRECTORY) -type d)
ALL_DIRECTORY_OBJ 						:= $(shell find $(OBJECTS_DIRECTORY) -type d)

ALL_SERVER_LIBRARIES 					= $(filter-out $(OBJECTS_DIRECTORY)/client/$(FOR_L)client.a $(OBJECTS_DIRECTORY)/entry-points/client/$(FOR_L)entry-points-client.a, $(shell find $(OBJECTS_DIRECTORY) -name "*.a"))
ALL_SERVER_OBJECTS 						= $(wildcard $(OBJECTS_DIRECTORY)/server/*.o) $(wildcard $(OBJECTS_DIRECTORY)/entry-points/server/*.o)
ALL_SERVER_LIBRARIES_DIR 				= $(filter-out $(OBJECTS_DIRECTORY)/client $(OBJECTS_DIRECTORY)/entry-points/client, $(shell find $(OBJECTS_DIRECTORY) -type d))
ALL_SERVER_LIBRARIES_DIRECTORY_FLAGS	= $(addprefix -L, $(ALL_SERVER_LIBRARIES_DIR))
ALL_SERVER_HEADERS_DIR					= $(filter-out $(SOURCES_DIRECTORY)/client $(SOURCES_DIRECTORY)/entry-points/client, $(shell find $(SOURCES_DIRECTORY) -type d))
ALL_SERVER_HEADERS_DIRECTORY_FLAGS 		= $(addprefix -I, $(ALL_SERVER_HEADERS_DIR))
ALL_SERVER_ARCHIVE_NAMES 				= $(patsubst lib%.a, %, $(notdir $(ALL_SERVER_LIBRARIES)))
ALL_SERVER_ARCHIVE_NAMES_FLAGS			= $(addprefix -l, $(ALL_SERVER_ARCHIVE_NAMES))
ALL_SERVER_ARCHIVE_NAMES_FLAGS			+= -ldotenv

ALL_CLIENT_LIBRARIES					= $(filter-out $(OBJECTS_DIRECTORY)/server/$(FOR_L)server.a $(OBJECTS_DIRECTORY)/entry-points/server/$(FOR_L)entry-points-server.a, $(shell find $(OBJECTS_DIRECTORY) -name "*.a"))
ALL_CLIENT_OBJECTS 						= $(wildcard $(OBJECTS_DIRECTORY)/client/*.o) $(wildcard $(OBJECTS_DIRECTORY)/entry-points/client/*.o)
ALL_CLIENT_LIBRARIES_DIR				= $(filter-out $(OBJECTS_DIRECTORY)/server $(OBJECTS_DIRECTORY)/entry-points/server, $(shell find $(OBJECTS_DIRECTORY) -type d))
ALL_CLIENT_LIBRARIES_LIBRARIES_FLAGS	= $(addprefix -L, $(ALL_CLIENT_LIBRARIES_DIR))
ALL_CLIENT_HEADERS_DIR					= $(filter-out $(SOURCES_DIRECTORY)/server $(SOURCES_DIRECTORY)/entry-points/server, $(shell find $(SOURCES_DIRECTORY) -type d))
ALL_CLIENT_HEADERS_DIRECTORY_FLAGS		= $(addprefix -I, $(ALL_CLIENT_HEADERS_DIR))
ALL_CLIENT_ARCHIVE_NAMES				= $(patsubst lib%.a, %, $(notdir $(ALL_CLIENT_LIBRARIES)))
ALL_CLIENT_ARCHIVE_NAMES_FLAGS			= $(addprefix -l, $(ALL_CLIENT_ARCHIVE_NAMES))
#------------------------------------------------------------------------------------------------------------------------
ALL_CLIENT_ARCHIVE_NAMES_FLAGS 			+= -ldotenv

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

re:	fclean all

server: all $(ALL_SERVER_LIBRARIES)
	$(CC) $(CFLAGS) $(ALL_SERVER_HEADERS_DIRECTORY_FLAGS) -o $(SERVER_EXECUTION_FILE_NAME) $(ALL_SERVER_LIBRARIES_DIRECTORY_FLAGS) $(LDFLAG_START) $(ALL_SERVER_ARCHIVE_NAMES_FLAGS) $(LDFLAG_END)

client: all $(ALL_SERVER_LIBRARIES)
	$(CC) $(CFLAGS) $(ALL_CLIENT_HEADERS_DIRECTORY_FLAGS) -o $(CLIENT_EXECUTION_FILE_NAME) $(ALL_CLIENT_LIBRARIES_LIBRARIES_FLAGS) $(LDFLAG_START) $(ALL_CLIENT_ARCHIVE_NAMES_FLAGS) $(LDFLAG_END)

clean:
	$(RM) $(OBJECTS_DIRECTORY)

fclean:
	$(RM) $(OBJECTS_DIRECTORY) ./server ./client

load:
	./dependency/dotenv-c.sh

.PHONY: server clean fclean client all test re