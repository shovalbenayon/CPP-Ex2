/**
 * 04-2020
 * @author Shoval Benayon
 */

#include "FamilyTree.hpp"
using namespace family;

char gender = 0;
char flag = 0;


/**
* Node and Tree constructors.
*/
Node::Node(std::string name) {
    this->gender = NONE;
    this->height = 0;
    this->name = name;
    this->left = nullptr;
    this->right = nullptr;
}

Tree::Tree(std::string name) {
    if (name == "") 
        throw std::invalid_argument("Error : bad input. String cannot be empty");
    root = new Node(name);
}

/**
* Node and Tree destructors.
*/
Node::~Node() {}
Tree::~Tree() {destroy(&root);}

/**
* addMother method implementation.
*/
Tree& Tree::addMother(const std::string descendant, const std::string parent) {
    if (root == nullptr) 
        throw std::runtime_error("ERROR! addMother method failed due to an empty tree");
    if (descendant == "" | parent == "") 
        throw std::invalid_argument("ERROR! the input must be a non-empty string");
    flag = 0;
    gender = FEMALE;
    insert(&root, descendant, parent); // A protected method
    if (flag == 1) 
        return *this;
    throw std::runtime_error("ERROR! addMother method failed due to descendant's non-existence");
}

/**
* addFather method implementation.
*/
Tree& Tree::addFather(const std::string descendant, const std::string parent) {
    if (root == nullptr) 
        throw std::invalid_argument("ERROR! addFather method failed due to an empty tree");
    if (descendant == "" | parent == "") 
        throw std::invalid_argument("ERROR! the input must be a non-empty string");
    flag = 0;
    gender = MALE;
    insert(&root, descendant, parent); // A protected method
    if (flag == 1) 
        return *this;
    throw std::runtime_error("ERROR! addFather failed due to descendant's non-existence");
}

/**
* display method implementation.
*/
void Tree::display() const {
    if (root == nullptr) 
        std::cout << "The tree is empty" << std::endl;        
    else traversal(root); // A protected method
}

/**
* relation method implementation.
*/
const std::string Tree::relation(const std::string name) const {
    if (root == nullptr) 
        throw std::invalid_argument("ERROR! relation method failed due to an empty tree");
    if (name == "") 
        throw std::invalid_argument("ERROR! the input must be a non-empty string");

    int len = length(root, name); // A protected method
    if (len == -1) 
        return "unrelated"; // No relation has found
    if (len == 0)
        return "me";
    if (len == 1) 
        return gender == FEMALE ? "mother" : "father";
    
    std::string related = "";
    for (int i = 2; i < len; i++) 
        related += "great-"; // Holds if len is greater than 2
    return gender == FEMALE ? related += "grandmother" : related += "grandfather";
    }

/**
* find method implementation.
*/
const std::string Tree::find(const std::string relation) const {
    if (root == nullptr) 
        throw std::runtime_error("ERROR! find method failed due to an empty tree");
    if (relation == "") 
        throw std::invalid_argument("ERROR! the input must be a non-empty string");

    std::vector<std::string> tokens;
    std::stringstream check1(relation);
    std::string intermediate;
    while (std::getline(check1, intermediate, '-')) // Tokenizing a string
        tokens.push_back(intermediate);
            
    int height = 0;
    int i = 0;
    while (i < tokens.size() - 1) { // For counting purpose
        if (tokens[i] != "great") 
            throw std::invalid_argument("ERROR! invalid input");
        height++;
        i++;
    }

    i = tokens.size() - 1; // To identify the relation type
    if (tokens[i] == "me") 
        return root->name; // The tree is non-empty

    else if (tokens[i] == "mother") {
        if (root->left == nullptr) 
            throw std::runtime_error("No relation has found");
        return root->left->name;
    }

    else if (tokens[i] == "father") {
        if (root->right == nullptr) 
            throw std::runtime_error("No relation has found");
        return root->right->name;
    }

    else if (tokens[i] == "grandmother") {
        gender = FEMALE;
        return limitedBFS(root, height + 2);
    }

    else if (tokens[i] == "grandfather") {
        gender = MALE;
        return limitedBFS(root, height + 2);
    }

    else throw std::runtime_error("Cannot handle the specified relation");
}

/**
* remove method implementation.
*/
Tree& Tree::remove(const std::string name) {
    if (root == nullptr) 
        throw std::runtime_error("ERROR! remove method failed due to an empty tree");
    if (name == "") 
        throw std::invalid_argument("ERROR! the input must be a non-empty string");

    if (root->name == name) // The tree is non-empty
        throw std::runtime_error("ERROR! remove method failed due to an attempt to destory the tree");

    flag = 0;
    remove(&root, name); // A protected method
    if (flag == 1) 
        return *this;
    throw std::runtime_error("ERROR! remove method failed due to name's non-existence");
}

void Tree::destroy(Node** current) {
    if (*current != nullptr) {
        destroy(&((*current)->left));
        destroy(&((*current)->right));
        delete(*current);
    }
}

void Tree::insert(Node** current, const std::string descendant, const std::string parent) {
    if (*current != nullptr) {
        if ((*current)->name == descendant) { // Match has found
            if (gender == FEMALE) {
                if ((*current)->left == nullptr) { // Checks mother's non-existence
                    (*current)->left = new Node(parent);
                    (*current)->left->gender = FEMALE;
                    (*current)->left->height = 1 + (*current)->height;
                    flag = 1; // Added
                    return;
                }

                else throw std::runtime_error("ERROR! addMother method failed since duplications are not allowed");
            }

            else {
                if ((*current)->right == nullptr) { // Checks father's non-existence
                    (*current)->right = new Node(parent);
                    (*current)->right->gender = MALE;
                    (*current)->right->height = 1 + (*current)->height;
                    flag = 1; // Added
                    return;
                }

                else throw std::runtime_error("ERROR! addFather method failed since duplications are not allowed");
            }
        }

        insert(&((*current)->left), descendant, parent);
        insert(&((*current)->right), descendant, parent);
    }
}

void Tree::traversal(const Node* current) const {
    if (current != nullptr) {
        // Prints the specified node and it's parents names
        std::cout << current->name << std::endl;
        if (current->left != nullptr) 
            std::cout << "Mother's name is " + current->left->name << std::endl;
        else    
            std::cout << "Mother's name is unknown" << std::endl; // Prints unknown in case of non-existence
        if (current->right != nullptr) 
            std::cout << "Father's name is " + current->right->name << std::endl;
        else 
            std::cout << "Father's name is unknown" << std::endl; // Prints unknown in case of non-existence
        std::cout << std::endl;

        traversal(current->left);
        traversal(current->right);
    }
}

const int Tree::length(const Node* current, const std::string name) const {
    if (current == nullptr) 
        return -1;

    int len = -1;
    if (current->name == name) { // Match has found
        if (current->gender == NONE) 
            return 0; // Refers to the root
        if (current->gender == FEMALE) 
            gender = FEMALE;
        else 
            gender = MALE;
        return len + 1;
    }

    else if ((len = length(current->left, name)) >= 0 || (len = length(current->right, name)) >= 0)
        return len + 1;
    
    return len;
}

void Tree::remove(Node** current, const std::string name) {
    if (*current != nullptr) {
        if ((*current)->left != nullptr) {
            if ((*current)->left->name == name) {
                Node* rem = (*current)->left;
                (*current)->left = nullptr; // Update
                destroy(&rem); // Free memory
                flag = 1; // Removed
                return;
            }
        }

        if ((*current)->right != nullptr) {
            if ((*current)->right->name == name) {
                Node* rem = (*current)->right;
                (*current)->right = nullptr; // Update
                destroy(&rem); // Free memory
                flag = 1; // Removed
                return;
            }
        }

        remove(&((*current)->left), name);
        remove(&((*current)->right), name);
    }
}

const std::string Tree::limitedBFS(Node* current, const int height) const {
    std::queue<Node*> nodes;
    nodes.push(current); // The tree is non-empty
    while (!nodes.empty()) {
        if (nodes.front()->height > height) /* height = limit */ 
            throw std::runtime_error("No relation has found");
        if (nodes.front()->height == height) {
            if (nodes.front()->gender == gender) 
                return nodes.front()->name;
        }

        if (nodes.front()->left != nullptr) 
            nodes.push(nodes.front()->left);
        if (nodes.front()->right != nullptr) 
            nodes.push(nodes.front()->right);
        nodes.pop();
    }

    throw std::runtime_error("No relation has found");
}