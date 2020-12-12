#include<iostream>
#include<string.h>
#include<cmath>
#include<time.h>
#include<stdlib.h>
#include<stdint.h>
#include<vector>
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
		//cout<<"train"<<endl;
		//fflush(stdin);
		//input.display();
		//first layer
//		input.display();
//		targets.display();
		matrix hidden;
		hidden=hidden.product(weight_ih,input);
	//	hidden.display();
	//	cout<<"c2";
//		hidden.display();
//		bias_h.display();
		hidden=hidden.add(bias_h);
		//cout<<"c3";
	//	hidden.display();
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


//	 matrix a(3,1);
//	 cin>>a;
//	  matrix aa(3,1);
//	 cin>>aa;
//	 a.add(aa).display();
	// a.randomize();
	// a.display();
	// matrix c(1,4);
	// cin>>c;
	// a.product(a,c).display();
	// a.display();
	// matrix b;
	// b=a;
	// a.multiply_hadamard(b.multiply(8)).display();
	// b.display();
	neuralnetwork nn(2,2,1);
	
	matrix input_arr[4];
	matrix target_arr[4];
	for(int i=0;i<4;i++){

	//	fflush(stdin);
		matrix input(2,1);
		fflush(stdin);
		cin>>input;
	//	fflush(stdin);
		input_arr[i]=input;
		matrix target(1,1);
		fflush(stdin);
		cin>>target;
		target_arr[i]=target;
		
	}	
fflush(stdin);	
//srand(time(0));
//	for(int i=0;i<4;i++){
//
//		cout<<"input no: "<<i+1<<endl;
//		input_arr[i].display();
//		target_arr[i].display();
//	}
//	cout<<"++++++++++++++"<<endl;
//fflush(stdin);
	for(int	i=0;i<1000000;i++){

		for(int j=0;j<4;j++){
			
//			int val=rand()%4;
			nn.train(input_arr[j],target_arr[j]);
			//cout<<"--";
		}
		//cout<<i<<endl;
	}

srand(time(0));
	for(int j=0;j<10;j++){
			int val=rand()%4;
			cout<<"val is: "<<val<<endl;
			cout<<"target: ";target_arr[val].display();cout<<endl;
			fflush(stdin);
			cout<<"Result ";nn.feedforward(input_arr[val]).display();
			cout<<"*******************"<<j<<endl;

		}
	
}
