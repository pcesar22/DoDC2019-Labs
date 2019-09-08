// Lab 5 -- ALU design

module alu (
            input [3:0]    aluop,
            input [N-1:0]  a,
            input [N-1:0]  b,
            output         zero,
            output [N-1:0] result);

  parameter N = 32;

  localparam OP_SUM     = 4'b0000;
  localparam OP_SUB     = 4'b0010;
  localparam OP_AND     = 4'b0100;
  localparam OP_OR      = 4'b0101;
  localparam OP_XOR     = 4'b0110;
  localparam OP_NOR     = 4'b0111;
  localparam OP_SLT     = 4'b1010;

  reg [N-1:0]              result;
  wire [N-1:0]             diff;

  assign diff = a - b;

  always @ (*) begin
    case (aluop)
      OP_AND:
        result = a & b;
      OP_OR:
        result = a | b;
      OP_XOR:
        result = a ^ b;
      OP_NOR:
        result = ~(a | b);
      OP_SUM:
        result = a + b;
      OP_SUB:
        result = a - b;
      OP_SLT:
        result = { 31'd0, diff[N-1]} ;
      // result = 32'd1;
      default:
        ;
    endcase // case (aluop)
  end

  assign zero = (result == 32'd0) ? 1'b1 : 1'b0;

endmodule // alu
