namespace {
    node* get_mid(node* head)
    {
        for (auto fast = head; fast != nullptr && fast->next != nullptr;
                               fast = fast->next->next)
            head = head->next;
        
        return head;
    }

    node* join(node* fst, node* snd)
    {
        if (fst == nullptr) return snd;
        
        while (fst->next != nullptr) fst = fst->next;
        fst->next = snd;
        return fst;
    }
}
