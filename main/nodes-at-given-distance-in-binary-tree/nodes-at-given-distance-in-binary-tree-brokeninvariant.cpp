// Various operations were extracted into their own functions, which is
// how popAndReturn() came into being.
//
// The action and paths stacks always needed to be the same size.
// An assertion outside popAndReturn() identified this broken invariant.
//
// But when precondition and postcondition assertions were added to the
// individual functions, including popAndReturn(), they did not find
// the bug in popAndReturn()!
//
// :)

inline bool popAndReturn(stack<NextAction>& actions, stack<node*> path)
{
    actions.pop();
    path.pop();
    return !path.empty(); // done if the stack is empty
}
