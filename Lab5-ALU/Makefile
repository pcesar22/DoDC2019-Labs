.PHONY: all
all: alu

VERILATOR=verilator
VERILATOR_ROOT ?= $(shell bash -c 'verilator -V|grep VERILATOR_ROOT | head -1 | sed -e "s/^.*=\s*//"')
VINC := $(VERILATOR_ROOT)/include

# Ideally, we'd want -GWIDTH=12
# This requires a newer version of Verilator than I have with my distro
# Hence we have the `ifdef inside alu.v
obj_dir/Valu.cpp: alu.v
	$(VERILATOR) --trace -Wall -cc alu.v

obj_dir/Valu__ALL.a: obj_dir/Valu.cpp
	make --no-print-directory -C obj_dir -f Valu.mk

alu: tb_alu.cpp obj_dir/Valu__ALL.a
	g++ -I$(VINC) -I obj_dir    \
		$(VINC)/verilated.cpp       \
		$(VINC)/verilated_vcd_c.cpp \
		tb_alu.cpp obj_dir/Valu__ALL.a \
		-o alu

.PHONY: clean
clean:
	rm -rf obj_dir/ alu alutrace.vcd
