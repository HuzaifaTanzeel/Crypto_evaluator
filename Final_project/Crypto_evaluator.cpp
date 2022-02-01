#include<iostream>
#include<sstream>
#include<fstream>
#include<string>
#include<iomanip>
#include <windows.h>
#define no_of_coins 27 

using namespace std;

class file_{
	public:
		string date;
		string open;
		string high;
		string low;
		string close;
		string vol;
		
};

class coin_node{
	public:
		string date;
		double open;
		double high;
		double low;
		double close;
		double volume; 
		coin_node* next;
		
		coin_node(){
			
		}
		coin_node(string date,double open, double high, double low, double close,double volume){
			this->date=date;
			this->open=open;
			this->high=high;
			this->low=low;
			this->close=close;
			this->volume=volume;
			next=NULL;
		}
		
};

class singlylinked{
	private:
		coin_node* head;
		coin_node* tail;
		int size;
		
		public:
			singlylinked()
	    	{ 
			    head=NULL;
			    tail=NULL;
			    size=0;
		    }
		    
		    int get_size()
		    {
		    	return size;
			}
		    void insertAtEnd(coin_node* n)
		    {

		    	if(head==NULL)
		    	{
		    		head=n;
		    		tail=n;
				}
				else
				{
					tail->next=n;
					tail=n;
				}
					
				size++;
			}
		    	
		   void traverse()
			{
				coin_node* temp;
				temp=head;
				while(temp!=NULL)
				{
					cout<<temp->date<<"  "<<temp->open<<"  "<<temp->close<<"  ";
					temp=temp->next;
				}
				cout<<endl;
			}
			
			~singlylinked()
			{
				coin_node* Next;
				if(head!=NULL)
				{
					Next=head->next;
					delete head;
					head=Next;
				}
			}
		
};


class coin_pnode{
	public:
		string coin_name;
		singlylinked s1;
		
		
		double day_percent_change;
		double day_highest;
		double day_lowest;
		double day_volume;
		double day_open;
		double day_close;
		double moving_avg;
		coin_pnode(){
			
		}
		coin_pnode(string st,coin_node *n){
			coin_name=st;
			s1.insertAtEnd(n);
			day_highest=n->high; 
			day_lowest=n->low;
			day_open=n->open;
			day_close=n->close;
			day_percent_change=((day_close-day_open)/day_open)*100;
			day_volume=n->volume;
			moving_avg=0;
			
		}
		
};

class coin_pointers 
{	
	public:
		coin_pnode **table;
	
		
		coin_pointers(){
				table=new coin_pnode*[no_of_coins];
				for(int i=0;i<no_of_coins;i++){
					table[i]=NULL;
				}
			}
			
			void insert(coin_node *n,int coin_no,string coin_label)
			{
				if(table[coin_no]==NULL){
					table[coin_no]=new coin_pnode(coin_label,n);
				}
				else{
					table[coin_no]->coin_name=coin_label;
					table[coin_no]->s1.insertAtEnd(n);
					table[coin_no]->day_close=n->close;
					table[coin_no]->day_percent_change=((table[coin_no]->day_close-table[coin_no]->day_open)/table[coin_no]->day_open)*100;
					table[coin_no]->day_volume+=n->volume;
					if(n->high>table[coin_no]->day_highest){
						table[coin_no]->day_highest=n->high;
					}
					if(n->low<table[coin_no]->day_lowest){
						table[coin_no]->day_lowest=n->low;
					}
				}
				
			}
			
			string get_coinname(int i){
				return table[i]->coin_name;
			}
			
			double get_per_change(int i){
				return table[i]->day_percent_change;
			}
			
			double get_highest(int i){
				return table[i]->day_highest;
			}
			double get_lowest(int i){
				return table[i]->day_lowest;
			}
			double get_volume(int i){
				return table[i]->day_volume;
			}
			double get_open(int i){
				return table[i]->day_open;
			}
			double get_close(int i){
				return table[i]->day_close;
			}
			void set_mov_avg(double m_avg,int i){
				table[i]->moving_avg=m_avg;
			}
			
			void printing(){
				cout << "COIN NAME\tOPEN PRICE\tCLOSE PRICE\tHIGHEST \tLOWEST";
				cout << "          VOLUME          CHANGE(%)" << endl;
				cout <<"____________________________________________________________________________________________________________" << endl;
				for(int i=0;i<no_of_coins;i++){
					cout << table[i]->coin_name << "\t";
					printf("%.5f \t", table[i]->day_open);
					printf("%.5f \t", table[i]->day_close);
					printf("%.5f \t", table[i]->day_highest);
					printf("%.5f \t", table[i]->day_lowest);
					printf("%.5f \t", table[i]->day_volume);
					printf("%.5f \n", table[i]->day_percent_change);
				}
			}
			
			void print_mov_avgs(){
				
				cout << "COIN NAME\tMOVING-AVG"<<endl;
				cout<<"__________________________"<<endl;
				
				for(int i=0;i<no_of_coins;i++){
					cout << table[i]->coin_name << "\t";
					cout<< table[i]->moving_avg<<endl;
				}
				
			}
};


class dayy{
	public:
		string coin_name;
		double day_percent_change;
		double day_highest;
		double day_lowest;
		double day_volume;
		double day_open;
		double day_close;
		
		dayy(){
		coin_name=" ";
		day_percent_change=0;
		day_highest=0;
		day_lowest=0;
		day_volume=0;
		day_open=0;
	    day_close=0;
}
	    dayy(string c_name,double per_change,double highst,double lowst,double vol,double opn,double clos){
	    	this->coin_name=c_name;
	    	this->day_percent_change=per_change;
	    	this->day_highest=highst;
			this->day_lowest=lowst;
			this->day_volume=vol;
			this->day_open=opn;
			this->day_close=clos;
		}
	
};


 class DynArrInt
{
	public:
		dayy **arr;
		
		
	public:
		// Constructor
		DynArrInt(){
			// Todo: check size can be zero or negative
			arr=new dayy*[no_of_coins];
			for(int i=0;i<no_of_coins;i++){
				arr[i]=NULL;
			}
				
		}
		
		void insertionn(int i,string c_name,double per_change,double highst,double lowst,double vol,double opn,double clos){
			arr[i]=new dayy(c_name,per_change,highst,lowst,vol,opn,clos);
		}
		
		
		void insertion_sort_volume(){
	
		for(int i=1;i<no_of_coins;i++){
			dayy* temp=arr[i];
			int j=i-1;
			while(j>=0 && arr[j]->day_volume<temp->day_volume){
				arr[j+1]=arr[j];
				j--;
			}
		arr[j+1]=temp;
	}
}

	void insertion_sort_advancers(){
	
		for(int i=1;i<no_of_coins;i++){
			dayy* temp=arr[i];
			int j=i-1;
			while(j>=0 && arr[j]->day_percent_change < temp->day_percent_change){
				arr[j+1]=arr[j];
				j--;
			}
		arr[j+1]=temp;
	}
}

	void insertion_sort_decliners(){
	
		for(int i=1;i<no_of_coins;i++){
			dayy* temp=arr[i];
			int j=i-1;
			while(j>=0 && arr[j]->day_percent_change > temp->day_percent_change){
				arr[j+1]=arr[j];
				j--;
			}
		arr[j+1]=temp;
	}
}
		void print(){
			cout << endl;
			cout << "COIN NAME\tCLOSE PRICE     CHANGE(%)     \tVOLUME"<<endl;
			cout <<"_________________________________________________________________" << endl;
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				for(int i=0;i<10;i++){
					if(arr[i]->day_percent_change > 0){	
						SetConsoleTextAttribute(hConsole, 10);
					}else{
						SetConsoleTextAttribute(hConsole, 12);
					}
				cout << arr[i]->coin_name << "\t";
				printf("%.5f \t", arr[i]->day_close);
				printf("%.5f \t", arr[i]->day_percent_change);
				printf("%.5f \n", arr[i]->day_volume);
			}
		}
		~DynArrInt(){
			delete [] arr;
		}
		
};

template<class T>
class AVLnode{
	public:
		string key;
		AVLnode<T>* left;
		AVLnode<T>* right;
		int height;
		coin_pointers cp;
		DynArrInt obj;
		AVLnode(){
			left=NULL;
			right=NULL;
			key=" ";
			
		}
		AVLnode(string d){
			key=d;
			left=right=NULL;
			height=1;
		}
};

template<class T>
class AVLtree{
	public:
		AVLnode<T>*root;
		AVLtree(){
			root=NULL;
		}
		
		friend bool operator ^(string,string);
		
		
		void print(){
			root->cp.printing();
		}
		int height(AVLnode<T> *N)
		{
			if (N == NULL){	
				return 0;
			}else{
				return N->height;
			}
		}
		
		int max(int a, int b)
		{
			return (a > b)? a : b;
		}
		
		
		AVLnode<T>* leftRotate(AVLnode<T>* x)
		{
			AVLnode<T>* y = x->right;
			AVLnode<T>* T2 = y->left;
	
			// Perform rotation
			y->left = x;
			x->right = T2;

			// Update heights
			x->height = max(height(x->left),height(x->right)) + 1;
			y->height = max(height(y->left),height(y->right)) + 1;

			// Return new root
			return y;
		}
		
		AVLnode<T>* rightRotate(AVLnode<T>* y)
		{
			AVLnode<T>* x = y->left;
			AVLnode<T>* T2 = x->right;

			// Perform rotation
			x->right = y;
			y->left = T2;

			// Update heights
			y->height = max(height(y->left),height(y->right)) + 1;
			x->height = max(height(x->left),height(x->right)) + 1;

			// Return new root
			return x;
		}
		
		int getBalance(AVLnode<T>* N)
		{
			if (N == NULL)
			return 0;
			return height(N->left)-height(N->right);
		}
		
		
		
		AVLnode<T>* insert(AVLnode<T>* node,coin_node* cn,int coin_no,string name)
		{
			/* 1. Perform the normal BST insertion */
			if (node == NULL)
			{
				
				node=new AVLnode<T>(cn->date);
				node->cp.insert(cn,coin_no,name);			//inserting coin_node in array of pointers
				return node;
			}
			

			if (node->key ^ cn->date)
			{
				node->left = insert(node->left,cn,coin_no,name);
			}
			
			else if (cn->date ^ node->key)
			{
				node->right = insert(node->right,cn,coin_no,name);
			}
			
			else if(cn->date==node->key){
				node->cp.insert(cn,coin_no,name);			//inserting coin_node in array of pointers
				return node;
			}
			

			/* 2. Update height of this ancestor node */
			node->height = 1 + max(height(node->left),height(node->right));

			/* 3. Get the balance factor of this ancestor
			node to check whether this node became
				unbalanced */
				int balance = getBalance(node);

			// If this node becomes unbalanced, then
			// there are 4 cases

			// Left Left Case
			if (balance > 1 &&  node->left->key ^ cn->date)
			return rightRotate(node);

			// Right Right Case
			if (balance < -1 && cn->date ^ node->right->key)
			return leftRotate(node);

			// Left Right Case
			if (balance > 1 && cn->date ^ node->left->key)
			{
				node->left = leftRotate(node->left);
				return rightRotate(node);
			}

			// Right Left Case
			if (balance < -1 &&  node->right->key ^ cn->date)
			{
				node->right = rightRotate(node->right);
				return leftRotate(node);
			}

			/* return the (unchanged) node pointer */
			return node;
		}
		
		AVLnode<T> *search_date(string date, AVLnode<T>* R){
			if(R == NULL ){
				cout<<"NO DATA FOUND !!!" << endl;
				return NULL;
			}
			
			if(R->key ^ date){
				R = search_date(date, R->left);
				return R;
			}
			else if(date ^ R->key){
				R = search_date(date, R->right);
				return R;
			}
			
			return R;
		}
		
		void searching(string dat){
			AVLnode<T>*temp=search_date(dat,root);
			if(temp == NULL){
				return;
			}
			temp->cp.printing();
		}
		
		
		void top_active(string dat){
			AVLnode<T>*temp=search_date(dat,root);
			if(temp == NULL){
				cout << "DATA NOT FOUND !!!" << endl;
				return;
			}
			
			for(int i=0;i<no_of_coins;i++){
					temp->obj.insertionn(i,temp->cp.get_coinname(i),temp->cp.get_per_change(i),temp->cp.get_highest(i),temp->cp.get_lowest(i),temp->cp.get_volume(i),temp->cp.get_open(i),temp->cp.get_close(i));	
				}
			
			
			temp->obj.insertion_sort_volume();
			temp->obj.print();
			
		}
		
		void top_advancers(string dat)
		{
			AVLnode<T>*temp=search_date(dat,root);
			if(temp == NULL){
				return;
			}
			for(int i=0;i<no_of_coins;i++){
				temp->obj.insertionn(i,temp->cp.get_coinname(i),temp->cp.get_per_change(i),temp->cp.get_highest(i),temp->cp.get_lowest(i),temp->cp.get_volume(i),temp->cp.get_open(i),temp->cp.get_close(i));	
			}
			temp->obj.insertion_sort_advancers();
			temp->obj.print();
			
		}
		
		void top_decliners(string dat)
		{
			AVLnode<T>*temp=search_date(dat,root);
			if(temp == NULL){
				return;
			}
			for(int i=0;i<no_of_coins;i++){
				temp->obj.insertionn(i,temp->cp.get_coinname(i),temp->cp.get_per_change(i),temp->cp.get_highest(i),temp->cp.get_lowest(i),temp->cp.get_volume(i),temp->cp.get_open(i),temp->cp.get_close(i));	
			}
			temp->obj.insertion_sort_decliners();
			temp->obj.print();			
		}

		double print_order(string date, AVLnode<T> *R, int i){
			static int count=0;
			static double sum=0;
			if(R == NULL || count == 5 ){
				return sum;
			}
			
			double val = print_order(date, R->right,i);
			sum = sum + R->cp.get_close(i);
			count++;
			val = print_order(date, R->left,i);
			return val;
			
		}
		
		void cal_SMA(string date){    			//Simple moving average 
			
			AVLnode<T> *temp = search_date(date, root);
			for(int i=0;i<no_of_coins;i++){
				double no=print_order(date, temp,i);
				double x=no/5;
				//cout << temp->cp.get_coinname(i) << "  ";
				temp->cp.set_mov_avg(x,i);				
			}
		}
		
		void print_movingaveragesfinal(string date){
			AVLnode<T> *temp = search_date(date, root);
			cout << "Moving average of 5 days: " << endl;
			temp->cp.print_mov_avgs();
		}
		
		
};


bool operator ^(string s1,string s2)
{
		bool flag1=0,flag2=0,flag3=0;
	int count=0;
	string year1,month1,day1;
	string year2,month2,day2;
	int y1,m1,d1;
	int y2,m2,d2;

	
	for(int i=0;i<s1.length();i++){
		
		if(s1[i]=='/' || s1[i]=='-'){
			count++;
			if(count==1){
				flag1=true;
			}
			else if(count==2){
				flag2=true;
			}
			else{
				flag3=true;
			}
		}
		if(s1[i]!='/' && s1[i]!='-' && flag1!=true){
			year1+=s1[i];
		}
		else if(s1[i]!='/' && s1[i]!='-' && flag2!=true){
			month1+=s1[i];
		}
		else if(s1[i]!='/' && s1[i]!='-' && flag3!=true){
			day1+=s1[i];
		}
	}
	
	flag1=0,flag2=0,flag3=0;
	count=0;
	for(int i=0;i<s2.length();i++){
		
		if(s2[i]=='/' || s2[i]=='-'){
			count++;
			if(count==1){
				flag1=true;
			}
			else if(count==2){
				flag2=true;
			}
			else{
				flag3=true;
			}
		}
		if(s2[i]!='/' && s2[i]!='-' && flag1!=true){
			year2+=s2[i];
		}
		else if(s2[i]!='/' && s2[i]!='-' && flag2!=true){
			month2+=s2[i];
		}
		else if(s2[i]!='/' && s2[i]!='-' && flag3!=true){
			day2+=s2[i];
		}
	}
	
	istringstream(year1)>>y1;
	istringstream(month1)>>m1;
	istringstream(day1)>>d1;
	
	istringstream(year2)>>y2;
	istringstream(month2)>>m2;
	istringstream(day2)>>d2;
	
	
	
	if(y1>y2)return true;
	if(y1<y2)return false;
	if(m1>m2)return true;
	if(m1<m2)return false;
	if(d1>d2)return true;
	if(d1<d2)return false;
	return false;
	
}


void data_loading(AVLtree <string>&Ab){
	
	string f_s[42];
	f_s[0] = "ADABTC1.csv";
	f_s[1] = "BNBBTC1.csv";
	f_s[2] = "CDTBTC1.csv";
	f_s[3] = "CNDBTC1.csv";
	f_s[4] = "DASHBTC1.csv";
	f_s[5] = "EOSBTC1.csv";
	f_s[6] = "ETCBTC1.csv";
	f_s[7] = "ETHBTC1.csv";
	f_s[8] = "FUNBTC1.csv";
	f_s[9] = "GASBTC1.csv";
	f_s[10] = "IOTABTC1.csv";
	f_s[11] = "IOTXBTC1.csv";
	f_s[12] = "LTCBTC1.csv";
	f_s[13] = "LUNBTC1.csv";
	f_s[14] = "MANABTC1.csv";
	f_s[15] = "MCOBTC1.csv";
	f_s[16] = "NANOBTC1.csv";
	f_s[17] = "WTCBTC1.csv";
	f_s[18] = "POWRBTC1.csv";
	f_s[19] = "LRCBTC1.csv";
	f_s[20] = "ARKBTC1.csv";
	f_s[21] = "KMDBTC1.csv";
	f_s[22] = "RDNBTC1.csv";
	f_s[23] = "XMRBTC1.csv";
	f_s[24] = "QSPBTC1.csv";
	f_s[25] = "XVGBTC1.csv";
	f_s[26] = "TRXBTC1.csv";
	f_s[27] = "TUSDBTC1.csv";
	f_s[28] = "USDCBTC1.csv";
	f_s[29] = "VENBTC1.csv";
	f_s[30] = "VETBTC1.csv";
	f_s[31] = "VIBBTC1.csv";
	f_s[32] = "VIABTC1.csv";
	f_s[33] = "VIBEBTC1.csv";
	f_s[34] = "WABIBTC1.csv";
	f_s[35] = "WANBTC1.csv";
	f_s[36] = "WAVESBTC1.csv";
	f_s[37] = "WINGSBTC1.csv";
	f_s[38] = "WPRBTC1.csv";
	f_s[39] = "XEMBTC1.csv";
	f_s[40] = "XLMBTC1.csv";
	f_s[41] = "XRPBTC1.csv";
	
	double high_;
	double low_;
	double open_;
	double close_;
	double volume_;
	
	file_ obj;
	
	fstream openFile;
	
	for(int i=0;i<no_of_coins;i++){
		openFile.open(f_s[i], ios::in);
	while(!openFile.eof()){
		getline(openFile, obj.date, ',');
		getline(openFile, obj.open, ',');
		getline(openFile, obj.high, ',');
		getline(openFile, obj.low, ',');
		getline(openFile, obj.close, ',');
		getline(openFile, obj.vol, '\n');
		obj.date.erase(obj.date.begin() + 11, obj.date.end());
		istringstream(obj.open) >> open_;
		istringstream(obj.high) >> high_;
		istringstream(obj.close) >> close_;
		istringstream(obj.low) >> low_;
		istringstream(obj.vol) >> volume_;
		coin_node *C= new coin_node(obj.date,open_,high_,low_,close_,volume_ );
		Ab.root=Ab.insert(Ab.root,C,i,f_s[i]);
		
	}
	openFile.close();
		cout<<"File : "<<i<<" read successfully "<<endl;
	}
	cout << endl;
	
}

void main_menu(AVLtree <string>&Ab){
	int option;
	string date;
	while(1){
		system("CLS");
	    system("Color 06");
		cout << "1. General Statistics" << endl;
		cout << "2. Top Active Coins" << endl;
		cout << "3. Top Advancers" << endl;
		cout << "4. Top Decliners" << endl;
		cout << "5. Indicators" << endl;
		cout << "6. Exit" << endl;
		cout << endl;
		cout << "Choose Option: ";
		cin >> option;
		switch(option){
			case 1:{
				cout << "General Statistics" << endl;
				cout << "Enter a date: (format : yyyy-mm-dd)" << endl;
				cin >> date;
				Ab.searching(date);
				system("pause");
				break;
			};
			case 2:{
				cout << "Top Active coin" << endl;
				cout << "Enter a date: (format : yyyy-mm-dd)" << endl;
				cin >> date;
				Ab.top_active(date);
				system("pause");
				break;
			}
			case 3:{
				cout << "Top Advancers" << endl;
				cout << "Enter a date: (format : yyyy-mm-dd)" << endl;
				cin >> date;
				Ab.top_advancers(date);
				system("pause");
				break;
			}
			case 4:{
				cout << "Top Decliners" << endl;
				cout << "Enter a date: (format : yyyy-mm-dd)" << endl;
				cin >> date;
				Ab.top_decliners(date);
				system("pause");
				break;
			}
			case 5:{
				cout << "Indicators" << endl;
				cout << "Enter a date: (format : yyyy-mm-dd) to calculate moving average" << endl;
				cin >> date;
				Ab.cal_SMA(date);
				Ab.print_movingaveragesfinal(date);
				system("pause");
				break;
			}
			case 6:{
				cout << "Exiting" << endl;
				exit(0);
				break;
			}
			default:{
				cout << "Enter again" << endl;
			}
		};
	}
}


int main(){
	AVLtree<string>Ab;
	data_loading(Ab);
	main_menu(Ab);
}


