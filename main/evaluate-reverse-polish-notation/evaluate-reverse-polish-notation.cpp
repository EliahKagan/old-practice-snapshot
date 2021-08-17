namespace {
    const unordered_map<string, function<int(int,int)>> operators {
        {"+", plus<int>{}},
        {"-", minus<int>{}},
        {"*", multiplies<int>{}},
        {"/", divides<int>{}}
    };

    const auto no_operator = end(operators);
}

class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> operands;

        for (const auto& tok : tokens) {
            const auto p = operators.find(tok);

            if (p == no_operator) operands.push(stoi(tok));
            else {
                const auto arg2 = operands.top();
                operands.pop();
                const auto arg1 = operands.top();
                operands.pop();
                operands.push((p->second)(arg1, arg2));
            }
        }

        if (operands.size() != 1u)
            throw invalid_argument{"formula is ill-formed"};

        return operands.top();
    }
};
