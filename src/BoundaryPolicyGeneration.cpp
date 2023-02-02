#include "BoundaryPolicyGeneration.hh"

using namespace llvm;
char pdg::BoundaryPolicyGeneration::ID = 0;


void pdg::BoundaryPolicyGeneration::getAnalysisUsage(AnalysisUsage &AU) const
{
  AU.addRequired<DataAccessAnalysis>();
  AU.setPreservesAll();
}

bool pdg::BoundaryPolicyGeneration::runOnModule(Module &M)
{
    _DDA = &getAnalysis<DataAccessAnalysis>();
    _PolicyFile.open("Policy.idl");
    for (auto &F : M)
    {
        if (F.isDeclaration())
            continue;
        generatePoliciesforFunc(F);
    }

    return false;
}

void pdg::BoundaryPolicyGeneration::generatePoliciesforFunc(Function &F)
{
    // generate policies for each boundary function
    auto fw = _DDA->getNescheckFuncWrapper(F);
    _PolicyFile << "policy for func " << F.getName().str() << ":\n";
    // generate projection for return value
    auto retArgTree = fw->getRetFormalInTree();
    if (retArgTree != nullptr && fw->getReturnValDIType() != nullptr)
        generatePoliciesForArgTree(*retArgTree, _PolicyFile, true);

    // generate projection for each argument
    auto argTreeMap = fw->getArgFormalInTreeMap();
    for (auto iter = argTreeMap.begin(); iter != argTreeMap.end(); iter++)
    {
        auto argTree = iter->second;
        if (argTree != nullptr)
            generatePoliciesForArgTree(*argTree, _PolicyFile);
    }
}

void pdg::BoundaryPolicyGeneration::generatePoliciesForArgTree(Tree &argTree, std::ofstream &outputFile, bool isRet)
{
    // for each arg tree, iterate through all the tree node (fields), generate policy for the corresponding field
    TreeNode *rootNode = argTree.getRootNode();
    DIType *rootNodeDIType = rootNode->getDIType();
    if (!rootNodeDIType)
        return;
    
    bool isPtrType = dbgutils::isPointerType(*rootNodeDIType);
    if (!isPtrType)
        return;
    // generate policy for arg
    std::string argName = rootNode->getSrcHierarchyName();
    if (isRet)
        outputFile << "\t(retPtr)"
                   << "\n"; // return value doesn't have name
    else
        outputFile << "\t(idx"
                   << ", " << argName << ")\n";

    std::queue<TreeNode *> nodeQueue;
    // process each node separately
    nodeQueue.push(rootNode);
    while (!nodeQueue.empty())
    {
        TreeNode *curNode = nodeQueue.front();
        nodeQueue.pop();
        generatePoliciesForTreeNode(*curNode, outputFile);
        for (auto childNode : curNode->getChildNodes())
        {
            nodeQueue.push(childNode);
        }
    }
}

std::set<Value *> pdg::BoundaryPolicyGeneration::computeStoreValuesForParamNode(TreeNode &paramTreeNode)
{
    std::set<Value *> storeValues;
    std::set<EdgeType> edgeTypes = {
        EdgeType::PARAMETER_IN,
        EdgeType::DATA_ALIAS};
    auto reachableNodes = _DDA->getPDG()->findNodesReachedByEdges(paramTreeNode, edgeTypes);
    for (auto node : reachableNodes)
    {
        auto nodeVal = node->getValue();
        if (!nodeVal)
            continue;
        for (auto user : nodeVal->users())
        {
            if (StoreInst *si = dyn_cast<StoreInst>(user))
                storeValues.insert(si->getValueOperand());
        }
    }
    return storeValues;
}

void pdg::BoundaryPolicyGeneration::generatePoliciesForTreeNode(TreeNode &paramTreeNode, std::ofstream &outputFile)
{
    // obtain read/write access to the node
    auto accTags = paramTreeNode.getAccessTags();
    bool isUpdated = (accTags.find(AccessTag::DATA_WRITE) != accTags.end());
    bool isRead = (accTags.find(AccessTag::DATA_READ) != accTags.end());
    std::string srcName = paramTreeNode.getSrcHierarchyName();
    DIType *DIType = paramTreeNode.getDIType();
    if (DIType == nullptr)
        return;
    bool isPtrType = dbgutils::isPointerType(*DIType);
    if (!isPtrType)
        return;

    auto fieldOffset = DIType->getOffsetInBits();
    auto size = DIType->getSizeInBits();
    /*
    generate writable policy
    1. check if the node is updated by module (driver)
    2. if ture, grant writable access based on the node's address
    e.g., writable(field_addr, size)
    */
    if (isUpdated)
        outputFile << "\t\t"
                   << "writable(&" << srcName << ", " << size << ");\n";

    /*
    generate readable policy
    1. check if the node is read by module (driver)
    2. if ture, grant readable access based on the node's address
    e.g., readable(field_addr, size)
    */
    if (isRead)
        outputFile << "\t\t"
                   << "readable(&" << srcName << ", " << size << ");\n";

    /*
    generate val_check policy
    1. check if the node is updated by module
    2. if ture, obtain the updated value to the node
    3. A few cases:
        a. if the node is a function ptr, check if the written address are module functions
        b. if the node is a ptr field, check if the updated addr are legit (e.g., driver globals)
        c. for addresses holding bounds information, check if the stored bound value is in the range
        d. other cases
    */
    if (isUpdated)
    {
        // compute all the values stored to the address represented by the node
        if (dbgutils::isPointerType(*DIType))
        {
            if (dbgutils::isFuncPointerType(*DIType))
            {
                outputFile << "\t\t"
                           << "val_check(&" << srcName
                           << ", DrvFuncAddrs)"
                           << "\n";
            }
            else
            {
                outputFile << "\t\t"
                           << "val_check(&" << srcName
                           << ", DrvLegalAddrs)"
                           << "\n";
            }
        }
    }
}

static RegisterPass<pdg::BoundaryPolicyGeneration>
    BPG("bpg", "Boundary policy generation", false, true);
