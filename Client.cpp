#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

using namespace std;

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) return 1;

    sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(8888);

    string ip;
    cout << "Enter Server IP (Codespaces Local: 127.0.0.1): ";
    cin >> ip;
    servAddr.sin_addr.s_addr = inet_addr(ip.c_str());

    if (connect(sock, (struct sockaddr*)&servAddr, sizeof(servAddr)) < 0) {
        cout << "Connection Failed!" << endl;
        return 1;
    }

    char buffer[1024];
    while (true) {
        memset(buffer, 0, 1024);
        int len = recv(sock, buffer, 1024, 0);
        if (len <= 0) break;

        string status(buffer);
        if (status == "SET_SECRET") {
            cout << "Set your 4-digit secret for opponent: ";
            string secret; cin >> secret;
            send(sock, secret.c_str(), (int)secret.length(), 0);
        } else if (status == "YOUR_TURN") {
            cout << "Your turn to guess: ";
            string guess; cin >> guess;
            send(sock, guess.c_str(), (int)guess.length(), 0);
        } else if (status == "WAIT") {
            cout << "Waiting for opponent..." << endl;
        } else if (status == "WIN") {
            cout << "CONGRATS! YOU WON!" << endl; break;
        } else if (status == "LOSE") {
            cout << "GAME OVER! Opponent cracked your code first." << endl; break;
        } else {
            cout << status;
        }
    }
    close(sock);
    return 0;
}