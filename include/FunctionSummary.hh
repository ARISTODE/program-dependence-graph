#ifndef _FUNCTIONSUMMARY_H_
#define _FUNCTIONSUMMARY_H_
// this file implements the function summary for some library functions
#include "Tree.hh"

namespace pdg
{
    namespace function_summary
    {
        // memcpy
        void _memcpySummary(void *dest, void *src, unsigned count, TreeNode &destParamTreeNode, TreeNode &srcParamTreeNode);
        // memset
        void _memsetSummary(void *ptr, int value, unsigned num, TreeNode &ptrTreeNode);
    }
}

#endif