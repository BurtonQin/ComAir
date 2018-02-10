#ifndef COMAIR_LOOPINTERESTEDHOOK_H
#define COMAIR_LOOPINTERESTEDHOOK_H

#include <fstream>

#include "llvm/Pass.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/GlobalVariable.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/IntrinsicInst.h"


using namespace llvm;
using namespace std;


struct LoopInterestedHook : public ModulePass {
    static char ID;

    LoopInterestedHook();

    virtual void getAnalysisUsage(AnalysisUsage &AU) const;

    virtual bool runOnModule(Module &M);

    void SetupInit();

    void SetupTypes();

    void SetupConstants();

    void SetupGlobals();

    void SetupFunctions();

    void CollectInterestedLoopFunction();

    void SetupHooks();

    void InstrumentInit(Instruction *);

    void InstrumentHooks(Function *, bool isOptimized = true);

    void InstrumentWrite(StoreInst *, Instruction *);

    void InstrumentRead(LoadInst *, Instruction *);

    void InstrumentAlloc(Value *, Instruction *);

    void InstrumentCallBefore(Function *pFunction);

    void InstrumentReturn(Instruction *m);

    void InstrumentCostUpdater(Function *pFunction, bool isOptimized = true);

    void InstrumentRmsUpdater(Function *pFunction);

    void InstrumentRmsUpdater(Function *Callee, Instruction *pInst);

    void ProcessMemIntrinsic(MemIntrinsic *memInst);

    /* Module */
    Module *pModule;
    /* ********** */

    /* Type */
    IntegerType *IntType;
    IntegerType *LongType;
    Type *VoidType;
    PointerType *VoidPointerType;
    /* ********** */

    /* Function */
    // int aprof_init()
    Function *aprof_init;
    // void aprof_increment_cost()
    Function *aprof_increment_cost;
    // void aprof_increment_rms
    Function *aprof_increment_rms;
    // void aprof_write(void *memory_addr, unsigned int length)
    Function *aprof_write;
    // void aprof_read(void *memory_addr, unsigned int length)
    Function *aprof_read;
    // void aprof_call_before(char *funcName)
    Function *aprof_call_before;
    // void aprof_return()
    Function *aprof_return;
    /* ********** */

    /* Constant */
    ConstantInt *ConstantLong0;
    ConstantInt *ConstantLong1;
    /* ********** */

    /* Alloc Inst */
    AllocaInst *BBAllocInst;
    AllocaInst *RmsAllocInst;
    /* **** */

    /* OutPut File */
    ofstream funNameIDFile;
    /* */

};

#endif //COMAIR_LOOPINTERESTEDHOOK_H