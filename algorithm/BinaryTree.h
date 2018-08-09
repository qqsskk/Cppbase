#pragma once
#include <stdio.h>


template <class T>
struct binary_tree_node
{
	binary_tree_node<T>* left_;
	binary_tree_node<T>* right_;
	T data_;
};

//���������
template <class T>
void binary_tree_output_impl(binary_tree_node<T>* n, bool left, string const& indent)
{
	if (n->right_)
	{
		binary_tree_output_impl(n->right_, false, indent + (left ? "|     " : "      "));
	}
	cout << indent;
	cout << (left ? '\\' : '/');
	cout << "-----";
	cout << n->data_ << endl;
	if (n->left_)
	{
		binary_tree_output_impl(n->left_, true, indent + (left ? "      " : "|     "));
	}
}

template <class T>
void binary_tree_print(binary_tree_node<T>* pRoot) {

	if (pRoot->right_)
	{
		binary_tree_output_impl(pRoot->right_, false, "");
	}
	cout << pRoot->data_ << endl;
	if (pRoot->left_)
	{
		binary_tree_output_impl(pRoot->left_, true, "");
	}
}

//������ͨ������
template <class T>
void binary_tree_create(binary_tree_node<T>*& ptree, T a[], int len)
{
	ptree = (binary_tree_node<T>*)malloc(sizeof(binary_tree_node<T>)*len);
	for (int j = 0; j < len; j++)
	{
		//����aֻ��һ����ֵ������
		ptree[j].data_ = a[j];
		ptree[j].left_ = nullptr;
		ptree[j].right_ = nullptr;
	}
	for (int i = 0; i <= len / 2 - 1; ++i)
	{
		//������
		if (2 * i + 1 < len)
		{
			ptree[i].left_ = &ptree[2 * i + 1];
		}
		//���Һ���
		if (2 * i + 2 < len)
		{
			ptree[i].right_ = &ptree[2 * i + 2];
		}
	}
}

//���ٶ�����
template <class T>
void binary_tree_destory(binary_tree_node<T>* ptree) {
	free(ptree);
}

//���Ҷ�����
template <class T>
bool SearchBST(binary_tree_node<T>* pNode, T data)
{
	if (pNode == nullptr)
		return false;
	if (data < pNode->data_)
		return SearchBST(pNode->left_, data);
	else if (data > pNode->data)
		return SearchBST(pNode->right_, data);
	else
		return true;
}

template <class T>
binary_tree_node<T>* insertBST(T data, binary_tree_node<T>* root)
{
	if (root == NULL)
	{
		root = (binary_tree_node<T>*)malloc(sizeof(binary_tree_node<T>));
		root->data_ = data;
		root->left_ = NULL;
		root->right_ = NULL;
		return root;
	}
	if (data < root->data_)
		root->left_ = insertBST(data, root->left_);
	else if (data > root->data_)
		root->right_ = insertBST(data, root->right_);
	else
		printf("%d is in tree!!!\n", data);
	return root;
}

//���Ҷ���������������С�ڵ�ֵ; �Ӹ��ڵ㿪ʼ��������ӣ�
//ֻҪ��������Ӿ�һֱ���ң��յ������С��Ԫ�أ�����Ϊ�Ҷ��Ӳ����յ� 
template <class T>
binary_tree_node<T>* findMin(binary_tree_node<T>* root)
{
	if (root == NULL)
		return NULL;
	else if (root->left_ == NULL)
		return root;
	return findMin(root->left_);     //�ݹ���� 
}

template <class T>
binary_tree_node<T>* findMax(binary_tree_node<T>* root)
{
	if (root != NULL)                   //�ǵݹ���� 
		while (root->right_ != NULL)
			root = root->right_;
	return root;
}

template <class T>
binary_tree_node<T>* deleteBST(binary_tree_node<T>* root, T data)
{
	if (root == NULL)
		return root;

	if (data < root->data_)
		root->left_ = deleteBST(root->left_, data);
	else if (data > root->data_)
		root->right_ = deleteBST(root->right_, data);
	else if (root->left_ != NULL && root->right_ != NULL)
	{
		root->data_ = findMin(root->right_)->data_;
		root->right_ = deleteBST(root->right_, root->data_);
	}
	else
		root = (root->left_ != NULL) ? root->left_ : root->left_;
	return root;
}