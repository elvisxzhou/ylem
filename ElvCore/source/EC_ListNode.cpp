#include "EC_ListNode.h"

namespace ElvCore
{
    int ListNode::length(ListNode* list)
    {
        int len = 0;
        ListNode* t = list;
        while(t) { len++; t=t->next; }
        return len;
    }
    void ListNode::detach()
    {
        if(next)
            next->prev = prev;
        if(prev)
            prev->next = next;
    }

    void ListNode::insert(ListNode* node,bool back)
    {
        if(!node) { return; }

        if(back)
        {
            next = node->next;
            if(node->next)
                node->next->prev = this;

            prev = node;
            node->next = this;
        }
        else
        {
            prev = node->prev;
            if(node->prev)
                node->prev->next = this;

            this->next = node;
            node->prev = this;
        }
    }
}