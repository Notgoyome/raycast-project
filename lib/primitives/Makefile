##
## EPITECH PROJECT, 2024
## B_OOP_400_MPL_4_1_raytracer_robin_glaude
## File description:
## Makefile
##

SUBDIRS = sphere

.PHONY: all $(SUBDIRS)

all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

clean:
	$(foreach dir, $(SUBDIRS), $(MAKE) -C $(dir) clean;)

fclean:
	$(foreach dir, $(SUBDIRS), $(MAKE) -C $(dir) fclean;)

re: fclean all
