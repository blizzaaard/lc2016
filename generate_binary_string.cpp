#include <iostream>
#include <string>
#include <vector>

using namespace std;

void print(const vector<string>& result)
{
    for (int i = 0; i < result.size(); ++i) {
        cout << result[i] << endl;
    }
}

void helper(vector<string>& result,
            const string&   path,
            const string&   input,
            int             index)
{
    if (index == input.size()) {
        result.push_back(path);
        return;
    }
    if ('?' == input[index]) {
        helper(result, path + '1', input, index + 1);
        helper(result, path + '0', input, index + 1);
    } else {
        helper(result, path + input[index], input, index + 1);
    }
}

vector<string> generate(const string& input)
{
    vector<string> result;
    helper(result, "", input, 0);
    return result;
}

int main()
{
    print(generate("01?01???10"));
    return 0;
}
