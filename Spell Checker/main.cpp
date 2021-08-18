#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include "BinaryTree.hpp"

void outputInfo(BinaryTree<std::string> tree) {
	std::cout << "---Tree Stats---" << std::endl;
	std::cout << "Total Nodes: " << tree.numberNodes() << std::endl;
	std::cout << "Leaf Nodes: " << tree.numberLeafNodes() << std::endl;
	std::cout << "Tree Height: " <<tree.height() << std::endl;
	std::cout << std::endl;
}

void setUpTree(BinaryTree<std::string>& tree) {
	std::ifstream fin;
	std::vector<std::string> temp;
	std::string word;
	fin.open("dictionary.txt");
	while (!fin.eof()) {
		fin >> word;
		temp.push_back(word);
	}

	// it would randomize in the exact same way every time until I put the srand(time(NULL)); line there.
	srand(time(NULL));
	std::random_shuffle(temp.begin(), temp.end());


	for (unsigned int i = 0; i < temp.size(); i++) {
		tree.insert(temp[i]);
	}
	fin.close();
}

void spellCheck(BinaryTree<std::string>& tree) {
	std::ifstream fin;
	std::string word;

	fin.open("Letter.txt");

	while (!fin.eof()) {
		fin >> word;
		std::string tempWord = tree.fixWord(word);
		if (!tree.search(tempWord)) {
			std::cout << tempWord << std::endl;
		}
	}
}

int main() {
	
	BinaryTree<std::string> tree;
	
	
	setUpTree(tree);
	outputInfo(tree);

	spellCheck(tree);

	 tree.display();

	return 0;
}