#include "Valu.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

#include <string>

using namespace std;

#define OP_AND     0b0000
#define OP_OR      0b0001
#define OP_SUM     0b0010
#define OP_UNUSED  0b0011
#define OP_AND_NOT 0b0100
#define OP_OR_NOT  0b0101
#define OP_MINUS   0b0110
#define OP_SLT     0b0111

string selectOperatorName(int operation)
{
    string operatorName;

    switch(operation){
    case OP_AND:
        operatorName = "AND";
        break;
    case OP_OR:
        operatorName = "OR";
        break;
    case OP_SUM:
        operatorName = "SUM";
        break;
    case OP_UNUSED:
        operatorName = "UNUNSED";
        break;
    case OP_AND_NOT:
        operatorName = "AND NOT";
        break;
    case OP_OR_NOT:
        operatorName = "OR NOT";
        break;
    case OP_MINUS:
        operatorName = "MINUS";
        break;
    case OP_SLT:
        operatorName = "SLT";
        break;
    default:
        printf("Unknown operation: %02X!!!\n", operation);
        break;
    }
    return operatorName;
}

int generateRandomOperation()
{
    return int(rand() % 8);
}

int generateRandomNumber(int nbits)
{
    return int(rand() % (1<<(nbits-1)));
}

int predictOutput (int a, int b, int operation)
{
    int prediction;
    switch(operation){
    case OP_AND:
        prediction = a & b;
        break;
    case OP_OR:
        prediction = a | b;
        break;
    case OP_SUM:
        prediction = a + b;
        break;
    case OP_UNUSED:
        prediction = a;
        break;
    case OP_AND_NOT:
        prediction = a & ~b;
        break;
    case OP_OR_NOT:
        prediction = a | ~b;
        break;
    case OP_MINUS:
        prediction = a - b;
        break;
    case OP_SLT:
        prediction = (a<b)?a:b;
        break;
    default:
        break;
    }
    return prediction;
}

int main(int argc, char **argv, char **env)
{

    Verilated::commandArgs(argc, argv);

    // init top verilog instance
    Valu* tb = new Valu;

    // init trace dump
    /* Verilated::traceEverOn(true); */
    /* VerilatedVcdC* tfp = new VerilatedVcdC; */

    string operatorName;
    int numOfTests = 1000000;
    int prediction;
    bool allPass = true;

    for (int i = 0; i < numOfTests; i++)
    {
        tb->op_a_i = generateRandomNumber(32);
        tb->op_b_i = generateRandomNumber(32);
        tb->op_sel_i = generateRandomOperation();
        operatorName = selectOperatorName(tb->op_sel_i);
        prediction = predictOutput(tb->op_a_i, tb->op_b_i, tb->op_sel_i);
        tb->eval();

        if (tb->op_res_o == prediction)
        {
        }
        else
        {
            allPass = false;
            printf("[%d/%d]: %d %s %d = %d",
                   i+1,
                   numOfTests,
                   tb->op_a_i,
                   operatorName.c_str(),
                   tb->op_b_i,
                   tb->op_res_o);

            printf(" ... FAIL (expected %08X, got %08X)\n", prediction , tb->op_res_o);
        }
    }

    if (allPass)
    {
        printf("All %d tests passed!\n", numOfTests);
    }
    // printf("Operation selected: %2X (%s)\n",
    //        tb->op_sel_i, operatorName.c_str());
    // printf("%08X %s %08X = %08X\n",
    //        tb->op_a_i, operatorName.c_str(), tb->op_b_i, tb->op_res_o);

    /* tfp->close(); */
    exit(0);
}
