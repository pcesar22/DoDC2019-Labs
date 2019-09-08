
#include "Valu.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

#include <string>

using namespace std;

#define OP_SUM     0b0000
#define OP_SUB     0b0010
#define OP_AND     0b0100
#define OP_OR      0b0101
#define OP_XOR     0b0110
#define OP_NOR     0b0111
#define OP_SLT     0b1010

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
    case OP_XOR:
        operatorName = "XOR";
        break;
    case OP_NOR:
        operatorName = "NOR";
        break;
    case OP_SUB:
        operatorName = "SUB";
        break;
    case OP_SLT:
        operatorName = "SLT";
        break;
    default:
        operatorName = "UNDEFINED";
        break;
    }
    return operatorName;
}

int generateRandomOperation()
{
    int result = 0;
    int val = int(rand() % 7);
    switch(val)
    {
    case 0:
        result = OP_SUM; break;
    case 1:
        result = OP_SUB; break;
    case 2:
        result = OP_AND; break;
    case 3:
        result = OP_OR; break;
    case 4:
        result = OP_XOR; break;
    case 5:
        result = OP_NOR; break;
    case 6:
        result = OP_SLT; break;
    default:
        break;
    }
    return result;
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
    case OP_XOR:
        prediction = a ^ b;
        break;
    case OP_NOR:
        prediction = ~(a | b);
        break;
    case OP_SUM:
        prediction = a + b;
        break;
    case OP_SUB:
        prediction = a - b;
        break;
    case OP_SLT:
        prediction = (a<b)?1:0;
        break;
    default:
        // default to a for unknown operators
        prediction = a;
        break;
    }
    return prediction;
}

int main(int argc, char **argv, char **env)
{
    Verilated::commandArgs(argc, argv);


    // init top verilog instance
    Valu* tb = new Valu;

    // Parse arguments locally
    bool verbose = false;
    for (int i  = 0; i < argc; i++)
    {
        if (string(argv[i]) == "--verbose")
        {
            verbose = true;
        }
    }

    // init trace dump
    /* Verilated::traceEverOn(true); */
    /* VerilatedVcdC* tfp = new VerilatedVcdC; */

    string operatorName;
    int numOfTests = 10000;
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

        if (verbose)
        {
            printf("[%d/%d]: %d %s %d = %d",
                   i+1,
                   numOfTests,
                   tb->op_a_i,
                   operatorName.c_str(),
                   tb->op_b_i,
                   tb->op_res_o);
        }
        if (tb->op_res_o != prediction )
        {
            allPass = false;

            printf(" ... FAIL (expected %08X, got %08X)\n", prediction , tb->op_res_o);
        }
        else if (verbose) printf(" ... SUCCESS!\n");
    }

    if (allPass)
    {
        printf("All %d tests passed!\n", numOfTests);
    }

    exit(0);
}
