#include "AnalysisState.hpp"

namespace NesCheck { 

int _safeptrscount, _seqptrscount, _dynptrscount, _hasmetadatatableentrycount;
llvm::Type* sizetype;

AnalysisState::AnalysisState() {}

void AnalysisState::SetSizeType(llvm::Type* st) {
    sizetype = st;
}

void AnalysisState::RegisterFunction(Function* func) {
    numFunctions++;
}

void AnalysisState::RegisterVariable(const VariableMapKeyType *Decl) {
    if (Variables.count(Decl)) return;
    Variables[Decl].classification = VariableStates::Safe;
    Variables[Decl].size = llvm::ConstantInt::get(sizetype, 0);
    // errs() << GREEN << "\t=>(Register) Classified " << getIdentifyingName(Decl) << " as SAFE" << NORMAL << "\n";
}

std::string AnalysisState::ClassifyPointerVariable(const VariableMapKeyType* Decl, VariableStates ptrType) {
    RegisterVariable(Decl);
//    errs()<< GREEN <<"\t=> Current Classification: "<< PtrTypeToString(Variables[Decl].classification) <<"\n";
//    errs() << GREEN <<"Trying to classsify this to "<<PtrTypeToString(ptrType)<<"\n";
    std::string ptrTypeName = PtrTypeToString(ptrType);
    if (Variables[Decl].classification < ptrType) {
        Variables[Decl].classification = ptrType;
        if(Variables[Decl].isGlobal)
            Variables[Decl].didClassificationChange = true;
        // errs() << GREEN << "\t=> Classified " << getIdentifyingName(Decl) << " as " << ptrTypeName << NORMAL << "\n";
    } else {
        // errs() << GRAY << "\t=> Ignored classification of " << getIdentifyingName(Decl) << " as " << ptrTypeName << NORMAL << "\n";
    }
    return ptrTypeName;
}
VariableInfo * AnalysisState::SetSizeForPointerVariable(const VariableMapKeyType* Decl, Value *size) {
    RegisterVariable(Decl);
    if (size == NULL) {
        // Variables[Decl].hasSize = false;
        Variables[Decl].size = llvm::ConstantInt::get(sizetype, 0);
    } else {
        // Variables[Decl].hasSize = true;
        Variables[Decl].size = size;
    }
    // errs() << GREEN << "\t=> Size of " << getIdentifyingName(Decl) << " set to " << *(Variables[Decl].size) << NORMAL << "\n";
    return &(Variables[Decl]);
}
void AnalysisState::SetExplicitSizeVariableForPointerVariable(const VariableMapKeyType *Decl, Value *explicitSize) {
    RegisterVariable(Decl);
    Variables[Decl].hasExplicitSizeVariable = (explicitSize != NULL);
    Variables[Decl].explicitSizeVariable = explicitSize;
    // errs() << GREEN << "\t=> Explicit size variable for " << getIdentifyingName(Decl) << " set to " << *(Variables[Decl].explicitSizeVariable) << NORMAL << "\n";
}

void AnalysisState::SetInstantiatedExplicitSizeVariable(const VariableMapKeyType *Ref, bool v) {
    RegisterVariable(Ref);
    Variables[Ref].instantiatedExplicitSizeVariable = v;
}

void AnalysisState::SetHasMetadataTableEntry(const VariableMapKeyType *Ref) {
    RegisterVariable(Ref);
    Variables[Ref].hasMetadataTableEntry = true;
}

VariableInfo * AnalysisState::GetPointerVariableInfo(VariableMapKeyType *Decl) {
    // errs() << GRAY << "\tGetting VarInfo for " << getIdentifyingName(Decl) << "... ";
    if (isa<ConstantPointerNull>(Decl)) {
        // errs() << "ConstantPointer NULL type creating new temp variable info.\n" << NORMAL;
        VariableInfo* info = new VariableInfo;
        //Attempted BUG FIX - ENUM ISSUE ( NEW STRUCT VARIABLE WITH DEFAULT ENUM VALUE WILL APPARENTLY LEAD TO UNDEFINED BEHAVIOUR)
        info->classification = VariableStates::Unknown;
        info->size = llvm::ConstantInt::get(sizetype, 0);
        return info;
    }
    if (Variables.count(Decl)) {
        // errs() << "found.\n" << NORMAL;
        return &(Variables[Decl]);
    }
    // errs() << RED << "NOT FOUND!\n" << NORMAL;
    return NULL;
}

std::string AnalysisState::GetVariablesStateAsString() {
    std::stringstream SS;

    int tot;
    _safeptrscount = _seqptrscount = _dynptrscount = _hasmetadatatableentrycount = 0;
    tot = Variables.size();

    SS << "Found " << numFunctions << " functions.\n";
    SS << "Found " << tot << " pointer variables:\n";

    for (auto iter = Variables.begin(); iter != Variables.end(); ++iter) {
        if (iter->second.classification == VariableStates::Safe) _safeptrscount++;
        else if (iter->second.classification == VariableStates::Seq) _seqptrscount++;
        else if (iter->second.classification == VariableStates::Dyn) _dynptrscount++;


        if (iter->second.hasMetadataTableEntry) _hasmetadatatableentrycount++;
    }
    SS << "-->) TOTAL Safe pointer variables:\t" << _safeptrscount << " (" << (tot > 0 ? _safeptrscount * 1.0 / tot : 0) * 100 << "%)\n";
    SS << "-->) TOTAL Seq pointer variables:\t" << _seqptrscount << " (" << (tot > 0 ? _seqptrscount * 1.0 / tot : 0) * 100 << "%)\n";
    SS << "-->) TOTAL Dyn pointer variables:\t" << _dynptrscount << " (" << (tot > 0 ? _dynptrscount * 1.0 / tot : 0) * 100 << "%)\n";
    SS << "\n";

    return SS.str();
}

int AnalysisState::GetSafePointerCount() {
    return _safeptrscount;
}
int AnalysisState::GetSeqPointerCount() {
    return _seqptrscount;
}
int AnalysisState::GetDynPointerCount() {
    return _dynptrscount;
}
int AnalysisState::GetHasMetadataTableEntryCount() {
    return _hasmetadatatableentrycount;
}

}
