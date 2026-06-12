#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

using namespace std;

string checkAB(string answer, string guess) {
    int a = 0, b = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (guess[i] == answer[j]) {
                if (i == j) a++;
                else b++;
            }
        }
    }
    return to_string(a) + "A" + to_string(b) + "B";
}

int main() {
    // Linux 不需要 WSAStartup

    int serverSock = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSock < 0) {
        cout << "Socket creation failed." << endl;
        return 1;
    }

    // 允許重複使用 Port，避免重啟時被鎖死
    int opt = 1;
    setsockopt(serverSock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8888);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        cout << "Bind failed." << endl;
        return 1;
    }

    listen(serverSock, 2);
    cout << "Server Online (Linux). Waiting for 2 players..." << endl;

    int players[2];
    string opponentAnswers[2];

    for (int i = 0; i < 2; i++) {
        players[i] = accept(serverSock, NULL, NULL);
        cout << "Player " << i + 1 << " joined." << endl;
        send(players[i], "SET_SECRET", 10, 0);
        char buf[1024] = {0};
        recv(players[i], buf, 1024, 0);
        opponentAnswers[i] = string(buf);
    }

    int turn = 0;
    while (true) {
        int cur = turn % 2;
        int target = (turn + 1) % 2;

        send(players[cur], "YOUR_TURN", 9, 0);
        send(players[target], "WAIT", 4, 0);

        char buf[1024] = {0};
        if (recv(players[cur], buf, 1024, 0) <= 0) break;

        string guess(buf);
        string result = checkAB(opponentAnswers[target], guess);
        string msg = "Player " + to_string(cur + 1) + " guessed " + guess + " -> " + result + "\n";
        
        send(players[0], msg.c_str(), (int)msg.length(), 0);
        send(players[1], msg.c_str(), (int)msg.length(), 0);

        if (result == "4A0B") {
            send(players[cur], "WIN", 3, 0);
            send(players[target], "LOSE", 4, 0);
            break;
        }
        turn++;
    }

    close(players[0]); 
    close(players[1]); 
    close(serverSock);
    return 0;
}