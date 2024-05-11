XPRA_LIST := $(shell xpra list)
XPRA_CMD = xpra start --bind-tcp=0.0.0.0:8080
DISPLAY=

.PHONY : test2 test all

all:
ifeq ($(findstring LIVE session at, $(XPRA_LIST)), )
	@$(XPRA_CMD) 2> /dev/null
	@echo Please wait for server to start...
	@sleep 5
	@make --no-print-directory test
else
	$(eval DISPLAY = $(shell echo $(XPRA_LIST) | cut -d : -f4))
	g++ main.cpp -o app -lGL -lglut
	DISPLAY=:$(DISPLAY) ./app
endif

test:
ifeq ($(findstring LIVE session at, $(shell xpra list)), )
	@echo Still working...
	@sleep 5
	@make --no-print-directory test2
else
	@echo
	@echo Server is running.
	@echo
	@echo Please launch your OpenGL View, click \"Connect\", and run \"make\" again.
	@echo
endif

test2:
ifeq ($(findstring LIVE session at, $(shell xpra list)), )
	@echo Still working...
	@sleep 5
	@echo Could not start server.
	@echo Please run "xpra list" to check if you have a live session.
	@echo Then run "make" again.
	xpra list
else
	@echo
	@echo Server is running.
	@echo
	@echo Please launch your OpenGL View, click \"Connect\", and run \"make\" again.
	@echo
endif

clean:
	rm -rf app