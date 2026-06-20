### Winsock TCP 雙人連線 1A2B 猜數字遊戲
專案介紹

本專案為使用 C++ 與 Winsock2 API 開發之雙人連線 1A2B 猜數字遊戲。

專案採用 TCP Socket Client-Server 架構，由 Server 統一管理玩家連線、遊戲狀態與訊息傳遞，Client 負責接收玩家輸入與顯示遊戲結果。

本專案開發目的為學習：

TCP Socket 通訊
Client-Server 架構設計
網路程式設計
狀態機（State Machine）設計
多玩家同步控制
開發環境
項目	內容
開發語言	C++
編譯器	MinGW g++
作業系統	Windows
網路函式庫	Winsock2 API
通訊協定	TCP
系統架構
Player 1
   |
 TCP
   |
Server
├─ Connection Manager
├─ Game State Manager
└─ Result Dispatcher
   |
 TCP
   |
Player 2
### 模組說明
Connection Manager

負責：

玩家連線建立
Socket 管理
玩家加入判定
Game State Manager

負責：

遊戲流程控制
回合同步
狀態轉換
Result Dispatcher

負責：

結果計算
勝負判定
訊息轉發
遊戲流程
玩家連線
    ↓
等待第二位玩家
    ↓
遊戲開始
    ↓
Player Guess
    ↓
Server 判定
    ↓
結果回傳
    ↓
是否猜中？
 ├─ 否 → 下一回合
 └─ 是 → 遊戲結束
狀態機設計（State Machine）

為避免雙方玩家回合同步錯亂，本專案採用狀態機控制遊戲流程。

Waiting
   ↓
Guessing
   ↓
Result
   ↓
Game Over
### 狀態說明
狀態	功能
Waiting	等待玩家輸入
Guessing	進行猜測
Result	回傳結果
Game Over	結束遊戲
畫面截圖
### Server 監聽畫面
<img width="865" height="314" alt="image" src="https://github.com/user-attachments/assets/81a69261-ce11-4415-8ab1-684c9926e9ef" />


### Client 對戰畫面
<img width="865" height="274" alt="image" src="https://github.com/user-attachments/assets/7f289e02-1a20-41a5-96cc-80966459ea95" />


### 技術挑戰
問題一：玩家回合同步

開發初期發現：

玩家 A 已完成猜測
玩家 B 尚未收到最新狀態

導致：

回合順序錯亂
勝負判定異常
解決方法

透過 State Machine 設計：

Waiting
Guessing
Result
Game Over

由 Server 統一管理狀態轉移。

成功解決雙方同步問題。

問題二：TCP 通訊流程管理

TCP 為連線導向協定。

開發過程中必須管理：

Socket 建立
連線監聽
訊息收發
斷線處理

藉此學習完整 Client-Server 通訊流程。

學習收穫

透過本專案，我學習到：

網路程式設計
TCP Socket
Winsock2 API
Client-Server 架構
軟體工程
狀態機設計
模組化架構
除錯能力
自主學習能力
查閱英文技術文件
解決網路同步問題
GitHub 專案管理
GitHub 專案資訊

開發時間：

約 10 週

專案類型：

TCP Socket Client-Server Game

開發者：

林庭右
