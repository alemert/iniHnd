################################################################################
# makefile for test util
################################################################################

MAKE_INCLUDE_PATH=mk.inc

# ------------------------------------------------------------------------------
# Compiler and BIT
# ------------------------------------------------------------------------------
CC=gcc
BIT = 64

# ------------------------------------------------------------------------------
# debugger
# ------------------------------------------------------------------------------
DBGOPT = -g

# ------------------------------------------------------------------------------
# sources
# ------------------------------------------------------------------------------
SOURCES = reader.c node.c

AROWN = 
LSOWN = msgcat sogen

# ------------------------------------------------------------------------------
# main source
# ------------------------------------------------------------------------------
MAIN = 

# ------------------------------------------------------------------------------
# BINARY
# ------------------------------------------------------------------------------
BINARY = 

# ------------------------------------------------------------------------------
# libraries dynamic & static
# ------------------------------------------------------------------------------
LIBRARY = libinih.so
ARCHIVE  = libinih.a

# ------------------------------------------------------------------------------
# rollout includes
# ------------------------------------------------------------------------------
ROLLOUT_INC = 

# ------------------------------------------------------------------------------
# general includes
# ------------------------------------------------------------------------------
include $(MAKE_INCLUDE_PATH)/general.modules.mk

# ------------------------------------------------------------------------------
# tests
# ------------------------------------------------------------------------------
TEST = t_node_000   t_node_001   t_node_002   \
       t_reader_000 t_reader_001 t_reader_002 t_reader_005 

include $(MAKE_INCLUDE_PATH)/test.mk

