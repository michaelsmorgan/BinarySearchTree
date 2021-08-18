#ifndef _BINARYTREE_HPP_
#define _BINARYTREE_HPP_
#include <memory>

template<typename T>
class BinaryTree {
public:
	BinaryTree() :
		m_root(nullptr)
	{}

	bool insert(T value);
	void remove(T value);
	bool search(T value);
	unsigned int numberNodes();
	unsigned int numberLeafNodes();
	unsigned int height();
	std::string fixWord(std::string word);

	void display();

	class NotFound{};
	class AlreadyThere{};

private:
	template<typename T>
	class TreeNode {
	public:
		TreeNode(T value) :
			data(value),
			left(nullptr),
			right(nullptr) 
		{}

		T data;

		std::shared_ptr<TreeNode<T> > left;
		std::shared_ptr<TreeNode<T> > right;

	};

	std::shared_ptr<TreeNode<T> > m_root;

	bool insert(std::shared_ptr<TreeNode<T> >& node, std::shared_ptr<TreeNode<T> > ptrNew);
	bool search(std::shared_ptr<TreeNode<T> > node, T value);
	void display(std::shared_ptr<TreeNode<T> > node);

	void remove(std::shared_ptr<TreeNode<T> >& node);
	void remove(std::shared_ptr<TreeNode<T> >& node, T value);

	unsigned int numberNodes(std::shared_ptr<TreeNode<T> > node);
	unsigned int numberLeafNodes(std::shared_ptr<TreeNode<T> > node);
	unsigned int height(std::shared_ptr<TreeNode<T> > node);
	
};

template<typename T>
bool BinaryTree<T>::insert(T value) {
	try {
		std::shared_ptr<TreeNode<T> > ptrNew = std::make_shared<TreeNode<T> >(value);
		return (insert(m_root, ptrNew));
	}
	catch (AlreadyThere) {
		std::cout << "That entry is already in the dictionary" << std::endl;
	}
}

template<typename T>
bool BinaryTree<T>::insert(std::shared_ptr<TreeNode<T> >& node, std::shared_ptr<TreeNode<T> > ptrNew) {
	if (node == nullptr) {
		node = ptrNew;
		return true;
	}
	if (node->data == ptrNew->data) {
		throw AlreadyThere();
	}
	if (node->data < ptrNew->data) {
		insert(node->right, ptrNew);
	}
	else {
		insert(node->left, ptrNew);
	}
}

template<typename T>
void BinaryTree<T>::remove(T value) {
	try {
		remove(m_root, value);
	}
	catch (NotFound ex) {
		std::cout << "That entry does not exist in the dictionary" << std::endl;
	}
}

template<typename T>
void BinaryTree<T>::remove(std::shared_ptr<TreeNode<T> >& node, T value) {
	if (node == nullptr) {
		throw NotFound();
	}
	else if (node->data == value) {
		remove(node);
	}
	else if (node->data < value) {
		remove(node->right, value);
	}
	else {
		remove(node->left, value);
	}
}

template<typename T>
void BinaryTree<T>::remove(std::shared_ptr<TreeNode<T> >& node) {
	if (node->right == nullptr) {
		node = node->left;
	}
	else if (node->left == nullptr) {
		node = node->right;
	}
	else {
		auto temp = node->right;
		while (temp->left) {
			temp = temp->left;
		}
		temp->left = node->left;
		node = node->right;
	}
}

template<typename T>
bool BinaryTree<T>::search(T value) {
	return search(m_root, value);
}

template<typename T>
bool BinaryTree<T>::search(std::shared_ptr<TreeNode<T> > node, T value) {
	if (node == nullptr) {
		return false;
	}
	if (node->data == value) {
		return true;
	}
	if (node->data < value) {
		return search(node->right, value);
	}
	else {
		return search(node->left, value);
	}
}

template<typename T>
void BinaryTree<T>::display() {
	display(m_root);
}

template<typename T>
void BinaryTree<T>::display(std::shared_ptr<TreeNode<T> > node) {
	if (node != nullptr) {
		display(node->left);
		std::cout << node->data << std::endl;
		display(node->right);
	}
}

template<typename T>
unsigned int BinaryTree<T>::numberNodes() {
	return numberNodes(m_root);
}

template<typename T>
unsigned int BinaryTree<T>::numberNodes(std::shared_ptr<TreeNode<T> > node) {
	if (node == nullptr) {
		return 0;
	}
	return 1 + (numberNodes(node->left) + numberNodes(node->right));
}

template<typename T>
unsigned int BinaryTree<T>::numberLeafNodes() {
	return numberLeafNodes(m_root);
}

template<typename T>
unsigned int BinaryTree<T>::numberLeafNodes(std::shared_ptr<TreeNode<T> > node) {
	if (node == nullptr) {
		return 0;
	}
	if (node->left == nullptr && node->right == nullptr) {
		return 1;
	}
	return (numberLeafNodes(node->left) + numberLeafNodes(node->right));
}

template<typename T>
unsigned int BinaryTree<T>::height() {
	return height(m_root);
}

template<typename T>
unsigned int BinaryTree<T>::height(std::shared_ptr<TreeNode<T> > node) {
	// TODO: rewrite this method
	if (node == nullptr) {
		return 0;
	}

	int right = (height(node->right));
	int left = height(node->left);
	if (left >= right) {
		return 1 + left;
	}
	else {
		return 1 + right;
	}
	
}

template<typename T>
std::string BinaryTree<T>::fixWord(std::string word)
{
	std::string temp = "";
	for (unsigned int i = 0; i < word.size(); i++) {
		if (word[i] != ',' && word[i] != '.' && word[i] != ':' && word[i] != '!' && word[i] != '?' && word[i] != '(' && word[i] != ')') {
			if (word[i] >= 65 && word[i] <= 90) {
				word[i] += 32;
			}
			temp += word[i];
		}
	}
	return temp;
}


#endif
