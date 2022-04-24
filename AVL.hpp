#ifndef AVL_H
#define AVL_H
#include <memory>
#include <iostream>
#include <stdexcept>

namespace custom_lib
{
typedef enum CompareRes{
    LESS,
    EQUAL,
    LARGER
}CompareRes;

/********************************************************************************
                            AVL class
********************************************************************************/

    template<class Data,class Key>
    class AVL
    {
/********************************************************************************
                            AVL variables
********************************************************************************/
        private:
        // Generic data 
        
        std::shared_ptr<Data> data;
        std::shared_ptr<Key> key;
        AVL* right;
        AVL* left;
        CompareRes (*compareFunc)(Key a,Key b); 
        int height = 0;

/********************************************************************************
                            AVL constructors
********************************************************************************/
        public:
        /**
         * @brief Default constructor()
         * 
         */
        AVL(Data new_data,Key new_key, AVL* right = nullptr,AVL* left = nullptr, CompareRes (*newCompareFunc)(Key a,Key b) = nullptr)
        {
            this->right = right;
            this->left = left;
            this->data = std::make_shared<Data>(new_data);
            this->key = std::make_shared<Key>(new_key);
            this->compareFunc = newCompareFunc;
            
            std::cout <<"Compare res :" <<(compareFunc(*key,1))<< std::endl;

        }

        /**
         * @brief Destroy the AVL object
         * 
         */
        ~AVL() = default;
       
/********************************************************************************
                            AVL functions(public)
********************************************************************************/
         
         /**
          * @brief Get the AVL's data
          * 
          * @return const T& 
          */
         const Data& getData() const
        {
            return data;
        }

        /**
         * @brief Get the pointer of the next AVL
         * 
         * @return AVL* 
         */
        AVL* getRight() const
        {
            return right;
        }

         /**
         * @brief Get the pointer of the next AVL
         * 
         * @return AVL* 
         */
        AVL* getLeft() const
        {
            return left;
        }

          /**
         * @brief Get the pointer of the next AVL
         * 
         * @return AVL* 
         */
        AVL* getKey() const
        {
            return key;
        }

        AVL* deleteTree()
        {
           if(this != nullptr)
           {
               if(left !=nullptr)
                 left->deleteTree();
                if(right != nullptr)
                right->deleteTree();
           }


        }

        const int getMax(int a,int b)
        {
            return (a < b) ?  a : b ;
        }

          const int getMaxHeight(AVL* first,AVL* second)
        {
            int a,b;
            if(first != nullptr)
                a = first->getHeight();
            else
               a =0;

            if(second != nullptr)
                b = second->getHeight();
            else
                b = 0;
            return (a < b) ?  a : b ;
        }

        const int getHeight()
        {
            return height;
        }

   AVL* insert(Data &item ,Key new_key)
        {
          if(standardBinInsert(item,new_key)==NULL)
            return this;

            int balance = this->getBalance();
 
    
 
            // Left Left Case
            if (balance > 1 && key < left->key)
                return rightRotate();
        
            // Right Right Case
            if (balance < -1 && key > right->key)
                return leftRotate();
        
            // Left Right Case
            if (balance > 1 && key > left->key)
            {
                left = leftRotate();
                return rightRotate();
            }
        
            // Right Left Case
            if (balance < -1 && key < right->key)
            {
                right = right->rightRotate();
                return leftRotate();
            }

            return this;

        }
/**
 * @brief 
 * AVL* remove(Key removeKey)
    {
        
        
        if (this == NULL)
            return this;
    
        // If the key to be deleted is smaller
        // than the root's key, then it lies
        // in left subtree
        if ( compareFunc(removeKey,key) == LESS )
            left = left->remove(key);
    
        // If the key to be deleted is greater
        // than the root's key, then it lies
        // in right subtree
        else if( compareFunc(removeKey,key) == LARGER )
            right = right->remove(key);
    
        // if key is same as root's key, then
        // This is the AVL to be deleted
        else
        {
            // AVL with only one child or no child
            if( (left == NULL) ||
                (right == NULL) )
            {
                AVL *temp = left ? left :right;
    
                // No child case
                if (temp == NULL)
                {
                    deleteTree();
                }
                else // One child case
                *root = *temp; // Copy the contents of
                            // the non-empty child
                free(temp);
            }
            else
            {
                // AVL with two children: Get the inorder
                // successor (smallest in the right subtree)
                AVL* temp = minValueAVL(root->right);
    
                // Copy the inorder successor's
                // data to this AVL
                root->key = temp->key;
    
                // Delete the inorder successor
                root->right = deleteAVL(root->right,
                                        temp->key);
            }
        }
    
        // If the tree had only one AVL
        // then return
        if (root == NULL)
        return root;
    
        // STEP 2: UPDATE HEIGHT OF THE CURRENT AVL
        root->height = 1 + max(height(root->left),
                            height(root->right));
    
        // STEP 3: GET THE BALANCE FACTOR OF
        // THIS AVL (to check whether this
        // AVL became unbalanced)
        int balance = getBalance(root);
    
        // If this AVL becomes unbalanced,
        // then there are 4 cases
    
        // Left Left Case
        if (balance > 1 &&
            getBalance(root->left) >= 0)
            return rightRotate(root);
    
        // Left Right Case
        if (balance > 1 &&
            getBalance(root->left) < 0)
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    
        // Right Right Case
        if (balance < -1 &&
            getBalance(root->right) <= 0)
            return leftRotate(root);
    
        // Right Left Case
        if (balance < -1 &&
            getBalance(root->right) > 0)
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    
        return root;
    }
 * @param removeKey 
 * @return AVL* 
 */

       
    
        void inOrder(void (*apply)(Data data))
        {
            if(left != nullptr)
                left->inOrder(apply);
            apply(*this->data);
            if(right != nullptr)
                right->inOrder(apply);
            
        }

        AVL *rightRotate()
        {
            AVL *x = this->left;
            AVL *T2 = x->right;
        
            // Perform rotation
            x->right = this;
            this->left = T2;
        
            // Update heights
            this->height = getMax(this->left->getHeight(),(this->right->getHeight()) + 1);
                            
            x->height = getMax(x->left->getHeight(), (x->right->getHeight()) + 1);
                           
        
            // Return new root
            return x;
        }
        
        // A utility function to left
        // rotate subtree rooted with x
        // See the diagram given above.
        AVL *leftRotate()
        {
            AVL *y = this->right;
            AVL *T2 = y->left;
        
            // Perform rotation
            y->left = this;
            this->right = T2;
        
            // Update heights
            this->height = getMax(this->left->getHeight(),(this->right->getHeight() + 1)); 
                            
            y->height = getMax(y->left->getHeight(),(y->right->getHeight() + 1));
                            
        
            // Return new root
            return y;
        } 
 
       

        // Get Balance factor of AVL N
        int getBalance() const
        {
            if (this == nullptr)
                return 0;
            int rightHeigth,leftHeigth;
            if(left!= nullptr)
                leftHeigth = left->getHeight();
            else
                leftHeigth = 0;
            
            if(right != nullptr)
                rightHeigth = right->getHeight();
            else
                rightHeigth = 0;
            return (leftHeigth - rightHeigth);
        }
/********************************************************************************
                            AVL operators
********************************************************************************/
        AVL& operator=(const AVL& item)
        {
            if (this == &item)
            {
                return *this;
            }
            if(this != nullptr)
            {
                delete this;
            }
            data = item.data;
            right = new AVL(item->right);
            left = new AVL(item->left);
            return *this;
        }
       
        bool operator==(const AVL& item) const
        {
             return (key==item.key);
        }

         private:
    
        AVL* standardBinInsert(Data &item ,Key new_key)
        {
             //normal bin tree insertion
             CompareRes res = compareFunc(*this->key,new_key);
            switch (res)
            {
            case LESS:
                if(this->left == nullptr)
                    this->left = new AVL(item,new_key,nullptr,nullptr,compareFunc);
                else
                    this->left->insert(item,new_key);
                break;

            case LARGER:
                if(this->right == nullptr)
                    this->right = new AVL(item,new_key,nullptr,nullptr,compareFunc);
                else
                    this->right->insert(item,new_key);
                break;

            default: 
                   return NULL ; 
                break;
            }
            this->height = 1 + getMaxHeight(left,right);
            return this;
        }
    };

   

}
#endif


