MODULE_NAME=alu
.PHONY: all
all: $MODULE_NAME

VERILATOR=verilator
VERILATOR_ROOT ?= $(shell bash -c 'verilator -V|grep VERILATOR_ROOT | head -1 | sed -e "s/^.*=\s*//"')
VINC := $(VERILATOR_ROOT)/include

# Ideally, we'd want -GWIDTH=12
# This requires a newer version of Verilator than I have with my distro
# Hence we have the `ifdef inside $MODULE_NAME.v
obj_dir/V$MODULE_NAME.cpp: $MODULE_NAME.v
	$(VERILATOR) --trace -Wall -cc $MODULE_NAME.v

obj_dir/V$MODULE_NAME__ALL.a: obj_dir/V$MODULE_NAME.cpp
	make --no-print-directory -C obj_dir -f V$MODULE_NAME.mk

$MODULE_NAME: tb_$MODULE_NAME.cpp obj_dir/V$MODULE_NAME__ALL.a
	g++ -I$(VINC) -I obj_dir    \
		$(VINC)/verilated.cpp       \
		$(VINC)/verilated_vcd_c.cpp \
		tb_$MODULE_NAME.cpp obj_dir/V$MODULE_NAME__ALL.a \
		-o $MODULE_NAME

.PHONY: clean
clean:
	rm -rf obj_dir/ $MODULE_NAME $MODULE_NAMEtrace.vcd
