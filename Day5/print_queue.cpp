#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

bool isNum(char c) {
    return '0' <= c && c <= '9';
}

int toNum(char c) {
    return c-'0';
}

int parseNum(int &i, string line) {
    int val = 0;
    while (i < line.length() && isNum(line[i])) {
        val = val*10+toNum(line[i]);
        i++;
    }
    return val;
}

class Rule {
public:
    int precedent;
    int subsequent;
};

vector<int> fixPageUpdate(vector<int> pageUpdate, vector<Rule> rules) {
    if (pageUpdate.size() == 0) {
        return pageUpdate;
    }

    else {
        vector<int> correctedPageUpdate;
        vector<int> leftPages;
        vector<int> rightPages;
        int val = pageUpdate[0];
        for(int i=1; i<pageUpdate.size(); i++) {
            bool added=false;
            for (int k=0; k<rules.size(); k++) {
                if (!added && val == rules[k].precedent && pageUpdate[i] == rules[k].subsequent) {
                    added=true;
                    rightPages.push_back(pageUpdate[i]);
                }
                else if (!added && val == rules[k].subsequent && pageUpdate[i] == rules[k].precedent) {
                    added=true;
                    leftPages.push_back(pageUpdate[i]);
                }
            }
            if (!added) {
                rightPages.push_back(pageUpdate[i]);
            }
        }

        rightPages = fixPageUpdate(rightPages, rules);
        leftPages = fixPageUpdate(leftPages, rules);

        for (int i=0; i<leftPages.size(); i++) {
            correctedPageUpdate.push_back(leftPages[i]);
        }
        correctedPageUpdate.push_back(val);
        for (int i=0; i<rightPages.size(); i++) {
            correctedPageUpdate.push_back(rightPages[i]);
        }

        return correctedPageUpdate;
    }
}

int main() {
    string fname = "input.txt";
    ifstream inputFile;
    inputFile.open(fname);
    string line;
    vector<Rule> rulesBase;

    int midPageSum=0;
    int midPageReorderedSum=0;

    while (getline(inputFile, line) && line.length() > 0) {
        Rule newRule;
        int i=0;
        newRule.precedent = parseNum(i, line);
        i++;
        newRule.subsequent = parseNum(i, line);
        rulesBase.push_back(newRule);
    }

    while (getline(inputFile, line)) {
        vector<int> pageUpdate;
        for (int i=0; i<line.length(); i++) {
            int page = parseNum(i, line);
            pageUpdate.push_back(page);
        }

        vector<Rule> tempRules;
        // set the active rules based on pages to be updated
        for (int i=0; i < pageUpdate.size()-1; i++) {
            for (int j=i+1; j<pageUpdate.size(); j++) {
                for (int k=0; k<rulesBase.size(); k++) {
                    if (rulesBase[k].precedent == pageUpdate[i] && rulesBase[k].subsequent == pageUpdate[j]) {
                        Rule newRule;
                        newRule.precedent = rulesBase[k].precedent;
                        newRule.subsequent = rulesBase[k].subsequent;
                        tempRules.push_back(newRule);
                    }
                    else if (rulesBase[k].precedent == pageUpdate[j] && rulesBase[k].subsequent == pageUpdate[i]) {
                        Rule newRule;
                        newRule.precedent = rulesBase[k].precedent;
                        newRule.subsequent = rulesBase[k].subsequent;
                        tempRules.push_back(newRule);
                    }
                }
            }
        }

        // Part 1
        bool allRulesValid = true;
        for (int i=0; i<pageUpdate.size() && allRulesValid; i++) {
            for (int j=0; j<pageUpdate.size() && allRulesValid; j++) {
                for (int k=0; k<tempRules.size() && allRulesValid; k++) {
                    if (i < j) {
                        for (int k = 0; k < tempRules.size() && allRulesValid; k++) {
                            if (tempRules[k].subsequent == pageUpdate[i] && tempRules[k].precedent == pageUpdate[j]) {
                                allRulesValid = false;
                            }
                        }
                    }
                }
            }
        }

        if (allRulesValid) {
            midPageSum += pageUpdate[pageUpdate.size()/2];
        }
        else {
            // Part 2
            vector<int> correctedPageUpdate = fixPageUpdate(pageUpdate, tempRules);
            midPageReorderedSum += correctedPageUpdate[correctedPageUpdate.size()/2];
        }
    }

    cout << "Part 1: Mid page sum = " << midPageSum << endl;

    cout << "Part 2: Corrected mid page sum = " << midPageReorderedSum << endl;

    return 0;
}
