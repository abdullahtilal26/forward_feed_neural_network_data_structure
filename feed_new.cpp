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
		//memcpy(this->data,NULL,sizeof(double)*rows*col);
		
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
		//memcpy(this->data,NULL,sizeof(double)*rows*col);
			
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
//		time_t tt;
//		srand((unsigned) time(&tt));
	//	srand(time(0));
	srand( (unsigned)time( NULL ) );
		for(int i=0;i<rows;i++){
			for(int j=0;j<col;j++){
				this->data[i][j]=((double)rand()/RAND_MAX)*2-1;//double
				//cout<<"randomize val: "<<data[i][j]<<" ";
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

	

	// void map(double(*ptr_func)(double)){
	// 	for(int i=0;i<rows;i++){
	// 		for(int j=0;j<col;j++){
	// 			double val =double(data[i][j]);
	// 			data[i][j]=ptr_fun(val);
	// 		}
	// 	}
	// }
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

	t r(){
		return *data[0];
	}

	friend istream& operator>>(istream& infile, matrix<t> & rhs)
	{
		// int n = rhs.rows*rhs.col;
		for (int i=0;i<rhs.rows;i++){
			for(int j=0;j<rhs.col;j++){
				infile>>rhs.data[i][j];
			}
		}
    	return infile;
	}

	~matrix(){
		//cout<<"delete";
	}
	
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
        //weight_ih->display();

		bias_h=new matrix<double>(hidden_nodes,1);
		bias_o=new matrix<double>(output_node,1);

		bias_h->randomize();
		bias_o->randomize();

		learning_rate=0.1;

	}
	
	
	matrix<t>& feedforward(matrix<double> &input){
		matrix<double> hidden=hidden.product(*weight_ih,input);
		hidden.add(*bias_h);
		hidden.map();

		matrix<t> *output=new matrix<t>(1,1);
		*output=output->product(*weight_ho,hidden);
		output->add(*bias_o);
		output->map();
//		weight_ih->display();
//		weight_ho->display();
//		bias_h->display();
//		bias_o->display();
		return *output;
	}

	void train(matrix<double> &input,matrix<double> &targets){
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
		
		//calculating hidden erros:
//		matrix<double>weight_ho_trans=weight_ho_trans.transpose(*weight_ho);
//		matrix<double>hidden_error=hidden_error.product(weight_ho_trans,output_errors);

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
		
	//	display_all();
//		weight_ih->display();
//		weight_ho->display();


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
		//srand(time(0));
//	for(int i=0;i<10;i++){
//	
//		cout<<rand()%4;
//
//	}
	neuralnetwork<double> nn(2,2,1);

	// matrix<double> inputt(2,1);//[1,0]
	// cin>>inputt;
	// matrix<double> targett(1,1);
	// cin>>targett;

	matrix<double> input_arr[4];
	matrix<double> target_arr[4];
	for(int i=0;i<4;i++){

		//cin>>
		matrix<double> input(2,1);
		cin>>input;
		input_arr[i]=input;
		matrix<double> target(1,1);
		cin>>target;
		target_arr[i]=target;
		
//		input.display();
//		target.display();
	}
					//	
					//	for(int i=0;i<4;i++){
					//
					//		cout<<"////";
					//		input_arr[i].display();
					//		target_arr[i].display();
					//	}
// for(int j=0;j<4;j++){
// 			cout<<"target: ";target_arr[j].display();cout<<endl;
// 			//nn.feedforward(input_arr[j]).display();
// 			cout<<"*******************"<<endl;

// 		}
//srand( (unsigned)time( NULL ) );
	for(int i=0;i<10000;i++){
//		time_t t;
//		srand((unsigned) time(&t));
		//srand(time(0));
		for(int j=0;j<4;j++){
			//input_arr[j].display();target_arr[j].display();
			
			//int val=rand()%4;
			nn.train(input_arr[j],target_arr[j]);
			cout<<"--";
		}
		cout<<"**"<<i<<endl;
	}

	for(int j=0;j<4;j++){
			cout<<"target: ";target_arr[j].display();cout<<endl;
			cout<<"Result ";nn.feedforward(input_arr[j]).display();
			cout<<"*******************"<<endl;

		}
	//nn.feedforward()
	// inputt.display();
	// target.display();
	//nn.feedforward(inputt).display();
	// nn.train(inputt,targett);
	//cout<<output;

	//**************************
	// matrix<double> m;
// m.randomize();
// m.display();
// cout<<(double) rand()/RAND_MAX;

	//****************
// 	matrix<double> f(1,1);

// 	f.randomize();
// 	f.display();
// 	matrix<double>ff(f);
// 	ff.display();

// 	//matrix<double> ans;
// 	matrix<double> ans=f.product(f,ff);
// 	ans.display();
// //*****************
}
