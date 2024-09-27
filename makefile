cc = gcc
src = ./src
out = ./
remove = rm -rf $(out)
TARGET := server
SRCEXT      := c
DEPEXT      := d
OBJEXT      := o

SOURCES     := $(shell find $(src) -type f -name *.$(SRCEXT))
obj  := $(patsubst $(src)/%,$(out)/%,  $(SOURCES:.$(SRCEXT)=.$(OBJEXT)))


#Links all of the ojects together
$(TARGET): $(obj)
	$(cc) -o $(out)/$(TARGET) $^

#comples anything that has a .c file extention into a .o in the out dirctory
$(out)/%.$(OBJEXT): $(src)/%.$(SRCEXT)
	$(cc) $< -c -o $@
