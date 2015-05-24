// http://stackoverflow.com/questions/19108737/java-how-to-implement-a-shift-cipher-caesar-cipher

#include <iostream>
#include <string>

using namespace std;

string generate(const string& input, int k)
{
    k = k % 26;
    if (k < 0) k = 26 + k;

    string result(input.size(), 0);
    for (int i = 0; i < input.size(); ++i) {
        if (input[i] + k > 'z') result[i] = input[i] + k - 26;
        else result[i] = input[i] + k;
    }
    return result;
}

int main()
{
    cout << generate("abc", 1) << endl;
    cout << generate("abc", 3) << endl;
    cout << generate("abc", -1) << endl;
    cout << generate("abc", -3) << endl;

    cout << generate("abc", 26) << endl;
    cout << generate("abc", -26) << endl;
    cout << generate("abc", 29) << endl;
    cout << generate("abc", -29) << endl;

    return 0;
}
