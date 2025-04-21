#include <iostream>
#include <queue>
#include <omp.h>
using namespace std;

class Node {
public:
    int data;
    Node *left = nullptr, *right = nullptr;
};

Node* insert(Node* root, int data) {
    if (!root) {
        root = new Node{data};
        return root;
    }

    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* temp = q.front();
        q.pop();

        if (!temp->left) {
            temp->left = new Node{data};
            return root;
        } else q.push(temp->left);

        if (!temp->right) {
            temp->right = new Node{data};
            return root;
        } else q.push(temp->right);
    }
    return root;
}

void bfs(Node* root) {
    if (!root) return;
    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        int size = q.size();
        #pragma omp parallel for
        for (int i = 0; i < size; ++i) {
            Node* curr;
            #pragma omp critical
            {
                curr = q.front();
                q.pop();
                cout << curr->data << "\t";
            }
            #pragma omp critical
            {
                if (curr->left) q.push(curr->left);
                if (curr->right) q.push(curr->right);
            }
        }
    }
}

int main() {
    Node* root = nullptr;
    int data;
    char ch;
    do {
        cout << "Enter data: ";
        cin >> data;
        root = insert(root, data);
        cout << "Insert more? (y/n): ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');

    cout << "\nBFS Traversal:\n";
    bfs(root);
    return 0;
}
