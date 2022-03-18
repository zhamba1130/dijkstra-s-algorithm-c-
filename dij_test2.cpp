#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <utility>          
#include <iomanip>          
#include <cmath>            

using namespace std;

class minHeap {
private:
    int size;
    int capacity;
    vector<int> heap;
    vector<int> node;// 紀錄element的位置
    int parent(int i) { return (i - 1) / 2; } 
    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }
public:
    minHeap(int capacity);
    void insert(int k);
    int extractMin();
    void heapify(int i);
    void decrease(int x, int k);
    void printHeap();
};

minHeap::minHeap(int capacity) {
    size = 0;
    this->capacity = capacity;
    heap.resize(capacity);
    node.resize(capacity);
}
void minHeap::insert(int k) {
    if (size == capacity) {
        cout << "MIN HEAP FULL" << endl;
        return;
    }

    size++;

    int i = size - 1;
    heap[i] = k;
    node[i] = i;

    while (i != 0 && heap[parent(i)] > heap[i]) {
        swap(heap[i], heap[parent(i)]);
        swap(node[i], node[parent(i)]);
        i = parent(i);
    }
}
void minHeap::heapify(int i) {
    int l_child = left(i);
    int r_child = right(i);
    int smallest = i;

    // Find the smallest element of the three
    if ((l_child < size) && (heap[l_child] < heap[smallest])) {
        smallest = l_child;
    }if ((r_child < size) && (heap[r_child] < heap[smallest])) {
        smallest = r_child;
    }

    //If the smallest of l or r, continue heapify
    if (smallest != i) {
        swap(heap[i], heap[smallest]);
        swap(node[i], node[smallest]);
        heapify(smallest);
    }
}
int minHeap::extractMin() {
    if (size == 0) {
        cout << "empty heap" << endl;
        return -1;
    }
    else if (size == 1) {
        size--;
        return heap[0];
    }
    else {
        // 記下現在的root
        int root = node[0];

        // 最後一個node移到root
        heap[0] = heap[size - 1];
        node[0] = node[size - 1];
        size--;
        heapify(0);

        // Return min element
        return root;
    }
}
void minHeap::decrease(int x, int k) {
    //先找到node現在在minHeap的哪個位置
    vector<int>::iterator it = find(node.begin(), node.end(), x);
    int index = distance(node.begin(), it);

    //往上檢查heap並修正
    heap[index] = k;
    while (index != 0 && heap[parent(index)] > heap[index]) {
        swap(heap[index], heap[parent(index)]);
        swap(node[index], node[parent(index)]);
        index = parent(index);
    }
}
void minHeap::printHeap() {
    int power = 0;
    int value = 1;
    for (int i = 0; i < size; i++) {
        if (i == value) {
            cout << endl;
            power += 1;
            value += (1 << power);
        }
        cout << heap[i] << "  ";
    }
    cout << endl;
    cout << "node: ";
    for (int j = 0;j < size;j++) {
        cout << node[j] << " ";
    }
    cout << endl;
}


class Shortest_Path {
private:
    int N, n;
    int max_damage;
    vector<list<pair<int, int>>> adjList;
    vector<int> poison, predecessor, distance;
    
public:
    Shortest_Path(string data);
    void MakeAdjacentList();
    void Dijkstra();        
    void Initialize();     
    void printArray(vector<int> array, int N);
    friend class minHeap;
    void ResultOutput();
};

Shortest_Path::Shortest_Path(string data) {
    // 讀檔
    ifstream ifs(data, ios::in);
    int cnt = 0;
    if (!ifs.is_open()) {
        cout << "Failed to open file.\n";
    }
    else {
        int node;
        while (ifs >> node) {
            if (cnt == 0) {
                n = node;     //第一行 矩陣邊長
                cnt += 1;
            }
            else {
                poison.push_back(node);     //依序存入每個點的damage數值
                cnt += 1;
            }
        }
        ifs.close();
    }
    ifs.close();

    N = n * n;       // node總數
    cout << n << " " << N << endl;
}
void Shortest_Path::Initialize() {
    max_damage = pow(1000, log10(n));
    
    // Initialize
    distance.resize(N);
    predecessor.resize(N);

    for (int i = 0; i < N; i++) {
        distance[i] = max_damage;
        predecessor[i] = -1;
    }
    distance[0] = poison[0];
}
void Shortest_Path::MakeAdjacentList() {
    adjList.resize(N);
    // 存放鄰接點的資訊
    for (int i = 0;i < N;i++) {
        if (i % n != n - 1) {  //除了最左排
            adjList[i].push_back(make_pair(i + 1, poison[i + 1])); //紀錄左接點
        }
        if (i % n != 0) {  //除了最右排
            adjList[i].push_back(make_pair(i - 1, poison[i - 1])); //紀錄右接點
        }
        if (i / n != 0) {  //除了最上排
            adjList[i].push_back(make_pair(i - n, poison[i - n])); //紀錄上接點
        }
        if (i / n != n - 1) {  //除了最下排
            adjList[i].push_back(make_pair(i + n, poison[i + n])); //紀錄下接點
        }
    }
    /*
    for (int i = 0;i < N;i++) {
        cout << i << ":" << endl;
        for (list<pair<int, int>>::iterator itr = adjList[i].begin(); itr != adjList[i].end(); itr++) {
            cout << "[" << (*itr).first << "," << (*itr).second << "] ";
        }
        cout << endl;
    }*/
}
void Shortest_Path::Dijkstra() {

    Initialize();
    MakeAdjacentList();

    // Construct a minHeap named openlist, then store distance data into it
    minHeap openlist(N);
    for (int i = 0;i < N;i++) {
        openlist.insert(distance[i]);
        //openlist.printHeap();
        //cout << endl;
    }

    while (distance[N - 1] == max_damage) {
        int min = openlist.extractMin();
        //openlist.printHeap();
        //cout << "extractMin: " << min << endl;

        for (list<pair<int, int>>::iterator itr = adjList[min].begin();itr != adjList[min].end(); itr++) {
            if (distance[(*itr).first] > distance[min] + (*itr).second) {
                distance[(*itr).first] = distance[min] + (*itr).second;
                predecessor[(*itr).first] = min;
                openlist.decrease((*itr).first, distance[(*itr).first]);
            }
        }
        // Print distance and predecessor
        /*cout << endl;
        cout << "\nprint predecessor:\n";
        printArray(predecessor, N);
        cout << "\nprint distance:\n";
        printArray(distance, N);
        cout << endl;*/
    }
}
void Shortest_Path::printArray(vector<int> array, int N) {
    for (int i = 0; i < N; i++) {
        cout << setw(4) << i;
    }
    cout << endl;
    for (int i = 0; i < N; i++) {
        cout << setw(4) << array[i];
    }
    cout << endl;
}
void Shortest_Path::ResultOutput(){
    vector<int> path;
    vector<string> directions;

    // 排列shortest path的順序
    path.push_back(N - 1);
    int p = N - 1;
    while (p != 0) {
        path.insert(path.begin(), predecessor[p]);
        p = predecessor[p];
    }

    // Print result
    for (int p = 0; p < path.size(); p++) {
        cout << path[p] << ",";
        if (p > 0) {
            int go = path[p] - path[p - 1];
            if (go == 1) {
                directions.push_back("R");
            }
            else if (go == -1) {
                directions.push_back("L");
            }
            else if (go == n) {
                directions.push_back("D");
            }
            else if (go == -n) {
                directions.push_back("U");
            }
        }
    }
    cout << endl;
    cout << distance[N - 1] << " " << path.size() << endl;
    for (int d = 0; d < directions.size(); d++) {
        cout << directions[d];
    }
}


int main() {

    string data_source = "C:/Users/johnny/Downloads/測資/input9";
    Shortest_Path hw(data_source);
    hw.Dijkstra();
    hw.ResultOutput();

    return 0;
}
