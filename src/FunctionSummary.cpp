#include "FunctionSummary.hh"

void pdg::function_summary::_memcpySummary(void *dest, void *src, unsigned count, TreeNode &destParamTreeNode, TreeNode &srcParamTreeNode)
{
    unsigned libraryUpdateFields = 0;
    unsigned libraryReadFields = 0;
    // update all the dest tree fields to be written, no transitive fields
    TreeNode *destTreePointedObjNode = destParamTreeNode.getChildNodes()[0];
    auto destObjFieldNodes = destTreePointedObjNode->getChildNodes();
    for (auto fieldNode : destObjFieldNodes)
    {
        fieldNode->addAccessTag(AccessTag::DATA_WRITE);
        libraryUpdateFields++;
    }

    // update all the src tree fields to be read, no transitive fields
    TreeNode *srcTreePointedObjNode = srcParamTreeNode.getChildNodes()[0];
    auto srcObjFieldNodes = srcTreePointedObjNode->getChildNodes();
    for (auto fieldNode : srcObjFieldNodes)
    {
        fieldNode->addAccessTag(AccessTag::DATA_WRITE);
        libraryReadFields++;
    }
    // ksplit stats recording

}

void pdg::function_summary::_memsetSummary(void *ptr, int value, unsigned num, TreeNode &ptrTreeNode)
{
    // update all the set fields

    // ksplit stats recording
}
