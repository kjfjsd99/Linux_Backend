#include <iostream>
#include <vector>
#include <string>

using namespace std;

void parserCmd(vector<string> &tokens, vector<vector<string>> &cmd) {

    // tokens：已經切好的一個一個文字
    // 例如 {"ls", "-l", "|", "grep", "txt"}

    // cmd：最後要把整理好的「一串一串指令」放進這裡

    vector<string> oneCmd;
    // oneCmd：暫時拿來裝「目前正在處理的這一個指令」

    tokens.push_back("|");
    // 在 tokens 最後面硬塞一個 "|"
    // 確保最後一個指令也一定會被存進 cmd

    for (const auto &token : tokens) {

        // 把 tokens 裡的東西，一個一個拿出來看

        if (token != "|") {

            // 如果目前看到的不是 "|"
            oneCmd.push_back(token);

            // 把它放進目前正在收集的指令 oneCmd 裡

            continue;
            // 這個 token 處理完了
            // 直接去看下一個 token
        }

        // 走到這裡，代表目前看到的是 "|"

        if (oneCmd.size() > 0) {

            // 確認 oneCmd 裡面有沒有東西

            cmd.push_back(oneCmd);
            // 把整個 oneCmd 存進 cmd
            // 代表這一個指令收集完成

            oneCmd.clear();
            // 清空 oneCmd
            // 準備收集下一個指令
        }
    }
}


int main() {

    // 假設這是前面 tokenizer 已經切好的結果
    vector<string> tokens = {
        "ls",
        "-l",
        "|",
        "grep",
        "txt"
    };

    // 用來存 parserCmd() 整理好的結果
    vector<vector<string>> cmd;

    // 呼叫 parserCmd()
    parserCmd(tokens, cmd);

    // 印出結果
    cout << "Parsed commands:" << endl;

    for (const auto &oneCmd : cmd) {

        cout << "Command: ";

        for (const auto &token : oneCmd) {
            cout << "[" << token << "] ";
        }

        cout << endl;
    }

    return 0;
}