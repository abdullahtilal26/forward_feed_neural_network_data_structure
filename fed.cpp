#include<iostream>
#include<string.h>
#include<cmath>
#include<time.h>
#include<stdlib.h>
#include<stdint.h>
#include<vector>
#include <bits/stdc++.h> 
using namespace std;

double sigmoid(double x){
		return (1/(1+exp(-x)));
	}
double der_sigmoid(double x){
	return x*(1-x);
}

//template<class t>
class matrix{
	private:
		
		int rows,col;
		vector<vector<double> > data;
		
	public:
		
	matrix(int r,int c){
		rows=r;
		col=c;
		data.resize(rows);
		for(int i=0;i<rows;i++){
			data[i].resize(col);
		}
		
		for(int i=0;i<rows;i++){
			for(int j=0;j<col;j++){
			data[i][j]=0;
			}
		}
	
	}
	
	matrix(){
		rows=1;
		col=1;
		
		data.resize(rows);
		for(int i=0;i<rows;i++){
			data[i].resize(col);
		}
		
		for(int i=0;i<rows;i++){
			for(int j=0;j<col;j++){
			data[i][j]=0;
			}
		}
	
			
	}
	
	matrix(const matrix &rhs){
		this->rows=rhs.rows;
		this->col=rhs.col;
		this->data=rhs.data;
	}

	matrix& operator=(const matrix &rhs){
		if(this!=&rhs){
		this->rows=rhs.rows;
		this->col=rhs.col;
		
		data.resize(this->rows);
		for(int i=0;i<this->rows;i++){
			this->data[i].resize(this->col);
		}
		
		for(int i=0;i<this->rows;i++){
			for(int j=0;j<this->col;j++){
				data[i][j]=rhs.data[i][j];
			}
		}
		return *this;
		
	}

}

void copy_data(const vector<vector<double> > &rhs){
		//if(this!=&rhs){
		this->rows=rhs.size()-1;
		this->col=rhs[0].size();
	
		data.resize(this->rows);
		for(int i=0;i<this->rows;i++){
			this->data[i].resize(this->col);
		}
		
		for(int i=0;i<this->rows;i++){
			for(int j=0;j<this->col;j++){
				data[i][j]=rhs[i][j];
			}
		
		}
		
}

void copy_data_rev(const vector<double> &rhs){
		//if(this!=&rhs){
		//cout<<"copy"<<rhs.size();
		this->rows=rhs.size();
		this->col=1;
	
		data.resize(this->rows);
		for(int i=0;i<this->rows;i++){
			this->data[i].resize(this->col);
		}
		
		for(int i=0;i<this->rows;i++){
			// for(int j=0;j<this->col;j++){
				data[i][0]=rhs[i]/255;
			//}
		
		}
		
}

void copy_val(const double val){
	for(int i=0;i<this->rows;i++){
		if(i==val){
			this->data[i][0]=1;//val
		}	
		else
		{
			this->data[i][0]=0;
		}
		
	}
}

	void randomize(){
	srand((unsigned)time(NULL));
		for(int i=0;i<this->rows;i++){
			for(int j=0;j<this->col;j++){
				this->data[i][j]=((double)rand()/RAND_MAX)*2-1;//double
			}
		}
	}

	matrix multiply(const double n) {
		matrix result(this->rows,this->col);
		
   		 for (int i = 0; i < rows; i++) {
     		 for (int j = 0; j < col; j++) {
        		result.data[i][j]=(this->data[i][j])*n;
      		}
    	}
		return result;
  	}

	matrix multiply_hadamard(const matrix &rhs) {
		matrix result(rows,col);
   		 for (int i = 0; i < rows; i++) {
     		 for (int j = 0; j < col; j++) {
        		result.data[i][j] = this->data[i][j]*rhs.data[i][j];
      		}
    	}
		return result;
  	}

	matrix product(const matrix &a,const matrix &b){
		matrix result(a.rows,b.col);
		//cout<<"--"<<result.rows<<result.col<<"--";
		if(a.col!=b.rows){
			cout<<"---mismatch----";
			return result;
		}
		else if(a.col==b.rows){
			
//			cout<<"kutta"<<endl;
			for(int i=0;i<result.rows;i++){
//				cout<<"l2";
				for(int j=0;j<result.col;j++){
					double sum=0;               //float
					// data[i][j]*=rhs.data[i][j];
//						cout<<"l3";
					for(int k=0;k<a.col;k++){
						sum =sum+((a.data[i][k])*(b.data[k][j]));
					}
					result.data[i][j]=sum;
				}
			}	
			//result.display();
//			cout<<"cute";
			return result;
			
		}
		cout<<"why u here?";
				
	}
	matrix transpose(const matrix &rhs){
		matrix result(rhs.col,rhs.rows);
		for(int i=0;i<rhs.rows;i++){
			for(int j=0;j<rhs.col;j++){
				result.data[j][i]=rhs.data[i][j];
			}
		}

		return result;	
	}
	
	matrix add(const matrix &rhs){
		
		matrix result(rhs.rows,rhs.col);
		
		if(this->rows==rhs.rows&&this->col==rhs.col){
		
//			cout<<"ASs";
		
			for(int i=0;i<rhs.rows;i++){
				for(int j=0;j<rhs.col;j++){
					result.data[i][j] = this->data[i][j]+rhs.data[i][j];
				}
			}
//			cout<<"??";
//			result.display();
				return result;
		}
		else{
			cout<<"error";
		}
		
	}

	matrix subtract(const matrix &a,const matrix &b){
		matrix result(a.rows,a.col);
		
			for(int i=0;i<result.rows;i++){
				for(int j=0;j<result.col;j++){
					result.data[i][j] = a.data[i][j]-b.data[i][j];
				}
			}

			return result;
	}

	 void map(){
		for(int i=0;i<rows;i++){
			for(int j=0;j<col;j++){
				double val =data[i][j];    //double
				this->data[i][j]=sigmoid(val);
			}
		}
	}

	void map_der(){
		for(int i=0;i<rows;i++){
			for(int j=0;j<col;j++){
				double val =data[i][j];    //double
				this->data[i][j]=der_sigmoid(val);
			}
		}
	}




	void display(){
		//cout<<"display: "<<endl;
		for(int i=0;i<rows;i++){
			for(int j=0;j<col;j++){
				cout<<this->data[i][j]<<"**";
			}
			cout<<endl;
		}
		cout<<endl;
	}


	friend istream& operator>>(istream& infile, matrix & rhs)
	{
		for (int i=0;i<rhs.rows;i++){
			for(int j=0;j<rhs.col;j++){
				infile>>rhs.data[i][j];
			}
		}
    	return infile;
	}

	 ~matrix(){//cout<<"destructor";
	 }

//						 for(int i = rows-1;i>=0;i--) {
//						 	if (*(data+i)!=0)
//						 	{
//						 		delete [] *(data+i);
//						 		*(data+i)=0;
//						 	}
//						 }
//						 delete[] data;
//						 data=0;
		//cout<<"delete";
		//delete [] data;
//	}
	void Resize(int r,int c){
		rows=r;
		col=c;
		data.resize(r);
		for(int i=0;i<r;i++){
			data[i].resize(c);
		}

		for(int i=0;i<rows;i++){
			for(int j=0;j<col;j++){
			data[i][j]=0;
			}
		}
	}

	int max(){
		double max_val=this->data[0][0];
		int num=0;
		for(int i=0;i<this->rows;i++){
			if(this->data[i][0]>max_val){
				max_val=this->data[i][0];
				num=i;
			}
				
		}

		cout<<" predicted: "<<num<<" %: "<<(max_val/1)*100;
		return num;
	}
	void save(){
	ofstream myfile ("w.txt");
	if (myfile.is_open())
	{
		int i=0;
		while(i<rows){
			for(int j=0;j<col;j++){
				myfile<<data[i][j];
				myfile<<",";
			}
			myfile<<"\n";
			i++;
			
		}
		myfile.close();
	}
		
	}

	// void delete_all(){
	// 	for(int i = rows-1;i>=0;i--) {
	// 		 if (*(data+i)!=0)
	// 		 {
	// 			delete [] *(data+i);
	// 			*(data+i)=0;
	// 		 }
	// 	 }
	// 	 delete[] data;
	// 	 data=0;
	// }
	
};
//template<class t>
class neuralnetwork{
	private:
		int input_nodes,hidden_nodes,output_node;
		matrix weight_ih;matrix weight_ho;
		matrix bias_h;matrix bias_o;
		double learning_rate;
	public:
	
	neuralnetwork(int input_n,int hidden_n,int output_n){
		input_nodes=input_n;
		hidden_nodes=hidden_n;
		output_node=output_n;
		
		weight_ih.Resize(hidden_nodes,input_nodes);
		weight_ho.Resize(output_node,hidden_nodes);

        weight_ih.randomize();
        weight_ho.randomize();

		bias_h.Resize(hidden_nodes,1);
		bias_o.Resize(output_node,1);

		bias_h.randomize();
		bias_o.randomize();

		learning_rate=0.1;

		weight_ih.save();
		int a;
		cin>>a;

	}
	
	
	matrix feedforward(matrix &input){
		matrix hidden(1,1);
		hidden=hidden.product(weight_ih,input);
		hidden=hidden.add(bias_h);
		hidden.map();

		matrix outputt(1,1);
		outputt=outputt.product(weight_ho,hidden);
		outputt=outputt.add(bias_o);
		outputt.map();
		
		return outputt;
	}

	void train(matrix &input,matrix &targets){
		
		matrix hidden;
		hidden=hidden.product(weight_ih,input);
	
		hidden=hidden.add(bias_h);
	
		hidden.map();
		
		//second layer
		matrix output;
		output=output.product(weight_ho,hidden);
		output=output.add(bias_o);
		output.map();
		
		
//--------------------------------------------
	///	cout<<"2";
		//hidden to output backprog
		//matrix<double> output=feedforward(input);
		//calculating output error
		matrix output_errors;
		output_errors=output_errors.subtract(targets,output);
		

		//gradint                        //hadamard
		//output->map_der();
		matrix gradient;
		gradient=output;
		gradient.map_der();
		gradient=gradient.multiply_hadamard(output_errors);
		gradient=gradient.multiply(learning_rate);

		//gradient delta
		matrix hidden_T;
		hidden_T=hidden_T.transpose(hidden);
		matrix weight_ho_delta;
		weight_ho_delta=weight_ho_delta.product(gradient,hidden_T);

		//adjust weights
		weight_ho=weight_ho.add(weight_ho_delta);
		//adjust biases
		bias_o=bias_o.add(gradient);
		
//-------------------------------------------------------
//	cout<<"3";
		//input to hidden backprog


		//calculating hidden erros:
		matrix weight_ho_trans=weight_ho_trans.transpose(weight_ho);
		matrix hidden_error=hidden_error.product(weight_ho_trans,output_errors);
	//	hidden_error.display();
		
		//calculatung  gradient for input lyaer
		matrix hidden_gradient=hidden;
		hidden_gradient.map_der();
		hidden_gradient=hidden_gradient.multiply_hadamard(hidden_error);
		hidden_gradient=hidden_gradient.multiply(learning_rate);

		//calculatig of gradient delta of input layer
		matrix input_T=input_T.transpose(input);
		matrix weight_ih_delta=weight_ih_delta.product(hidden_gradient,input_T);

		//adjust weights
		weight_ih=weight_ih.add(weight_ih_delta);
		//adjust bias
		bias_h=bias_h.add(hidden_gradient);
		

	}
	
	void display_all(){
		cout<<"**************************";
		cout<<"display weight ih:"<<endl;
		weight_ih.display();
		cout<<"display weight ho:"<<endl;
		weight_ho.display();
		cout<<"display bias ih:"<<endl;
		bias_h.display();
		cout<<"display bias ho:"<<endl;
		bias_o.display();
	}

	
	
};

int main(){
	//***********************************************

	ifstream input("mnist_test.csv");
	vector< vector<double> > data_test;
	vector<double> label_test;
	int row=0,col=0;
	while(input.good()){
		
		string val;
		getline(input,val,'\n');
		if(row!=0){
			stringstream ss(val);
			string inp;
			vector<double> dat_row;
			while(getline(ss,inp,',')){
				if(col==0)
					label_test.push_back(stod(inp));
				else
					dat_row.push_back(stod(inp));
				col++;
			}

			data_test.push_back(dat_row);
				
			if(col==785){
				col=0;
				row++;
			}
		}
		else{
			row++;
		}
	}
	input.close();
	//***********************************************
	ifstream input2("mnist_train.csv");
		vector< vector<double> > data_train;
		vector<double> label_train;
		//int 
		row=0,col=0;
		while(input2.good()){
			
			string val2;
			getline(input2,val2);
			if(row!=0){
				stringstream ss2(val2);
				string inp2;
				vector<double> dat_row2;
				while(getline(ss2,inp2,',')){
					if(col==0)
						label_train.push_back(stod(inp2));
					else
						dat_row2.push_back(stod(inp2));
					col++;
				}

				data_train.push_back(dat_row2);
					
				if(col==785){
					col=0;
					row++;
				}
			}
			else{
				row++;
			}
		}
		input2.close();
	//**********************************************

neuralnetwork nn(784,30,10);
	
fflush(stdin);	
// //cout<<label[0];
// matrix input_arr;
// input_arr.copy_data(data);
// // input_arr.display();
// matrix target_arr;
//target_arr.copy_data(label);
	for(int	i=0;i<60000;i++){

			matrix input_arr;
			input_arr.copy_data_rev(data_train[i]);

			matrix target_arr(10,1);
			target_arr.copy_val(label_train[i]);
			//cout<<i<<endl;
			nn.train(input_arr,target_arr);
			cout<<i<<endl;
		/**if(i==10000||i==20000||30000||40000||50000){
			for(int i=0;i<100;i++){
			
			cout<<"target: "<<label_test[i];
			// fflush(stdin);
			matrix input_arrr;
			input_arrr.copy_data_rev(data_test[i]);
			nn.feedforward(input_arrr).max();
			cout<<endl;

			}
		}*/
	}
//cout<<"complete";
//srand(time(0));
int success=0,fail=0;
	for(int i=0;i<10000;i++){
			
			cout<<"target: "<<label_test[i];
			// fflush(stdin);
			matrix input_arrr;
			input_arrr.copy_data_rev(data_test[i]);
			if(nn.feedforward(input_arrr).max()==label_test[i]){
				success++;
			}
			else
			{
				fail++;
			}
			
			cout<<endl;

		}

	cout<<"***Total % of successfull prediction: "<<success<<" "<<double((success/10000)*100)<<" fail: "<<fail<<" ***";
	
}
