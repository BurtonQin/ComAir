#include "llvm/Analysis/PostDominators.h"
#include "llvm/IR/CallSite.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/MDBuilder.h"

#include "Common/Constant.h"
#include "Common/Helper.h"

using namespace llvm;
using namespace std;


int GetFunctionID(Function *F) {

    if (F->begin() == F->end()) {
        return -1;
    }

    BasicBlock *EntryBB = &(F->getEntryBlock());

    if (EntryBB) {

        for (BasicBlock::iterator II = EntryBB->begin(); II != EntryBB->end(); II++) {
            Instruction *Inst = &*II;
            MDNode *Node = Inst->getMetadata("func_id");
            if (!Node) {
                continue;
            }
            assert(Node->getNumOperands() == 1);
            const Metadata *MD = Node->getOperand(0);
            if (auto *MDV = dyn_cast<ValueAsMetadata>(MD)) {
                Value *V = MDV->getValue();
                ConstantInt *CI = dyn_cast<ConstantInt>(V);
                assert(CI);
                return CI->getZExtValue();
            }
        }
    }

    return -1;
}

int GetBasicBlockID(BasicBlock *BB) {

    if (BB->begin() == BB->end()) {
        return -1;
    }

    for (BasicBlock::iterator II = BB->begin(); II != BB->end(); II++) {
        Instruction *I = &*II;

        MDNode *Node = I->getMetadata("bb_id");
        if (!Node) {
            continue;
        }

        assert(Node->getNumOperands() == 1);
        const Metadata *MD = Node->getOperand(0);
        if (auto *MDV = dyn_cast<ValueAsMetadata>(MD)) {
            Value *V = MDV->getValue();
            ConstantInt *CI = dyn_cast<ConstantInt>(V);
            assert(CI);
            return CI->getZExtValue();
        }
    }

    return -1;
}

int GetInstructionID(Instruction *II) {

    MDNode *Node = II->getMetadata("ins_id");
    if (!Node) {
        return -1;
    }

    assert(Node->getNumOperands() == 1);
    const Metadata *MD = Node->getOperand(0);
    if (auto *MDV = dyn_cast<ValueAsMetadata>(MD)) {
        Value *V = MDV->getValue();
        ConstantInt *CI = dyn_cast<ConstantInt>(V);
        assert(CI);
        return CI->getZExtValue();
    }

    return -1;
}

int GetInstructionInsertFlag(Instruction *II) {

    MDNode *Node = II->getMetadata(APROF_INSERT_FLAG);
    if (!Node) {
        return -1;
    }

    assert(Node->getNumOperands() == 1);
    const Metadata *MD = Node->getOperand(0);
    if (auto *MDV = dyn_cast<ValueAsMetadata>(MD)) {
        Value *V = MDV->getValue();
        ConstantInt *CI = dyn_cast<ConstantInt>(V);
        assert(CI);
        return CI->getZExtValue();
    }

    return -1;
}

bool getIgnoreFlag(Function *F) {

    if (F->begin() == F->end()) {
        return true;
    }

    BasicBlock *entryBB = &*(F->begin());
    if (entryBB) {

        Instruction *II = &*(entryBB->getFirstInsertionPt());
        MDNode *Node = II->getMetadata(IGNORE_FUNC_FLAG);

        if (!Node) {
            return false;
        }

        return true;
    }

    return false;

}

bool IsIgnoreFunc(Function *F) {

    if (!F) {
        return true;
    }

    if (getIgnoreFlag(F)) {
        return true;
    }

    if (F->getSection().str() == ".text.startup") {
        return true;
    }

    std::string FuncName = F->getName().str();

    if (FuncName == "JS_Assert") {
        return true;
    }

    if (FuncName.substr(0, 5) == "aprof") {
        return true;
    }

    int FuncID = GetFunctionID(F);

    if (FuncID < 0) {

        return true;
    }

    return false;
}


bool IsClonedFunc(Function *F) {

    if (!F) {
        return false;
    }

    std::string funcName = F->getName().str();

    // FIXME::
    if (funcName == "main") {
        return true;
    }

    if (funcName.length() > 7 &&
        funcName.substr(0, 7) == CLONE_FUNCTION_PREFIX) {
        return true;
    }

    return false;

}

int GetBBCostNum(BasicBlock *BB) {

    MDNode *Node;

    for (BasicBlock::iterator II = BB->begin(); II != BB->end(); II++) {

        Instruction *Inst = &*II;
        MDNode *Node = Inst->getMetadata(BB_COST_FLAG);
        if (!Node) {
            continue;
        }

        assert(Node->getNumOperands() == 1);
        const Metadata *MD = Node->getOperand(0);
        if (auto *MDV = dyn_cast<ValueAsMetadata>(MD)) {
            Value *V = MDV->getValue();
            ConstantInt *CI = dyn_cast<ConstantInt>(V);
            assert(CI);
            return CI->getZExtValue();
        }
    }

    return -1;

}
