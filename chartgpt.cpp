#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <limits>
// #include <bits/stdc++.h>
using namespace std;

// 定義家庭結構
struct Family
{
    int id;         // 家庭 ID
    int arrival;    // 抵達時間（分鐘）
    int payment;    // 需支付金額
    int finishTime; // 完成報到時間（分鐘）
    int servedBy;   // 服務該家庭的機器人 ID
};

// 定義機器人結構
struct Robot
{
    int id;               // 機器人 ID
    int finishTime;       // 下一次可服務時間（分鐘）
    int tasks;            // 已完成服務家庭數
    int income;           // 累計收入
    int maintenanceCount; // 電池檢查次數（本例不觸發維修）
    bool busy;            // 是否忙碌
    bool dispatched;      // 是否已出場（首次派遣後設 true）
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Y, T;
    // 讀取第一行：機器人數量 N、報到次數上限 Y、模擬總分鐘數 T
    cin >> N >> Y >> T;
    cin.ignore();

    // 讀取 T 行，每行為該分鐘抵達的家庭資料，格式："familyID,payment"（以空格分隔）
    vector<Family> families;
    for (int minute = 1; minute <= T; minute++)
    {
        string line;
        getline(cin, line);
        if (line.empty())
            continue;
        stringstream ss(line);
        string token;
        while (ss >> token)
        {
            size_t commaPos = token.find(',');
            if (commaPos == string::npos)
                continue;
            Family f;
            f.id = stoi(token.substr(0, commaPos));
            f.payment = stoi(token.substr(commaPos + 1));
            f.arrival = minute; // 記錄抵達分鐘
            f.finishTime = -1;
            f.servedBy = -1;
            families.push_back(f);
        }
    }
    int totalFamilies = families.size();

    // 等待佇列：存放家庭在 families 向量中的索引（依抵達順序）
    queue<int> waiting;
    int nextFamilyIndex = 0;

    // repairQueue：存放尚未派遣的機器人，初始順序 0～N-1（FIFO）
    queue<int> repairQueue;
    for (int i = 0; i < N; i++)
    {
        repairQueue.push(i);
    }

    // 初始化機器人狀態，存入 vector<Robot>
    vector<Robot> robots(N);
    for (int i = 0; i < N; i++)
    {
        robots[i].id = i;
        robots[i].finishTime = 0; // 初始皆可立即派遣
        robots[i].tasks = 0;
        robots[i].income = 0;
        robots[i].maintenanceCount = 0;
        robots[i].busy = false;
        robots[i].dispatched = false;
    }

    int currentTime = 1;
    int servedFamilies = 0;

    // 分派輪次旗標，用來決定交替順序
    // 當有已出場的機器人可用時：
    //   若它們的 tasks 為偶數 → 遞增（從 0 到 N-1）
    //   若為奇數 → 遞減（從 N-1 到 0）
    // 如果沒有已出場的空閒機器人，則從 repairQueue 派遣新機器人（順序固定FIFO，即升冪）
    while (servedFamilies < totalFamilies)
    {
        // 1. 每分鐘加入該分鐘抵達的家庭到 waiting 佇列
        while (nextFamilyIndex < totalFamilies && families[nextFamilyIndex].arrival == currentTime)
        {
            waiting.push(nextFamilyIndex);
            nextFamilyIndex++;
        }

        // 2. 檢查所有機器人：若其 busy 為 true 且 finishTime == currentTime，則服務完成，設 busy = false
        for (int i = 0; i < N; i++)
        {
            if (robots[i].busy && robots[i].finishTime == currentTime)
            {
                robots[i].busy = false;

                // 若完成 Y 次需進維修
                if (robots[i].tasks % Y == 0 && robots[i].tasks != 0)
                {
                    robots[i].finishTime = currentTime + 1; // 維修花 1 分鐘
                    robots[i].maintenanceCount++;
                    robots[i].dispatched = false; // 暫時不算場外
                    repairQueue.push(i);          // 等維修完再出場
                }
            }

            // 檢查是否維修完成
            if (!robots[i].busy && !robots[i].dispatched && robots[i].finishTime == currentTime)
            {
                robots[i].dispatched = true; // 修完了，準備重新上場
            }
        }

        // 3. 準備分派：首先檢查是否有「已出場」(dispatched==true)且空閒的機器人
        bool hasDispatchedAvailable = false;
        // 我們透過迴圈檢查所有機器人，若有 dispatched==true 且 !busy 且 finishTime <= currentTime，即視為已出場可用
        for (int i = 0; i < N; i++)
        {
            if (robots[i].dispatched && !robots[i].busy && robots[i].finishTime <= currentTime)
            {
                hasDispatchedAvailable = true;
                break;
            }
        }

        // 4. 分派步驟
        // 如果有已出場的空閒機器人，則依照它們的 tasks 決定分派順序
        if (hasDispatchedAvailable)
        {
            // 先，根據所有已出場空閒機器人，假設它們同一分鐘完成服務，故 tasks 值相同。
            // 為了實作交替順序而不用 sort，我們分別用兩個迴圈：
            // 如果 tasks 為偶數，則從 0 到 N-1；若奇數，則從 N-1 到 0。
            // 假設至少一個已出場可用機器人的 tasks 為 X，則:
            int order = -1; // 0 表示升冪, 1 表示降冪
            for (int i = 0; i < N; i++)
            {
                if (robots[i].dispatched && !robots[i].busy && robots[i].finishTime <= currentTime)
                {
                    order = (robots[i].tasks % 2 == 0) ? 0 : 1;
                    break;
                }
            }
            // 根據 order 來依序檢查機器人並分派
            if (order == 0)
            { // 升冪
                for (int i = 0; i < N && !waiting.empty(); i++)
                {
                    if (robots[i].dispatched && !robots[i].busy && robots[i].finishTime <= currentTime)
                    {
                        int famIdx = waiting.front();
                        waiting.pop();
                        int procTime = 2; // 每次報到均耗時 2 分鐘
                        families[famIdx].finishTime = currentTime + procTime;
                        families[famIdx].servedBy = i;
                        robots[i].busy = true;
                        robots[i].finishTime = currentTime + procTime;
                        robots[i].tasks++;
                        robots[i].income += families[famIdx].payment;
                        servedFamilies++;
                    }
                }
            }
            else
            { // 降冪
                for (int i = N - 1; i >= 0 && !waiting.empty(); i--)
                {
                    if (robots[i].dispatched && !robots[i].busy && robots[i].finishTime <= currentTime)
                    {
                        int famIdx = waiting.front();
                        waiting.pop();
                        int procTime = 2;
                        families[famIdx].finishTime = currentTime + procTime;
                        families[famIdx].servedBy = i;
                        robots[i].busy = true;
                        robots[i].finishTime = currentTime + procTime;
                        robots[i].tasks++;
                        robots[i].income += families[famIdx].payment;
                        servedFamilies++;
                    }
                }
            }
        }
        else
        {
            // 若沒有已出場可用機器人，則從 repairQueue 派遣新機器人（順序固定 FIFO）
            while (!waiting.empty() && !repairQueue.empty())
            {
                int rid = repairQueue.front();
                repairQueue.pop();
                // 派遣該機器人（首次服務），服務耗時 2 分鐘
                int famIdx = waiting.front();
                waiting.pop();
                int procTime = 2;
                families[famIdx].finishTime = currentTime + procTime;
                families[famIdx].servedBy = rid;
                robots[rid].busy = true;
                robots[rid].finishTime = currentTime + procTime;
                robots[rid].tasks++;
                robots[rid].income += families[famIdx].payment;
                robots[rid].dispatched = true; // 標記該機器人已出場
                servedFamilies++;
            }
        }

        // 時間以每分鐘固定遞增
        currentTime++;
    }

    // --- 輸出結果 ---
    // 輸出機器人資訊（依機器人 ID 升冪）
    cout << "Robots' information:" << "\n";
    for (int i = 0; i < N; i++)
    {
        cout << "ID: " << robots[i].id << ", "
             << robots[i].tasks << " families, "
             << robots[i].income << " dollars, "
             << robots[i].maintenanceCount << " battery checks";
        if (i != N - 1)
            cout << " \n";
    }
    cout << "\n";

    // 輸出家庭資訊（僅輸出已完成服務的家庭），依家庭 ID 升冪
    cout << "Families' information:" << "\n\n";
    // 因為家庭的 ID 在輸入時已正確給出，所以依 vector 順序輸出即可
    for (auto &f : families)
    {
        if (f.finishTime != -1)
            cout << "ID: " << f.id << " completed by Robot "
                 << f.servedBy << " at minute " << f.finishTime << "\n";
    }

    return 0;
}
