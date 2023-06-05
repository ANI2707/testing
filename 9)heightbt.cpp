#include<iostream>
#include<queue>

using namespace std;

class Node {
private:
	int key;
	string value;
	int height;
	Node* left;
	Node* right;
public:
	Node(int k, const string& v) {
		key = k;
		value = v;
		height = 1;
		left = NULL;
		right = NULL;
	}
	int Height(Node*);
	int balanceFactor(Node*);
	void updateHeight(Node*);
	Node* rotateLeft(Node*);
	Node* rotateRight(Node*);
	Node* rotateRightLeft(Node*);
	Node* rotateLeftRight(Node*);
	Node* balance(Node*);
	Node* insert(Node*, int, const string&);
	bool search(Node*, int);
	void inorderTraversal(Node*);
	void levelTraversal(Node*);
};

int Node :: Height(Node* node) {
	if(!node)
		return 0;
	return node->height;
}

int Node :: balanceFactor(Node* node) {
	if(!node)
		return 0;
	return Height(node->left) - Height(node->right);
}

void Node :: updateHeight(Node* node) {
	node->height = 1 + max(Height(node->left), Height(node->right));
}

Node* Node :: rotateLeft(Node* node) {
	cout<<"------LL Rotation Applied-------"<< endl;

	Node* newRoot = node->right;
	node->right = newRoot->left;
	newRoot->left = node;
	updateHeight(node);
	updateHeight(newRoot);
	return newRoot;
}

Node* Node :: rotateRight(Node* node) {
	cout<<"------RR Rotation Applied-------"<< endl;

	Node* newRoot = node->left;
	node->left = newRoot->right;
	newRoot->right = node;
	updateHeight(node);
	updateHeight(newRoot);
	return newRoot;
}

Node* Node :: rotateRightLeft(Node* node) {
	cout<<"------RL Rotation Applied-------"<< endl;

	node->left = rotateLeft(node->left);
	return rotateRight(node);
}

Node* Node :: rotateLeftRight(Node* node) {
	cout<<"------LR Rotation Applied-------"<< endl;

	node->right = rotateRight(node->right);
	return rotateLeft(node);
}

Node* Node :: balance (Node* node) {
	if(balanceFactor(node) == 2) {
		if(balanceFactor(node->left) < 0)
			node = rotateLeftRight(node);
		else
			node = rotateRight(node);
	}
	else if(balanceFactor(node) == -2) {
		if(balanceFactor(node->right) > 0)
			node = rotateRightLeft(node);
		else
			node = rotateLeft(node);
	}
	updateHeight(node);
	return node;
}

Node* Node :: insert(Node* node, int key, const string& value) {
	if(!node)
		return new Node(key, value);
	if(key < node->key)
		node->left = insert(node->left, key, value);
	else if(key > node->key)
		node->right = insert(node->right, key, value);
	else {
		node->value = value;
		return node;
	}
	return balance(node);
}

bool Node :: search(Node* node, int key) {
	if(!node)
		return false;
	if(key < node->key)
		return search(node->left, key);
	else if(key > node->key)
		return search(node->right, key);
	else
		return true;
}

void Node :: inorderTraversal(Node* node) {
	if(node) {
		inorderTraversal(node->left);
		cout << node->key << " : " << node->value << " ";
		inorderTraversal(node->right);
	}
}

void Node :: levelTraversal(Node* root) {
	if(root) {
		queue<Node*> q;
		q.push(root);
		while(!q.empty()) {
			Node* node = q.front();
			q.pop();
			cout << node->key << " : " << node->value << " ";
			if(node->left)
				q.push(node->left);
			if(node->right)
				q.push(node->right);
		}
	}
}

int main() {
	int key;
	string value;

	Node* root = NULL;
	int choice = 0;

	do {
		cout << "Menu" << endl;
		cout << "1. Insert key-value pair" << endl;
		cout << "2. Search key" << endl;
		cout << "3. Level order traversal" << endl;
		cout << "4. Inorder traversal" << endl;
		cout << "5. Quit" << endl;
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice) {
		case 1:
			cout << "Enter key: ";
			cin >> key;
			cout << "Enter value: ";
			cin >> value;
			root = root->insert(root, key, value);
			cout << "Inserted key-value pair: " << key << ": " << value << endl;
			break;

		case 2:
			cout << "Enter key to search: ";
			cin >> key;
			if (root->search(root, key))
				cout << "Key found!" << endl;
			else
				cout << "Key not found." << endl;
			break;

		case 3:
				cout << "Level order traversal: ";
				root->levelTraversal(root);
				cout << endl;
				break;


		case 4:
			cout << "Inorder traversal: ";
			root->inorderTraversal(root);
			cout << endl;
			break;

		case 5:
			cout << "Quitting program." << endl;
			break;

		default:
			cout << "Invalid choice. Please try again." << endl;
		}
	} while (choice != 5);

	return 0;
}

