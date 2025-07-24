#include <stdio.h>
#include <stdlib.h>

// 结点的定义
struct Node {
    char data;
    int freq;
    struct Node* left;
    struct Node* right;
};

// 最小堆的定义
struct MinHeap {
    int size;
    int capacity;
    struct Node** array;
};

// 创建一个新的结点
struct Node* newNode(char data, int freq) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->freq = freq;
    node->left = node->right = NULL;
    return node;
}

// 创建一个包含给定容量的最小堆
struct MinHeap* createMinHeap(int capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct Node**)malloc(capacity * sizeof(struct Node*));
    return minHeap;
}

// 交换两个结点
void swapNodes(struct Node** a, struct Node** b) {
    struct Node* t = *a;
    *a = *b;
    *b = t;
}

// 最小堆的维护：自底向上
void minHeapifyUp(struct MinHeap* minHeap, int idx) {
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (minHeap->array[idx]->freq < minHeap->array[parent]->freq) {
            swapNodes(&minHeap->array[idx], &minHeap->array[parent]);
            idx = parent;
        } else {
            break;
        }
    }
}

// 最小堆的维护：自顶向下
void minHeapifyDown(struct MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq) {
        smallest = left;
    }

    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq) {
        smallest = right;
    }

    if (smallest != idx) {
        swapNodes(&minHeap->array[idx], &minHeap->array[smallest]);
        minHeapifyDown(minHeap, smallest);
    }
}

// 插入一个新结点到最小堆
void insertMinHeap(struct MinHeap* minHeap, struct Node* node) {
    minHeap->size++;
    int idx = minHeap->size - 1;
    minHeap->array[idx] = node;
    minHeapifyUp(minHeap, idx);
}

// 弹出最小堆的根结点
struct Node* extractMin(struct MinHeap* minHeap) {
    if (minHeap->size == 1) {
        minHeap->size--;
        return minHeap->array[0];
    }

    struct Node* root = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    minHeap->size--;

    minHeapifyDown(minHeap, 0);

    return root;
}

// 构建霍夫曼树
struct Node* buildHuffmanTree(char data[], int freq[], int size) {
    struct Node *left, *right, *top;

    // 创建一个最小堆，并将所有结点插入其中
    struct MinHeap* minHeap = createMinHeap(size);
    for (int i = 0; i < size; ++i) {
        insertMinHeap(minHeap, newNode(data[i], freq[i]));
    }

    // 构建霍夫曼树
    while (minHeap->size > 1) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;

        insertMinHeap(minHeap, top);
    }

    // 返回霍夫曼树的根结点
    return extractMin(minHeap);
}

// 打印字符的霍夫曼编码
void printCodes(struct Node* root, int arr[], int top) {
    if (root->left) {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }

    if (root->right) {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }

    if (!(root->left) && !(root->right)) {
        printf("%c: ", root->data);
        for (int i = 0; i < top; ++i) {
            printf("%d", arr[i]);
        }
        printf("\n");
    }
}

// 解码编码字符串
void decodeHuffman(struct Node* root, const char* encoded) {
    struct Node* current = root;
    printf("Decoded Message: ");
    for (int i = 0; encoded[i] != '\0'; ++i) {
        if (encoded[i] == '0') {
            current = current->left;
        } else {
            current = current->right;
        }

        if (!(current->left) && !(current->right)) {
            printf("%c", current->data);
            current = root;
        }
    }
    printf("\n");
}

int main() {
    char data[] = {'a', 'b', 'c', 'd', 'e'};
    int freq[] = {4, 7, 5, 2, 9};
    int size = sizeof(data) / sizeof(data[0]);

    // 构建霍夫曼树
    struct Node* root = buildHuffmanTree(data, freq, size);

    // 打印每个字符的霍夫曼编码
    int arr[100], top = 0;
    printCodes(root, arr, top);

    // 编码系列11000111000101011
    const char* encodedMessage = "11000111000101011";

    // 解码编码系列
    decodeHuffman(root, encodedMessage);

    return 0;
}
