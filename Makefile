CC=g++
CFLAGS=-I./includes -I./src -std=c++17 -fPIC -g3
LDFLAGS=-shared
MAIN_SRCS=$(shell find src/main -name "*.cpp")
CAMERAS=$(patsubst src/cameras/%/,%, $(wildcard src/cameras/*/))
LIGHTS=$(patsubst src/lights/%/,%, $(wildcard src/lights/*/))
MATERIALS=$(patsubst src/materials/%/,%, $(wildcard src/materials/*/))
SCENES=$(patsubst src/scenes/%/,%, $(wildcard src/scenes/*/))
SHAPES=$(patsubst src/shapes/%/,%, $(wildcard src/shapes/*/))
TRANSFORMATIONS=$(patsubst src/transformations/%/,%, $(wildcard src/transformations/*/))
PLUGINS_TARGETS=$(foreach plugin,$(CAMERAS),plugins/cameras_$(plugin).so) \
				$(foreach plugin,$(LIGHTS),plugins/lights_$(plugin).so) \
				$(foreach plugin,$(MATERIALS),plugins/materials_$(plugin).so) \
				$(foreach plugin,$(SCENES),plugins/scenes_$(plugin).so) \
				$(foreach plugin,$(SHAPES),plugins/shapes_$(plugin).so) \
				$(foreach plugin,$(TRANSFORMATIONS),plugins/transformations_$(plugin).so)

.PHONY: all clean

all: main plugins

main: $(MAIN_SRCS)
	$(CC) $(CFLAGS) -o raytracer $(MAIN_SRCS)

define build_plugin
plugins/$(1)_$(2).so:
	$(CC) $(CFLAGS) $(wildcard src/$(1)/$(2)/*.cpp) $(LDFLAGS) -o plugins/$(1)_$(2).so
endef

plugins: $(PLUGINS_TARGETS)

$(foreach plugin,$(CAMERAS),$(eval $(call build_plugin,cameras,$(plugin))))
$(foreach plugin,$(LIGHTS),$(eval $(call build_plugin,lights,$(plugin))))
$(foreach plugin,$(MATERIALS),$(eval $(call build_plugin,materials,$(plugin))))
$(foreach plugin,$(SCENES),$(eval $(call build_plugin,scenes,$(plugin))))
$(foreach plugin,$(SHAPES),$(eval $(call build_plugin,shapes,$(plugin))))
$(foreach plugin,$(TRANSFORMATIONS),$(eval $(call build_plugin,transformations,$(plugin))))

clean:
	rm -f plugins/*.so

fclean: clean
	rm -f raytracer

re: fclean all