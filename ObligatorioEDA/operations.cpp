#include <iostream>
#include "operations.h"
#include "variables.h"
using namespace std;

void insBack(List& initialList, string value) {
    List newNode = new nodeList;
    newNode->value = value;
    newNode->next = NULL;
    if (initialList == NULL) {
        initialList = newNode;
    }
    else {
        List copyList = initialList;
        while (copyList->next != NULL) {
            copyList = copyList->next;
        }
        copyList->next = newNode;
    }
}

void insBackInt(ListInt& initialList, int value) {
    ListInt newNode = new nodeListInt;
    newNode->value = value;
    newNode->next = NULL;
    if (initialList == NULL) {
        initialList = newNode;
    }
    else {
        ListInt copyList = initialList;
        while (copyList->next != NULL) {
            copyList = copyList->next;
        }
        copyList->next = newNode;
    }
}

TreeInt newNode(int value, string row) {
    TreeInt newNode = new nodeTree;
    newNode->value = value;
    newNode->row = row;
    newNode->right = NULL;
    newNode->left = NULL;
    return newNode;
}

TreeStr newNodeStr(string value, string row) {
    TreeStr newNode = new nodeTreeStr;
    newNode->value = value;
    newNode->row = row;
    newNode->right = NULL;
    newNode->left = NULL;
    return newNode;
}

typeRet insert(TreeInt& tree, int value, string row) {
    if (tree == NULL) {
        TreeInt newTree = newNode(value, row);
        tree = newTree;
        return OK;
    }
    else {
        if (value < tree->value) {
            insert(tree->left, value, row);
            return OK;
        }
        else if (value == tree->value) {
            insert(tree->right, value, row);
            return ERROR;
        }
        else {
            insert(tree->right, value, row);
            return OK;
        }
    }
}

typeRet insertText(TreeStr& tree, string value, string row) {
    if (tree == NULL) {
        TreeStr newTree = newNodeStr(value, row);
        tree = newTree;
        return OK;
    }
    else {
        if (value.compare(tree->value) < 0) {
            insertText(tree->left, value, row);
            return OK;
        }
        else if (value.compare(tree->value) == 0) {
            insertText(tree->right, value, row);
            return ERROR;
        }
        else {
            insertText(tree->right, value, row);
            return OK;
        }
    }
}

void showTreeStr(TreeStr tree) {
    if (tree == NULL) return;
    showTreeStr(tree->left);
    cout << tree->row << endl;
    showTreeStr(tree->right);
}

void showTree(TreeInt tree) {
    if (tree == NULL) return;
    showTree(tree->left);
    cout << tree->row << endl;
    showTree(tree->right);
}