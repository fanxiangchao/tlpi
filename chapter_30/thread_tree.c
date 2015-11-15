#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include "tlpi_hdr.h"

struct thread_tree_node
{
    char *key;
    void *value;
    pthread_mutex_t mtx;
    struct thread_tree_node *left;
    struct thread_tree_node *right;
};

typedef struct thread_tree_node * treeNodePtr;

void lockNode(treeNodePtr node);
void unlockNode(treeNodePtr node);

/** Initialize tree */
void initialize(treeNodePtr *treeRoot)
{
    int s;
    *treeRoot = (struct thread_tree_node *)malloc(sizeof(struct thread_tree_node));
    if (treeRoot == NULL)
    {
        errExit("malloc");
    }

    (*treeRoot)->key = NULL;
    (*treeRoot)->value = NULL;
    if ((s = pthread_mutex_init(&((*treeRoot)->mtx),NULL)) != 0)
    {
        errExitEN(s,"pthread_mutex_init");
    }
    (*treeRoot)->left = NULL;
    (*treeRoot)->right = NULL;
}

/** Add tree node  */
void add(treeNodePtr *tree,char *key,void *value)
{
    treeNodePtr root = *tree;
    treeNodePtr node;
    treeNodePtr nodePar;
    treeNodePtr nodeTrans;
    int s;
    
    if (root == NULL)
    {
        initialize(tree);
        (*tree)->key = key;
        (*tree)->value = value;
        return;
    }

    node = (struct thread_tree_node *)malloc(sizeof(struct thread_tree_node));
    if (node == NULL)
    {
        errExit("malloc node");
    }

    node->key = key;
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    
    if ((s = pthread_mutex_init(&node->mtx,NULL)) != 0)
    {
        errExitEN(s,"pthread_mutex_init");
    }
    
    nodeTrans = root;
    while (nodeTrans != NULL)
    {

        nodePar = nodeTrans;
        lockNode(nodePar);
        
        if (strcmp(nodeTrans->key,key) > 0)
        {
            nodeTrans = nodeTrans->left;
            if (nodeTrans == NULL)
            {
                nodePar->left = node;
            }
        }else
        {
            nodeTrans = nodeTrans->right;
            if (nodeTrans == NULL)
            {
                nodePar->right = node;
            }
        }

        unlockNode(nodePar);
    }

}

treeNodePtr getMostLeftChild(treeNodePtr node)
{
    treeNodePtr child;
    if (node == NULL)
    {
        return NULL;
    }

    child = node;
    while (child->left != NULL)
    {
        child = child->left;
    }

    return child;
}

treeNodePtr getMostRightChild(treeNodePtr node)
{
    treeNodePtr child;
    if (node == NULL)
    {
        return NULL;
    }

    child = node;
    while (child->right != NULL)
    {
        child = child->right;
    }

    return child;
}

void destroyNode(treeNodePtr node)
{

    int s;
    
    if (node == NULL)
    {
        return;
    }

    printf("delete key = %s, value = %s\n",node->key,(char *)(node->value));
    s = pthread_mutex_destroy(&(node->mtx));

    if (s != 0)
    {
        errExitEN(s,"pthread_mutex_destroy");
    }

    free(node);
}

void lockNode(treeNodePtr node)
{
    int s;
    
    if (node == NULL)
    {
        return;
    }

    s = pthread_mutex_lock(&(node->mtx));
    if (s != 0)
    {
        errExitEN(s,"pthread_mutex_lock");
    }    
}

void unlockNode(treeNodePtr node)
{
    int s;

    if (node == NULL)
    {
        return;
    }
    
    s = pthread_mutex_unlock(&(node->mtx));
    if (s != 0)
    {
        errExitEN(s,"pthread_mutex_lock");
    }

}


/** Delete tree node */
void delete(treeNodePtr *tree,char *key)
{
    treeNodePtr root = *tree;
    treeNodePtr node;
    treeNodePtr nodePar;
    treeNodePtr mostLeftChild = NULL;
    treeNodePtr mostRightChild = NULL;
    treeNodePtr rightChild = NULL;
    treeNodePtr leftChild = NULL;
    treeNodePtr parRightChild = NULL;
    treeNodePtr childNode = NULL;
    
    int s;
    
    if (tree == NULL || root == NULL)
    {
        printf("Empty tree");
        return;
    }

    nodePar = NULL;
    node = root;
    while (node != NULL)
    {

        lockNode(node);

        if (strcmp(node->key,key) > 0)
        {
            nodePar = node;
            node = node->left;
            unlockNode(nodePar);
        }else if (strcmp(node->key,key) < 0)
        {
            nodePar = node;
            node = node->right;
            unlockNode(nodePar);
        }else
        {
            /** Not root node  */
            if (nodePar != NULL)
            {

                lockNode(nodePar);
                if (node->right != NULL)
                {
                    if (node->left != NULL)
                    {
                        leftChild = node->right->left;
                        lockNode(node->right);
                        node->right->left = node->left;
                        unlockNode(node->right);
                    
                        mostRightChild = getMostRightChild(node->left);
                        if (mostRightChild != NULL)
                        {
                            lockNode(mostRightChild);
                            mostRightChild->right = leftChild;
                            unlockNode(mostRightChild);
                        }
                    }

                    childNode = node->right;
                    
                }else if (node->left != NULL)
                {
                    childNode = node->left;
                }else
                {
                    childNode = NULL;
                }

                if (nodePar->left == node)
                {
                    nodePar->left = childNode;
                }else
                {
                    nodePar->right = childNode;
                }

                unlockNode(nodePar);
            }else  /* Root node */
            {
                if (node->left != NULL)
                {
                    rightChild = node->left->right;
                    lockNode(node->left);
                    node->left->right = node->right;
                    unlockNode(node->left);
                    parRightChild = node->right;

                    if (parRightChild != NULL)
                    {
                        mostLeftChild = getMostLeftChild(parRightChild);
                        lockNode(mostLeftChild);
                        mostLeftChild->left = rightChild;
                        unlockNode(mostLeftChild);
                    }
                    
                    *tree = node->left;
                }else
                {
                    *tree = node->right;
                }
            }
            
            unlockNode(node);
            destroyNode(node);
            
            break;
        }

    }
}

/** Look up tree node */
int lookup(treeNodePtr root,char *key,void **value)
{
    treeNodePtr node;
    int s;
    int isFind = 0;
    
    if (root == NULL)
    {
        return isFind;
    }

    node = root;

    while (node != NULL)
    {
        lockNode(node);

        if (strcmp(node->key,key) > 0)
        {
            unlockNode(node);
            node = node->left;
        }else if (strcmp(node->key,key) < 0)
        {
            unlockNode(node);
            node = node->right;
        }else
        {
            unlockNode(node);
            if (strcmp((char *)node->value,(char *)(*value)) == 0)
            {
                isFind = 1;
                
            }else
            {
                node = node->right;
            }
        }
        
        if (isFind)
        {
            break;
        }
    }

    return isFind;
}

static void * threadFunc_1(void *arg)
{
    treeNodePtr *root = (treeNodePtr *)arg;
    char* data[][2] = {
                      {"th1_6","thread_1:node 6"},
                      {"th1_2","thread_1:node 2"},
                      {"th1_8","thread_1:node 8"},
                      {"th1_3","thread_1:node 3"},
                      {"th1_9","thread_1:node 9"},
                      {"th1_7","thread_1:node 7"},
                      {"th1_5","thread_1:node 5"},
                      {"th1_1","thread_1:node 1"}
    };
    int i;
    int isFind;
    
    for (i = 0; i < 8; i++)
    {
        add(root,data[i][0],(void *)data[i][1]);
        sleep(2);
    }

    for (i = 0; i < 8; i++)
    {
        isFind = lookup(*root,data[i][0],(void **)(&data[i][1]));
        printf("Thread 1: key = %s, value = %s %s\n",data[i][0],
               data[i][1],isFind ? "found" : "not found");
        sleep(1);
    }

    for (i = 0; i < 8; i++)
    {
        delete(root,data[i][0]);
        isFind = lookup(*root,data[i][0],(void **)(&data[i][1]));
        printf("Thread 1: key = %s, value = %s %s\n",data[i][0],
               data[i][1],isFind ? "found" : "not found");
        sleep(2);
    }

    return NULL;
}

static void * threadFunc_2(void *arg)
{
    treeNodePtr *root = (treeNodePtr *)arg;
    char* data[][2] = {
                      {"th2_6","thread_2:node 6"},
                      {"th2_2","thread_2:node 2"},
                      {"th2_8","thread_2:node 8"},
                      {"th2_3","thread_2:node 3"},
                      {"th2_9","thread_2:node 9"},
                      {"th2_7","thread_2:node 7"},
                      {"th2_5","thread_2:node 5"},
                      {"th2_1","thread_2:node 1"}
    };
    int i;
    int isFind;
    
    for (i = 0; i < 8; i++)
    {
        add(root,data[i][0],(void *)data[i][1]);
    }

    for (i = 0; i < 8; i++)
    {
        isFind = lookup(*root,data[i][0],(void **)(&data[i][1]));
        printf("Thread 2: key = %s, value = %s %s\n",data[i][0],
               data[i][1],isFind ? "found" : "not found");
    }

    for (i = 0; i < 8; i++)
    {
        delete(root,data[i][0]);
        isFind = lookup(*root,data[i][0],(void **)(&data[i][1]));
        printf("Thread 2: key = %s, value = %s %s\n",data[i][0],
               data[i][1],isFind ? "found" : "not found");
    }

    return NULL;
}

int main(int argc,char *argv[])
{
    treeNodePtr root = NULL;
    char* data[][2] = {{"6","node 6"},
                      {"2","node 2"},
                      {"8","node 8"},
                      {"3","node 3"},
                      {"9","node 9"},
                      {"7","node 7"},
                      {"5","node 5"},
                      {"1","node 1"}};
    int i;
    int isFind;
    pthread_t t1,t2;
    int s;
    
    for (i = 0; i < 8; i++)
    {
        add(&root,data[i][0],(void *)data[i][1]);
    }

    printf("Find key\n");

    for (i = 0; i < 8; i++)
    {
        isFind = lookup(root,data[i][0],(void **)(&data[i][1]));
        printf("key = %s, value = %s %s\n",data[i][0],
               data[i][1],isFind ? "found" : "not found");
    }

    for (i = 0; i < 8; i++)
    {
        delete(&root,data[i][0]);
        isFind = lookup(root,data[i][0],(void **)(&data[i][1]));
        printf("key = %s, value = %s %s\n",data[i][0],
               data[i][1],isFind ? "found" : "not found");
    }

    s = pthread_create(&t1,NULL,threadFunc_1,&root);
    if (s != 0)
    {
        errExitEN(s,"pthread_create");
    }

    s = pthread_create(&t2,NULL,threadFunc_2,&root);
    if (s != 0)
    {
        errExitEN(s,"pthread_create");
    }
    
    s = pthread_join(t1,NULL);
    if (s != 0)
    {
        errExitEN(s,"pthread_join");
    }

    s = pthread_join(t2,NULL);
    if (s != 0)
    {
        errExitEN(s,"pthread_join");
    }
    
    exit(EXIT_SUCCESS);
}