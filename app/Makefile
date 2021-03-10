# name of your application
APPLICATION = mecanum

BOARD ?= native

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/..

#include ../Makefile.tests_common

USEMODULE += motor_driver
USEMODULE += xtimer
USEMODULE += event_callback
USEMODULE += event_timeout
USEMODULE += isrpipe

#$USEMODULE += shell
#USEMODULE += shell_commands

#FEATURES_REQUIRED += periph_qdec
#FEATURES_REQUIRED += motor_driver

CFLAGS += -DLOG_LEVEL=LOG_DEBUG
CFLAGS += -DDEBUG_ASSERT_VERBOSE

include $(RIOTBASE)/Makefile.include
