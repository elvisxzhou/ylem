#ifndef EC_LISTNODE_H
#define EC_LISTNODE_H

namespace ElvCore
{
    class ListNode
    {
    public:
        ListNode() : prev(0),next(0) {}

        void detach();
        void insert(ListNode* node,bool back = true);
        static int length(ListNode* list);
            
    protected:
        ListNode* prev;
        ListNode* next;
    };
}

#endif