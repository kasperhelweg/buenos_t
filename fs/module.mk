# Makefile for the drivers module

# Set the module name
MODULE := fs

FILES := vfs.c tfs.c gfs.c filesystems.c 

SRC += $(patsubst %, $(MODULE)/%, $(FILES))
