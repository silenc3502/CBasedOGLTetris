game		:=	game
presenter	:=	presenter
view		:=	view
math		:=	math
shader		:=	shader

modules		:=	$(shader) $(game) $(presenter) $(view) $(math)

cores		:=	main

SUBDIRS		:=	$(cores) $(modules)

.PHONY: all $(cores) $(modules)
all: $(cores)
	@echo "$(cores)"
	@echo "$(modules)"
	@echo "$(shell pwd)"
#	gcc main/main.c -lglut -lGL -lGLU

$(cores) $(modules):
	$(MAKE) --directory=$@

$(cores): $(modules)

clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done