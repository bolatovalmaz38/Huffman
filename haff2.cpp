#include <iostream>
#include <string>
#include <fstream>
#include <set>
using namespace std;
string S;
int K = 1;
int KK = 0;
struct Node{
	char sym;
	int freq;
	Node *left;
	Node *right;
};
class priority_queue_min{
private:
	Node **heap;
	int heap_size;
	int max_size;
	void sift_up(int z);
	void sift_down(int z);
public:
	priority_queue_min(int n);
	priority_queue_min(int n, char *symbols, int *freqs);
	~priority_queue_min();
	Node *extract_min();
	void insert(Node *new_elem);
	Node *build_haffman_tree();
	Node *f(int k){
		return heap[k];
	}
	void print(){
		int i;
		for (i = 1; i <= heap_size; i++)
			cout << heap[i]->sym << " - " << heap[i]->freq << "\n";
	}
	void print_tree(Node *r, string s){
		string ss;
		if (r->left != NULL || r->right != NULL){
			ss = s;
			if (r->left != NULL){
				s += "0";
				print_tree(r->left, s);
			}
			s = ss;
			if (r->right != NULL){
				s += "1";
				print_tree(r->right, s);
			}
		}
		else 
			cout << r->sym << " " << s << "\n";
	}
	void Code(Node *r, string code, char *ch, string *mad, int *m) {
	        if (r->left != NULL || r->right != NULL) {
	            Code(r->left, code + "0", ch, mad, m);
	       	    Code(r->right, code + "1", ch, mad, m);
	       	}
		else{
			ch[K] = r->sym;
			mad[K] = code;
			m[K] = r->freq;
			K++;
		}
	}
	void tree_walk(Node *r, string s, char &k);
};
priority_queue_min :: priority_queue_min (int n){
		heap = new Node*[1000];
		for(int i = 1; i <= 1000; i++)
			heap[i] = new Node;
		heap_size = n;
		for(int i = 1; i <= n; i++)
			heap[i]->freq = 0;
	}
priority_queue_min :: priority_queue_min(int n, char *symbols, int *freqs){
		heap = new Node*[1000];
		max_size = 1000;
		int i;
		for(i = 0; i <= 1000; i++){
			heap[i] = new Node;
			heap[i]->left = NULL;
			heap[i]->right = NULL;
		}
		heap_size = n;
		for(i = 1; i <= n; i++)
			heap[i]->freq = freqs[i];
		for(i = 1; i <= n;i++)
			heap[i]->sym = symbols[i];
		for(i = 1; i <= n; i++)
			sift_up(i);
}
priority_queue_min :: ~priority_queue_min(){
	for (int i = 0; i <= heap_size; i++)
			delete heap[i];
	delete []heap;
}
Node* priority_queue_min :: extract_min(){
	Node *ans = heap[1];
	heap[1] = heap[heap_size];
	heap_size -= 1;
	sift_down(1);
	return ans;	
}
void priority_queue_min :: insert(Node *new_elem){
	int i;
	Node* temp[heap_size];
	for(i = 1; i <= heap_size; i++)
		temp[i] = new Node;
	for(i = 1; i <= heap_size; i++)
		temp[i] = heap[i];
	for(i = 1; i <= heap_size;i++)
		heap[i+1] = temp[i];
	heap[heap_size+2] = new_elem;
	heap_size++;
	for(i = 1; i <= heap_size; i++)
		heap[i]=heap[i+1];
	for(i = heap_size / 2 ; i >= 1; i--)
		sift_down(i);
}
void priority_queue_min :: sift_up(int z){
	int l = z;
	Node *c;
	if(z == 1 || heap[z]->freq >= heap[z / 2]->freq)
		return;
	if(heap[z]->freq < heap[z / 2]->freq)
	{
		c = heap[z];
		heap[z] = heap[z/2];
		heap[z/2] = c;
		z = z/2;
	}
	sift_up(z);
}
void priority_queue_min :: sift_down(int z){
	int m = 2 * z;
	Node *t;
	if(2 * z > heap_size || (2 * z + 1 > heap_size && heap[z]->freq <= heap[2 * z]->freq) || (heap[z]->freq <= heap[2 * z]->freq && heap[z]->freq <= heap[2 * z + 1]->freq))
		return;
	if (2 * z + 1 <= heap_size && heap[2 * z]->freq	> heap[2 * z + 1]->freq)
		m = 2 * z + 1;
	t = heap[z];
	heap[z] = heap[m];
	heap[m] = t;
	sift_down(m);
}
Node* priority_queue_min :: build_haffman_tree(){
	Node *t1, *t2;
	Node *r;
	while (heap_size >= 2){
		t1 = extract_min();
		t2 = extract_min();
		r = new Node;
		r->left = t1;
		r->right = t2;
		r->freq = t1->freq + t2->freq;
		insert(r);
	}
}
void priority_queue_min :: tree_walk(Node *r, string s, char &k){
	if (r->left == NULL && r->right == NULL){
		k = r->sym;
	}
	else{
		if (s[KK] == '0'){
			KK++;
			tree_walk(r->left, s, k);
		}
		else{
			KK++;
			tree_walk(r->right, s, k);
		}
	}
}
int main(){
	unsigned long long h, k, j, n, N, i;
	int *m;
	char *c, o;
	string S;
	ofstream fout("tablo.txt");
	ofstream foutt("code.txt");
	ofstream fouttt("decode.txt");
	ofstream foutttt("Code.txt");
	ofstream fouttttt("Decode.txt");
	FILE *f;
	f = fopen("input2.txt", "r");
	o = fgetc(f);
	while( o != EOF ){	
		S += o;
		o = fgetc(f);
	}
	fouttttt << S;
	set <char> ss;
	for (i = 0; i < S.length()-1; i++)
		ss.insert(S[i]);
	set<char>::iterator it;
	N = ss.size();
	c = new char[N+1];
	for (it = ss.begin(), j = 1; it != ss.end(); j++, it++)
		c[j] = *it;
	m = new int[N+1];
	for (j = 1; j <= N; j++){
		k = 0;
		for (i = 0; i < S.length()-1; i++)
			if (c[j] == S[i])
				k++;
		m[j] = k;
	}
	string s;
	string *mad;
	mad = new string[N+1];
	priority_queue_min kucha(N, c, m);
	kucha.build_haffman_tree();
	kucha.Code(kucha.f(1), s, c, mad, m);
	fout << N << ' ' << S.length()-1 << endl;
	for(i = 1; i <= N; i++)
		if (c[i] != ' ')
			fout << c[i] << ' ' << mad[i] << ' ' << m[i] << endl;
		else
			fout << '_' << ' ' << mad[i] << ' ' << m[i] << endl;
	s = "";
	for (i = 0; i < S.length()-1; i++){
		for (j = 1; j <= N; j++){
			if (S[i] == c[j])
				s += mad[j];
		}
	}
	foutttt << s << endl;
	k = s.length();
	int flag = 0, u;
	if (k % 8 == 0)
		k /= 8;
	else{
		flag = k % 8;
		k /= 8;
		k++;
	}
	char *w;
	w = new char[k];
	for (i = 0; i < k; i++)
		w[i] = '\0';
	for (i = 0; i < s.length(); i++){
		if (s[i] == '1'){
			u = i / 8;
			w[u] |= 1 << (7-i%8);
		}
	} 
	for (i = 0; i < k; i++)
		foutt << w[i];
	foutt << endl;
	string SS, s_code;
	FILE *ff = fopen("code.txt", "r");
	o = fgetc(ff);
	i = 0;
	while(i < k){	
		i++;
		SS += o;
		o = fgetc(ff);
	}
	int maxsize = SS.length() * 8 - flag;
	for (i = 0; i < maxsize; i++){
		u = i / 8;
		if ((SS[u] ^ (1 << (7-i%8))) > SS[u])
			s_code += '0';
		else
			s_code += '1';
	}
	char chh;
	for (; KK < s_code.length();){
		kucha.tree_walk(kucha.f(1), s_code, chh);
		fouttt << chh;
	}
	fouttt << endl;
	return 0;
}
