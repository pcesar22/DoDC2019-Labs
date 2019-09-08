// Lab 5 -- ALU design

module alu (
            input [3:0]    op_sel_i,
            input [N-1:0]  op_a_i,
            input [N-1:0]  op_b_i,
            output [N-1:0] op_res_o);

  parameter N = 32;

  localparam OP_AND     = 4'b0000;
  localparam OP_OR      = 4'b0001;
  localparam OP_SUM     = 4'b0010;
  localparam OP_UNUSED  = 4'b0011;
  localparam OP_AND_NOT = 4'b0100;
  localparam OP_OR_NOT  = 4'b0101;
  localparam OP_MINUS   = 4'b0110;
  localparam OP_SLT     = 4'b0111;

  always @ (*) begin
    case (op_sel_i)
      OP_AND:
        op_res_o = op_a_i & op_b_i;
      OP_OR:
        op_res_o = op_a_i | op_b_i;
      OP_SUM:
        op_res_o = op_a_i + op_b_i;
      OP_UNUSED:
        op_res_o = op_a_i;
      OP_AND_NOT:
        op_res_o = op_a_i & ~op_b_i;
      OP_OR_NOT:
        op_res_o = op_a_i | ~op_b_i;
      OP_MINUS:
        op_res_o = op_a_i - op_b_i;
      OP_SLT:
        op_res_o = (op_a_i < op_b_i) ? op_a_i : op_b_i;
      default:
        ;
    endcase // case (op_sel_i)
  end


endmodule // alu
