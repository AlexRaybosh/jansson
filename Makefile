where-am-i = $(CURDIR)/$(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST))
THIS_MAKEFILE := $(call where-am-i)
ROOT := $(dir $(THIS_MAKEFILE))
$(info ROOT $(ROOT))

export CXXFLAGS =	-g -fpic -D_REENTRANT -Wall -fmessage-length=0 -std=gnu++11 -D_POSIX_C_SOURCE=201712L -D_XOPEN_SOURCE=600
export LDFLAGS := -fpic -lpthread
export CFLAGS =	-g -fpic -D_REENTRANT -D_POSIX_C_SOURCE=201712L -D_XOPEN_SOURCE=600 -std=gnu99

all: $(ROOT)/jansson_src

#$(ROOT)/src_native:
#	@$(MAKE) -C $@ ROOT=$(ROOT)	CXX=$(X86_64_CXX) CXXFLAGS=$(X86_64_CXXFLAGS) LIB_LDFLAGS=$(X86_64_LIB_LDFLAGS) ARCH=$(X86_64_ARCH) ARCH_INCLUDE=$(X86_64_ARCH_INCLUDE) JNI_BUILD=$(X86_64_JNI_BUILD)
#	@$(MAKE) -C $@ ROOT=$(ROOT)	CXX=$(ARMV6_CXX) CXXFLAGS=$(ARMV6_CXXFLAGS) LIB_LDFLAGS=$(ARMV6_LIB_LDFLAGS) ARCH=$(ARMV6_ARCH) ARCH_INCLUDE=$(ARMV6_ARCH_INCLUDE) JNI_BUILD=$(ARMV6_JNI_BUILD)

$(ROOT)/jansson_src:
	@$(MAKE) -C $@ ROOT=$(ROOT)

clean:
	@echo "Cleaning " $(CURDIR)
	@$(MAKE) -C jansson_src ROOT=$(ROOT) clean
	rm -rf build dist


install:
	@echo "Installing " $(CURDIR)

.PHONY: all clean install $(ROOT)/jansson_src