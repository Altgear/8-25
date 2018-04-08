#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <vector>

class tree_t {
private:

    struct node_t {
        node_t * left;
        node_t * right;
        int value;
    };

private:
    node_t * root_;
    void print_tree(std::ostream & stream, const node_t * branch,
        unsigned int depth) const;
public:
    tree_t();
    tree_t(int val);
    ~tree_t();
    void insert(int value); //done
    bool find(int value) const noexcept; // not shure|+~
    void print(std::ostream & stream) const; //done~
    void delete_branch(node_t * branch);

    void del_rt();
};

int main() {
    char op;
    std::string line;
    tree_t * origin = nullptr;
    int value = 0XFFFFFF; // error
    for (;; ) {

        std::getline(std::cin, line);
        std::istringstream stream(line);
        //try
        if ( !( stream >> op ) )
            op = 'e'; //error
        //
        switch ( op ) {
            case '+':

            {

                //try
                stream >> value;
                if ( origin == nullptr ) {
                    origin = new tree_t(value);

                } else {
                    origin->insert(value);
                }
                //
                origin->print(std::cout);
                break;
            }
            case '?':
            {
                int value;
                //try
                stream >> value;
                if ( origin->find(value) ) {
                    std::cout << "true\n";
                } else
                    std::cout << "false\n";
                //
                break;
            }
            case '=':
            {
                origin->print(std::cout);
                break;
            }
            case 'q':
            {
                origin->~tree_t();
                return 0;
            }
            default:
            {
                std::cout << "wrong op" << std::endl;
            }

        }


    }

    return 0;
}

bool tree_t::find(int val) const noexcept {
    node_t * current = root_;
    bool found = false;
    while ( current != nullptr ) {
        if ( val > current->value ) {
            current = current->right;
            continue;
        } else if ( val < current->value ) {
            current = current->left;
            continue;
        } else if ( current->value == val ) {
            found = true;
            return found;
        }
    }

    return found;
}

void tree_t::insert(int value) {
    node_t * current = root_;
    bool direction = false;
    while ( true ) {
        if ( current->value <= value ) {
            if ( current->right == nullptr ) {
                direction = true;
                break;
            }
            current = current->right;
        } else if ( current->value > value ) {
            if ( current->left == nullptr ) {
                break;
            }
            current = current->left;
        }
    }
    if ( direction ) {
        current->right = new node_t;
        current->right->value = value;
        current->right->left = nullptr;
        current->right->right = nullptr;
    } else {
        current->left = new node_t;
        current->left->value = value;
        current->left->left = nullptr;
        current->left->right = nullptr;
    }
    return;
}

void tree_t::print_tree(std::ostream & stream, const node_t * branch,
    unsigned int depth) const {
    if ( branch->right != nullptr ) {
        print_tree(stream, branch->right, depth + 4);
    }
    for ( unsigned int i = 0; i < depth; ++i ) {
        stream << "-";
    }
    stream << branch->value << std::endl;

    if ( branch->left != nullptr ) {
        print_tree(stream, branch->left, depth + 4);
    }
    return;
}

void tree_t::delete_branch(node_t * branch) {
    if ( branch->left != nullptr ) {
        delete_branch(branch->left);
    }
    if ( branch->right != nullptr ) {
        delete_branch(branch->right);
    }
    delete[] branch;
    return;

}

tree_t::tree_t(int val) {
    root_ = new node_t; //!!!"*" new returns ptr
    root_->value = val;
    root_->left = nullptr;
    root_->right = nullptr;
}

tree_t::tree_t() {
    root_ = nullptr;
}

void tree_t::print(std::ostream & stream) const {
    print_tree(stream, root_, 4); // 4 init branch length
}

/*void tree_t::print(std::ostream & stream) const {
    
}*/

tree_t::~tree_t() {
    delete_branch(root_);
}

