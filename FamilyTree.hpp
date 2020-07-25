#include "Node.hpp"
#pragma once


namespace family{
    class Tree{
        private:
            Node* root;
            void destroy(Node** current);
            void insert(Node** current, const std::string descendant, const std::string parent);
            void traversal(const Node* current) const;
            const int length(const Node* current, const std::string name) const;
            void remove(Node** current, const std::string name);
            const std::string limitedBFS(Node* current, const int height) const;

        public:

            /**
            *constructor
            **/
            Tree(std::string name);

            /**
            *destructor
            **/
            
            ~Tree();

            /**
            * Add Mother Node by given the nother's name to the descendent and return the tree after adding the mother 
            * to the left node.
            *If one of the names is empty or the tree is empty or the the descendent is non-existence, Exception will be thrown
            */
            Tree& addMother(const std::string descendant, const std::string Mother);

             /**
            * Add Father Node by given the nother's name to the descendent and return the tree after adding the mother 
            * to the left node.
            *If one of the names is empty or the tree is empty or the the descendent is non-existence, Exception will be thrown
            */
            Tree& addFather(const std::string descendant, const std::string Father);

            /**
            * This method prints the tree .
            */
            void display() const;

            /**
            * This method returns the relation between the root and any given name.
            * NOTE that an exception would be thrown in case of an empty string or an empty tree.
            */
            const std::string relation(const std::string name) const;

            /**
            * This method finds and returns the name of any given relation.
            * NOTE that an exception would be thrown in case of an empty string, an empty tree or when 
            * the tree cannot handle the given relation.
            */
            const std::string find(const std::string relation) const;

            /**
            * Given any name, this method returns the tree after removing it and 
            * it's descendants.
            * NOTE that an exception would be thrown in case of an empty string or an empty tree.
            */
            Tree& remove(const std::string name);
       
    }; // class Tree
}; // namespace family
