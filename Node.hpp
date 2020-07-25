/**
 * 04-2020
 * @author Shoval Benayon
 */

#pragma once
#include <bits/stdc++.h>
#include <queue>
#include <string>
#include <iostream>

#define FEMALE 0
#define MALE 1
#define NONE 2

#include <string>
#include <iostream>

namespace family {
    class Node {
        friend class Tree;
    private:
        char gender;
        int height;
        std::string name;
        Node* left; // Mother
        Node* right; // Father
        Node(std::string name);
        ~Node();
    }; // class Node
}; // namespace family