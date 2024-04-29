##
## EPITECH PROJECT, 2024
## B_OOP_400_MPL_4_1_raytracer_robin_glaude
## File description:
## Makefile
##

TARGET = plane

SRC = Plane.cpp \
	../../../src/shapes/AShape.cpp \
	../../../src/math/Vector3D.cpp \
	../../../src/math/Point3D.cpp \
	../../../src/materials/AMaterial.cpp \
	../../utils/ANode.cpp \
	../../transformations/Transform.cpp

CC = g++

CFLAGS= -std=c++20

LIBNAME = ../../../plugins/$(TARGET).so

INCLUDE = ../../../include

OBJ = $(SRC:.cpp=.o)

all: $(LIBNAME)

%.o: %.cpp
	$(CC) $(CFLAGS) -fPIC -c $< -o $@ -I $(INCLUDE)

$(LIBNAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ -fPIC -shared

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(LIBNAME)

re: fclean all
