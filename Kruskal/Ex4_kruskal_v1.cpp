#include <iostream>
using namespace std;
struct node
{
	int start;
	int end;
	int w;
	bool flag;
	struct node *next;
};
class Graph
{
	struct node *first;
	int n, m;
	int parent[20];
	int rank[20];
	
	public:
		Graph() {
			first = NULL;
		}
		void createGraph(){
			cout << "Enter number of vertices: ";
			cin >> n;
			cout << "Enter number of edges: ";
			cin >> m;
			for (int i=0; i<m; i++) {
				node* nn = new node();
				cout << "Enter the start vertex index: ";
				cin >> nn->start;
				cout << "Enter the end vertex index: ";
				cin >> nn->end;
				cout << "Enter the weight of the edge: ";
				cin >> nn->w;
				nn->flag = false;
				nn->next = NULL;
				if (first == NULL)
				    first = nn;
				else{
					if (first->w > nn->w){
						nn->next = first;
						first = nn;
					}
					else{
						node *temp = first;
						while (temp->next != NULL && temp->next->w < nn->w)
						     temp = temp->next;
						nn->next = temp->next;
						temp->next = nn;
					}
				}
			}
		}
		void display(){
			cout << "Edges of the Graph: " << endl;
			node *temp = first;
			while (temp != NULL){
				cout << temp->start << "-->" << temp->end << ": " << temp->w << endl;
				temp = temp->next;
			}
			cout << "Edges included in spanning tree: "<< endl;
			temp = first;
			int total_w = 0;
			while (temp != NULL){
				if (temp->flag){
				     cout << temp->start << "-->" << temp->end << ": " << temp->w << endl;
				     total_w += temp->w;
				}
				temp = temp->next;
			}
		}
		void make_set(int v){
			parent[v]=-1;
		}
		int find_set(int u){
			while (parent[u] != -1)
			    u = parent[u];
			return u;
		}
		void set_union(int x, int y){
			if (rank[x] > rank[y])
				parent[y] = x;
			else
		        parent[x] = y;
		        if (rank[x] == rank[y])
		           rank[y]++;
		}
		void MWST(){
			for (int u=1; u<=n; u++)
			   make_set(u);
			node *temp;
			temp = first;
			while (temp != NULL){
				int u = temp->start;
				int v = temp->end;
				int i = find_set(u);
				int j = find_set(v);
				if (i != j){
					temp->flag = true;
					set_union(i, j);
				}
				temp = temp->next;
			}
		}
};
int main(){
	Graph g;
	g.createGraph();
	g.MWST();
	g.display();
	return 0;
}
