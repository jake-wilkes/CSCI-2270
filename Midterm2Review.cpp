#include<iostream>
#include<vector>
#include<string>
#include<queue>
using namespace std;

// BFS search of an unweighted list, given two vertices, see if the path from one to the other
// includes the intermediate vertex

void Graph::shortestPath(string source, string destination, string intermediate){
    int i = 0;
    vertex* s;
	while ((unsigned)i < vertices.size()) {
		if (vertices[i].name == source) {
			s = &vertices[i];
		}
		i++;
	}
	// ^^ searching through a vertex vector for the source vector
    bool hit = false;
    queue<vertex*> q;
	q.push(s);
	s->prev = NULL;
	vertex* cur;
	while(!q.empty()) {
		cur = q.front();
		q.pop();
		cur->visited = true;
		if (cur->name == destination){
			break;
		}
		else {
    		for (int i = 0; (unsigned)i < cur->adj.size(); i++) {
    			if(!cur->adj[i].v->visited) {
    				cur->adj[i].v->visited = true;
    				q.push(cur->adj[i].v);
    				cur->adj[i].v->prev = cur;
    			}
    		}
    		// ^^ this for-loop is how you search through the graph and add vertices to the queue
		}
	}
	while (cur != NULL){
	    if (cur->name == intermediate){
	        hit = true;
	    }
	    cur = cur->prev;
	}
	if (!hit){
	    cout << "No" << endl;
	}
	else if (hit == true){
	    cout << "Yes" << endl;
	}
}

void Graph::printMislabeledParents(int startVertex) {
	vertex *start;
	for (int i = 0; i < (int)vertices.size(); i++) {
		vertices[i].visited = false;
		if (vertices[i].value == startVertex) {
			start = &vertices[i];
		}
	}
	queue<vertex*> Q;
	Q.push(start);
	start->visited = true;
	cout << start->value << endl;
	while (!Q.empty()) {
		vertex *cur = Q.front();
		Q.pop();
	    for (int i = 0; (unsigned)i < cur->adj.size(); i++){
	        if(!cur->adj[i].v->visited){
	            cur->adj[i].v->visited = true;
	            Q.push(cur->adj[i].v);
	            if (cur->adj[i].v->parentID != cur->value){
	                cout << cur->adj[i].v->value << endl;
	            }
	        }
	    }
	}
}

void Graph::findOddAdjacent(int startVertex) {
	vertex *start;
	for (int i = 0; i < (int)vertices.size(); i++) {
		vertices[i].visited = false;
		if (vertices[i].value == startVertex) {
			start = &vertices[i];
		}
	}
	queue<vertex*> Q;
	Q.push(start);
	start->visited = true;
	cout << start->value << " ";
	while (!Q.empty()) {
		vertex *cur = Q.front();
		Q.pop();
		for (int i = 0; i < (int)cur->adj.size(); i++) {
		    if (!cur->adj[i].v->visited){
		        cur->adj[i].v->visited = true;
		        Q.push(cur->adj[i].v);
		        if (cur->adj[i].v->value % 2 != 0){
		            cout << cur->adj[i].v->value << " ";
		        }
		    }
		}
	}
}

void Graph::findNodeWithMaximumAdjacent(int startVertex) {
	vertex *start;
	for (int i = 0; i < (int)vertices.size(); i++) {
		vertices[i].visited = false;
		if (vertices[i].value == startVertex) {
			start = &vertices[i];
		}
	}
	vertex* maxKey = start;
	queue<vertex*> q;
	q.push(start);
	start->visited = true;
	//cout << start->value << " ";
	while(!q.empty()) {
		vertex* cur = q.front();
		q.pop();
		cur->visited = true;
		cout << cur->value << " ";
		for (int i = 0; (unsigned)i < cur->adj.size(); i++) {
			if(!cur->adj[i].v->visited) {
				cur->adj[i].v->visited = true;
				q.push(cur->adj[i].v);
			}
		}
		if(cur->adj.size() > maxKey->adj.size()) {
			maxKey = cur;
		}
	}
	cout << endl;
	cout << maxKey->value << endl;
}

void traversal(TreeNode *node, char m, char n, vector<char> *nodes){
    if (node != NULL){
        traversal(node->left, m, n, nodes);
        if (node->key >= m && node->key <= n){
            nodes->push_back(node->key);
        }
        traversal(node->right, m, n, nodes);
    }
}

void RangeSearch(TreeNode *node, char m, char n){
    vector<char> nodes;
    traversal(node, m, n, &nodes);
    if (nodes.size() != 0){
        head = new Node();
        head->key = nodes[0];
        Node *temp = head;
        for (int i = 1; i < (int)nodes.size(); i++){
            temp->next = new Node();
            temp->next->key = nodes[i];
            temp = temp->next;
        }    
    }
}

// inserting a node in a bst

Node* insert(Node* root, int value){
    Node* tmp = root;
    Node* parent = NULL;  
    while (tmp != NULL){
        if (value > tmp->key){
            parent = tmp;
            tmp = tmp->right;
        }
        else {
            parent = tmp;
            tmp = tmp->left;
        }
    }
    if (value > parent->key){
        parent->right = new Node(parent, NULL, NULL);
        parent->right->parent = parent;
        parent->right->key = value;
        cout << "inserted: " << value << " right child of: " << parent->key << endl;
    }
    else {
        parent->left = new Node(parent, NULL, NULL);
        parent->left->parent = parent;
        parent->left->key = value;
        cout << "inserted: " << value << " left child of: " << parent->key << endl;
    }
    return root;
}



void Graph::colorVertices(string source){
    int i = 0;
    vertex* s;
	while ((unsigned)i < vertices.size()) {
		if (vertices[i].name == source) {
			s = &vertices[i];
		}
		i++;
	}
    queue<vertex*> q;
	q.push(s);
	s->color = "Red";
	vertex* cur;
	while(!q.empty()) {
		cur = q.front();
		q.pop();
		cur->visited = true;
    	for (int i = 0; (unsigned)i < cur->adj.size(); i++) {
    		if(!cur->adj[i].v->visited) {
				cur->adj[i].v->visited = true;
    	    	q.push(cur->adj[i].v);
    			if (cur->color == "Red"){
    			    cur->adj[i].v->color = "Black";
    			}
    			else if (cur->color == "Black"){
    			    cur->adj[i].v->color = "Red";
    			}
    		}
    	}
	}
}

void Graph::findVerticesWithNoAdjacentVertices(){
    vector<string> noAdj;
    for (int i = 0; i < (int)vertices.size(); i++){
        if ((int)vertices[i].adj.size() == 0){
            noAdj.push_back(vertices[i].name);
        }
    }
    if ((int)noAdj.size() == 0){
        cout << "Not Found!" << endl;
    }
    else {
        for (int i = 0; i < (int)noAdj.size(); i++){
            cout << noAdj[i] << " ";
        }
    }
}
// ACDFH

// 1) Create a set sptSet (shortest path tree set) that keeps track of vertices included in shortest path tree, i.e., whose minimum distance from source is calculated and finalized. Initially, this set is empty.
// 2) Assign a distance value to all vertices in the input graph. Initialize all distance values as INFINITE. Assign distance value as 0 for the source vertex so that it is picked first.
// 3) While sptSet doesn’t include all vertices
// ….a) Pick a vertex u which is not there in sptSetand has minimum distance value.
// ….b) Include u to sptSet.
// ….c) Update distance value of all adjacent vertices of u. To update the distance values, iterate through all adjacent vertices. For every adjacent vertex v, if sum of distance value of u (from source) and weight of edge u-v, is less than the distance value of v, then update the distance value of v.

bool Graph::ifPathExistsLessThanDist(string vertex1, string vertex2, int dist){
    vertex* s;
    for (int i = 0; i < (int)vertices.size(); i++){
        if (vertices[i].name == vertex1){
            s = &vertices[i];
            vertices[i].distance = 0;
        }
    }
    bool shortest = false;
    queue<vertex*> q;
    q.push(s);
    vertex* cur;
    while (!q.empty()){
        cur = q.front();
        q.pop();
        cur->visited = true;
        if (cur->name == vertex2){
            break;
        }
        for (int i = 0; i < (int)cur->adj.size(); i++){
            if (!cur->adj[i].v->visited){
                cur->adj[i].v->visited = true;
                q.push(cur->adj[i].v);
                cur->adj[i].v->distance = cur->distance + 1;
            }
        }
    }
    if (cur->distance >= dist){
        shortest = false;
    }
    else if (cur->distance < dist){
        shortest = true;
    }
    return shortest;
}

void replaceMaxWithMin(TreeNode *root){
    if (root != NULL){
        TreeNode* tmp = root;
        // TreeNode* parent = NULL;
        while (tmp->leftChild != NULL){
            // parent = tmp;
            tmp = tmp->leftChild;
        }
        TreeNode* min = tmp;
        tmp = root;
        while (tmp->rightChild != NULL){
            tmp = tmp->rightChild;
        }
        TreeNode* max = tmp;
        if (min->rightChild != NULL){
            min->parent->leftChild = min->rightChild;
            min->rightChild->parent = min->parent;
            min->rightChild = NULL;
        }
        else if (min->rightChild == NULL){
            min->parent->leftChild = NULL;
        }
        min->parent = max->parent;
        if (max == max->parent->rightChild){
            max->parent->rightChild = min;
        }
        else if (max == max->parent->leftChild){
            max->parent->leftChild = min;
        }
        max->parent = NULL;
        delete(max);
    }
}