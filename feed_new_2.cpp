#include<iostream>
#include<string.h>
#include<cmath>
#include<time.h>
#include<stdlib.h>
using namespace std;

double sigmoid(double x){
		return (1/(1+exp(-x)));
	}
double der_sigmoid(double x){
	return x*(1-x);
}
template<class t>
class matrix{
	private:
		
		int rows,col;
		t **data;
		
	public:
		
	matrix(int r,int c){
		rows=r;
		col=c;
		data= new t*[rows];
		for(int i=0;i<rows;i++){
			data[i]=new t[col];
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
		
		data= new t*[rows];
		for(int i=0;i<rows;i++){
			data[i]=new t[col];
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
		
		data=new t*[rows];
		for(int i=0;i<rows;i++){
			this->data[i]=new t[col];
		}
		
		memcpy(this->data,rhs.data,sizeof(t)*rows*col);
	}

	matrix& operator=(const matrix &rhs){
		if(this!=&rhs){
			//this->delete_all();
		this->rows=rhs.rows;
		this->col=rhs.col;
		
		data=new t*[rows];
		for(int i=0;i<rows;i++){
			this->data[i]=new t[col];
		}
		
		memcpy(this->data,rhs.data,sizeof(t)*rows*col);
		}
		return *this;
		
	}

	void randomize(){

	srand( (unsigned)time( NULL ) );
		for(int i=0;i<rows;i++){
			for(int j=0;j<col;j++){
				this->data[i][j]=((double)rand()/RAND_MAX)*2-1;//double
			}
		}
	}

	void multiply(const t n) {
   		 for (int i = 0; i < rows; i++) {
     		 for (int j = 0; j < col; j++) {
        		this->data[i][j] *= n;
      		}
    	}
  	}

	void multiply_hadamard(const matrix &rhs) {
   		 for (int i = 0; i < rows; i++) {
     		 for (int j = 0; j < col; j++) {
        		this->data[i][j] *= rhs.data[i][j];
      		}
    	}
  	}

	matrix& product(const matrix a,const matrix b){
		matrix<t> *result;
		result=new matrix<t>(a.rows,b.col);

		if(a.col!=b.rows){
		
			return *result;
		}
		else
		{	
			for(int i=0;i<result->rows;i++){

				for(int j=0;j<result->col;j++){
					double sum=0;               //float
					// data[i][j]*=rhs.data[i][j];
					for(int k=0;k<a.col;k++){
						sum =sum+((a.data[i][k])*(b.data[k][j]));
					}
					result->data[i][j]=sum;
				}
			}	
			
			return *result;
			
		}
				
	}
	matrix& transpose(const matrix<t>&rhs){
		matrix<double> *result=new matrix<double>(rhs.col,rhs.rows);
		for(int i=0;i<rhs.rows;i++){
			for(int j=0;j<rhs.col;j++){
				result->data[j][i]=rhs.data[i][j];
			}
		}

		return *result;	
	}
	void add(const matrix &rhs){
			for(int i=0;i<rows;i++){
				for(int j=0;j<col;j++){
					this->data[i][j] += rhs.data[i][j];
				}
			}
	}

	matrix& subtract(const matrix &a,const matrix &b){
		matrix<double> *result=new matrix<double>(a.rows,a.col);
		
			for(int i=0;i<result->rows;i++){
				for(int j=0;j<result->col;j++){
					result->data[i][j] = a.data[i][j]-b.data[i][j];
				}
			}

			return *result;
	}

	 void map(){
		for(int i=0;i<rows;i++){
			for(int j=0;j<col;j++){
				t val =data[i][j];    //double
				this->data[i][j]=sigmoid(val);
			}
		}
	}

	void map_der(){
		for(int i=0;i<rows;i++){
			for(int j=0;j<col;j++){
				t val =data[i][j];    //double
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


	friend istream& operator>>(istream& infile, matrix<t> & rhs)
	{
		for (int i=0;i<rhs.rows;i++){
			for(int j=0;j<rhs.col;j++){
				infile>>rhs.data[i][j];
			}
		}
    	return infile;
	}

	~matrix(){

						// for(int i = rows-1;i>=0;i--) {
						// 	if (*(data+i)!=0)
						// 	{
						// 		delete [] *(data+i);
						// 		*(data+i)=0;
						// 	}
						// }
						// delete[] data;
						// data=0;
		//cout<<"delete";
		//delete [] data;
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
template<class t>
class neuralnetwork{
	private:
		int input_nodes,hidden_nodes,output_node;
		matrix<double> *weight_ih;matrix<double> *weight_ho;
		matrix<double> *bias_h;matrix<double> *bias_o;
		t learning_rate;
	public:
	
	neuralnetwork(int input_n,int hidden_n,int output_n){
		input_nodes=input_n;
		hidden_nodes=hidden_n;
		output_node=output_n;
		
		weight_ih=new matrix<double>(hidden_nodes,input_nodes);
		weight_ho=new matrix<double>(output_node,hidden_nodes);

        weight_ih->randomize();
        weight_ho->randomize();

		bias_h=new matrix<double>(hidden_nodes,1);
		bias_o=new matrix<double>(output_node,1);

		bias_h->randomize();
		bias_o->randomize();

		learning_rate=0.1;

	}
	
	
	matrix<t>& feedforward(matrix<t> &input){
		matrix<double> *hidden=new 	matrix<double>(1,1);
		*hidden=hidden->product(*weight_ih,input);
		hidden->add(*bias_h);
		hidden->map();

		matrix<t> *outputt=new matrix<t>(1,1);
		*outputt=outputt->product(*weight_ho,*hidden);
		outputt->add(*bias_o);
		outputt->map();
		
		return *outputt;
	}

	void train(matrix<t> &input,matrix<t> &targets){
	//	cout<<"train"<<endl;
		fflush(stdin);
		//input.display();
		//first layer
		matrix<double> hidden=hidden.product(*weight_ih,input);
		hidden.add(*bias_h);
		hidden.map();
		//second layer
		matrix<t> *output=new matrix<t>(1,1);
		*output=output->product(*weight_ho,hidden);
		output->add(*bias_o);
		output->map();
//--------------------------------------------
		//hidden to output backprog
		//matrix<double> output=feedforward(input);
		//calculating output error
		matrix<double>output_errors=output_errors.subtract(targets,*output);
		

		//gradint                        //hadamard
		//output->map_der();
		matrix<double>gradient=*output;
		gradient.map_der();
		gradient.multiply_hadamard(output_errors);
		gradient.multiply(learning_rate);

		//gradient delta
		matrix<double> hidden_T=hidden_T.transpose(hidden);
		matrix<double>weight_ho_delta=weight_ho_delta.product(gradient,hidden_T);

		//adjust weights
		weight_ho->add(weight_ho_delta);
		//adjust biases
		bias_o->add(gradient);
		
//-------------------------------------------------------
		//input to hidden backprog


		//calculating hidden erros:
		matrix<double>weight_ho_trans=weight_ho_trans.transpose(*weight_ho);
		matrix<double>hidden_error=hidden_error.product(weight_ho_trans,output_errors);
	//	hidden_error.display();
		
		//calculatung  gradient for input lyaer
		matrix<double>hidden_gradient=hidden;
		hidden_gradient.map_der();
		hidden_gradient.multiply_hadamard(hidden_error);
		hidden_gradient.multiply(learning_rate);

		//calculatig of gradient delta of input layer
		matrix<double> input_T=input_T.transpose(input);
		matrix<double>weight_ih_delta=weight_ih_delta.product(hidden_gradient,input_T);

		//adjust weights
		weight_ih->add(weight_ih_delta);
		//adjust bias
		bias_h->add(hidden_gradient);
		

	}
	
	void display_all(){
		cout<<"**************************";
		cout<<"display weight ih:"<<endl;
		weight_ih->display();
		cout<<"display weight ho:"<<endl;
		weight_ho->display();
		cout<<"display bias ih:"<<endl;
		bias_h->display();
		cout<<"display bias ho:"<<endl;
		bias_o->display();
	}
	
};

int main(){
	
	neuralnetwork<double> nn(2,2,1);
	
	matrix<double> input_arr[4];
	matrix<double> target_arr[4];
	for(int i=0;i<4;i++){

	//	fflush(stdin);
		matrix<double> *input=new matrix<double>(2,1);
		fflush(stdin);
		cin>>*input;
	//	fflush(stdin);
		input_arr[i]=*input;
		matrix<double> *target=new matrix<double>(1,1);
		fflush(stdin);
		cin>>*target;
		target_arr[i]=*target;
		
	}	
fflush(stdin);	
//	for(int i=0;i<4;i++){
//
//		cout<<"input no: "<<i+1<<endl;
//		input_arr[i].display();
//		target_arr[i].display();
//	}
//	cout<<"++++++++++++++"<<endl;
//fflush(stdin);
	for(int i=0;i<1000000;i++){

		for(int j=0;j<4;j++){
			
		//	int val=rand()%4;
			nn.train(input_arr[j],target_arr[j]);
			//cout<<"--";
		}
		//cout<<"----"<<i<<endl;
	}

srand(time(0));
	for(int j=0;j<10;j++){
			int val=rand()%4;
			cout<<"target: ";target_arr[val].display();cout<<endl;
			cout<<"Result ";nn.feedforward(input_arr[val]).display();
			cout<<"*******************"<<endl;

		}
	
}
