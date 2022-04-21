#include <iostream>
#include <vector>

using namespace std;

vector<int> lpsvFunction(string p)
{
    int n = p.length(), i = 1, j = 0;
    vector<int> lpsv(n, 0);
    
    while(i < n)
    {
        if(p[i] == p[j])
        {
            lpsv[i] = j + 1;
            i++;
            j++;
        }

        else
        {
            if(j == 0)
            {
                lpsv[i] = 0;
                i++;
            }
            else j = lpsv[j - 1];
        }
    }

    return lpsv;
}

vector<int> kmpAlgorithm(string text, string pattern)
{
    vector<int> posMatch;
    vector<int> lpsv = lpsvFunction(pattern);
    int i = 0, j = 0, n = text.length(), m = pattern.length();

    for(int a = 0; a < m; a++)
    {
        cout << "[" << a << "] = " << lpsv[i] << endl;
    }

    while(i < n)
    {
        if(text[i] == pattern[j])
        {
            i++;
            j++;
            if(j == m)
            {
                posMatch.push_back(i - m);
                j = lpsv[j - 1];
            }
        }

        else
        {
            if(j == 0) i++;
            else j = lpsv[j - 1];
        }
    }

    return posMatch;
}

int main()
{
    string text, pattern;
    cin >> text >> pattern;

    vector<int> posMatch = kmpAlgorithm(text, pattern);

    if(posMatch.size() == 0) cout << "No match" << endl;
    else
    {
        for(int i = 0; i < posMatch.size(); i++) cout << posMatch[i] << endl;
    }
}