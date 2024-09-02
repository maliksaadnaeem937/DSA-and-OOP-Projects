#include <iostream>
#include <fstream>
#include <conio.h>

using namespace std;

void startingFunction();
void admin_section();

class Product {
public:
    int product_id;
    string product_name;
    float product_price;
    Product* next;

    Product(int product_id, string product_name, float product_price) {
        this->product_name = product_name;
        this->product_id = product_id;
        this->product_price = product_price;
        this->next = NULL;
    }
};

class ProductStack {
private:
    Product* top;

public:
    ProductStack() {
        top = NULL;
    }

    void to_File(Product*& deleted_product) {
        fstream file;
        file.open("recently_deleted.txt", ios::app);
        file << deleted_product->product_id << " " << deleted_product->product_name << "  " << deleted_product->product_price << endl;
        file.close();
    }

    void push() {
        int id;
        string name;
        float price;
        bool empty = true;

        fstream file;
        file.open("recently_deleted.txt", ios::in);
        if (file.is_open()) {
            file >> id >> name >> price;
            while (!file.eof()) {
                empty = false;
                Product* product = new Product(id, name, price);
                if (top == NULL) {
                    top = product;
                } else {
                    product->next = top;
                    top = product;
                }
                file >> id >> name >> price;
            }
            if (empty) {
                cout << "File is empty" << endl;
                getch();
            } else {
                // nothing;
            }
            file.close();
        } else {
            cout << "No data to show" << endl;
            getch();
        }
    }

    void getTop() {
        push();
        if (top != NULL)
        
            cout << "Id: "<<top->product_id << " " <<"Name:"<< top->product_name << " "<<"Price:" << top->product_price << endl;
        else
            cout << "No recently deleted data found" << endl;

        getch();
    }

    void getAll() {
        push();
        if (top != NULL) {
            Product* temp = top;
            while (temp != NULL) {
                cout <<"Id: "<< temp->product_id << " " <<"Name:"<< temp->product_name << " " <<"Price:"<< temp->product_price << endl;
                temp = temp->next;
            }
            getch();
        } else {
            cout << "No recently deleted data found" << endl;
            getch();
        }
    }
    void pop(){
    	
    	push();
    	cout<<"YOU POPPED THIS DATA FROM STACK:"<<endl;
    	
    	cout<<"Id: "<<top->product_id<<" ";
    	cout<<"Name:"<<top->product_name<<" ";
    	cout<<"Price:"<<top->product_price<<endl;
    	getch();
    	top=top->next;
    	fstream  file;
    	file.open("recently_deleted.txt",ios::out);
    	
    	while(top!=NULL){
    	file << top->product_id << " " << top->product_name << "  " << top->product_price << endl;
      
        top=top->next;
    		
		}
		file.close();
    	
    	
	}
};

class ProductList {
private:
    Product* head;
    Product* tail;

public:
    ProductList() {
        head = NULL;
        tail = NULL;
    }
    int productExists(int newId){
    	fstream file;
    	file.open("products.txt",ios::in);
    	if(file.is_open()){
    		
    		string name;
    		int id;
    		float price;
    		file>>id>>name>>price;
    		while(!file.eof()){
    			
    			if(newId==id){
    				return 1;
				}
				file>>id>>name>>price;
			}
		}
		return 0;
    	
    	
	}

    void add_product() {
        system("cls");
        int id;
        float price;
        string name;

           cout << "============================================" << endl;
    cout << "|                                          |" << endl;
    cout << "|              Add New Product              |" << endl;
    cout << "|                                          |" << endl;
    cout << "============================================" << endl;
    cout << "| Enter product Name:                      |" << endl;
    cout << "|                                          |" << endl;
    cout << "============================================" << endl;
    cin >> name;
    cout << "============================================" << endl;
    cout << "| Enter product ID:                        |" << endl;
    cout << "|                                          |" << endl;
    cout << "============================================" << endl;
    cin >> id;
    cout << "============================================" << endl;
    cout << "| Enter product price:                     |" << endl;
    cout << "|                                          |" << endl;
    cout << "============================================" << endl;
    cin >> price;
    

        if(!productExists(id)){
         Product* new_product = new Product(id, name, price);
        if (head == NULL) {
            head = tail = new_product;
        } else {
            tail->next = new_product;
            tail = new_product;
        }

        cout << "Product added successfully!" << endl;
        getch();
        	
        	
		}
		else{
			cout<<"Duplicate product id:"<<endl;
			getch();
		}
     
    }

    void creating_linkedList(Product*& node) {
        if (head == NULL) {
            head = tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }

    void display_linkedList() {
        system("cls");
        cout << "Products in the list:" << endl;
        Product* current = head;
        if (current == NULL) {
            cout << "List empty" << endl;
            return;
        }
        while (current != NULL) {
            cout << "Product id: " << current->product_id << " ";
            cout << "Product Name: " << current->product_name << " ";
            cout << "Product Price: " << current->product_price << endl;
            current = current->next;
        }
        cout << "Press any key to continue.." << endl;
        getch();
    }

    void write_to_file() {
        fstream file("products.txt", ios::app);

        if (!file.is_open()) {
            cout << "Error: Unable to open file!" << endl;
            return;
        }

        Product* current = head;
        while (current != NULL) {
            file << current->product_id << " " << current->product_name << " " << current->product_price << endl;
            current = current->next;
        }
        file.close();

        cout << "Operation Successful!" << endl;
        getch();
    }

    void display_from_file() {
        bool empty = true;
        fstream file("products.txt", ios::in);
        if (!file.is_open()) {
            cout << "Error: Unable to open file!" << endl;
            return;
        }
        float price;
        string name;
        int id;
        file >> id >> name >> price;
        while (!file.eof()) {
            empty = false;
            Product* node = new Product(id, name, price);
            creating_linkedList(node);
            file >> id >> name >> price;
        }
        file.close();
        display_linkedList();
        if (empty) {
            cout << "Nothing to show" << endl;
            getch();
        }
    }

    void delete_product() {
        bool found = false;
        float price;
        string name;
        int key, id;
        display_from_file();
        cout << "Enter product id you want to delete: ";
        cin >> key;

        head = tail = NULL;

        fstream file;
        file.open("products.txt", ios::in);
        if (file.is_open()) {
            file >> id >> name >> price;
            while (!file.eof()) {
                if (id != key) {
                    Product* product = new Product(id, name, price);
                    creating_linkedList(product);
                } else if (id == key) {
                    found = true;
                    Product* deleted_product = new Product(id, name, price);
                    ProductStack ss;
                    ss.to_File(deleted_product);
                }
                file >> id >> name >> price;
            }
            file.close();
            fstream file("products.txt", ios::out);

            if (!file.is_open()) {
                cout << "Error: Unable to open file!" << endl;
                return;
            }

            Product* current = head;
            while (current != NULL) {
                file << current->product_id << " ";
                file << current->product_name << " ";
                file << current->product_price << endl;
                current = current->next;
            }
            file.close();

            if (found) {
                cout << "Data deleted from file successfully!" << endl;
            } else {
                cout << "Data not found" << endl;
            }
            getch();
        } else {
            cout << "There is no data in the file" << endl;
            getch();
        }
    }
};
class Customer{

	
	private:
		
	
		int product_id[100], product_quantity[100];
		float product_price[100];
		public:
		string customerName;
		int customerId;
			Customer* next;
			Customer(string name , int id){
				this->customerName=name;
				this->customerId=id;
				this->next=NULL;
			}
			int productExists(int pr_id,int index){
				int id;
				string name;
				float price;
				
				fstream file;
				file.open("products.txt",ios::in);
				file>>id>>name>>price;
				while(!file.eof()){
					if(id==pr_id){
						file.close();
						product_price[index]=price;
						return 1;
					}
					file>>id>>name>>price;
				}
				file.close();
				return 0;
				
			}
		void handleBuyingFunction() {
    int index = 0;
    char choice;
     float total_bill=0.0;
    do {
        cout << "Enter product id you want to buy:" << endl;
        cin >> product_id[index];
        cout << "Enter quantity of product:" << endl;
        cin >> product_quantity[index];
        
        if (!productExists(product_id[index],index)) {
            cout << "Product id does not exist, please enter a valid id" << endl;
            getch();
            continue; // Skip to the next iteration of the loop
        }

        cout << "Press Y if you want to buy another product and N to cancel:" << endl;
        cin >> choice;
        index++;
    } while (choice == 'y' || choice == 'Y');

    for (int j = 0; j < index; j++) { 
        cout << "Product id: " << product_id[j] << "   ";
        cout << "Product quantity: " << product_quantity[j]<<"  ";
        cout<<"unit Price: "<<product_price[j]<<"  ";
         cout<<"Total :"<<product_price[j]*product_quantity[j]<<"  ";
         total_bill=total_bill+product_price[j]*product_quantity[j];
        cout << endl;
    }
    cout<<"Displaying bill..."<<endl;
    
    cout<<total_bill<<endl;
  
    
    getch();
}

			void enterDetails(){
				
			  ProductList productList;
				 productList.display_from_file();
				 
				 handleBuyingFunction();
				
				
			}
};
class CustomerQueue{
	
	public:
		Customer* front;
		Customer* rear;
		CustomerQueue(){
			front=NULL;
			rear=NULL;
		}
		void enqueue(Customer *&customer){
			
			if(front==NULL && rear==NULL){
				
				front=customer;
				rear=customer;
			}
			else{
				
				rear->next=customer;
				rear=customer;
				
			}
			
			
			
		}
		void dequeue(){
			int i=1;
			while(front!=NULL){
				cout<<"You are customer number "<<i<<endl;
				cout<<"Start your shopping:"<<endl;
				cout<<"Your data:"<<endl;
				cout<<"Name:"<<front->customerName<<"   ";
				cout<<"Id: "<<front->customerId<<endl;
				cout<<"Press enter to start shoping"<<endl;
				getch();
				
				front->enterDetails();
				front=front->next;
				i++;
				
				
			}
			cout<<"All operations succesfull"<<endl;
			
			
			
			
			
			
		}
	
	
	
	
};
void customer_section(){

		CustomerQueue customerQueue;
	string name;
	int id;
		system("cls");
		
		int number_customers;
		cout<<"Enter how many customers do u want to enqueue:"<<endl;
		cin>>number_customers;
		for( int i=0; i<number_customers; i++){
			cout<<"Enter name of customer:"<<endl;
			cin>>name;
			cout<<"Enter id:"<<endl;
			cin>>id;
			
			Customer *customer= new Customer(name,id);
			customerQueue.enqueue(customer);
		}
		customerQueue.dequeue();
		
		

	
}

void admin_section() {
top:
    system("cls");
    int choice;
    ProductList productList;
    ProductStack stack;
      cout << "============================================" << endl;
    cout << "|          Welcome to the Admin Section    |" << endl;
    cout << "============================================" << endl;
    cout << "|                                          |" << endl;
    cout << "|   1. Add a Product                       |" << endl;
    cout << "|   2. View All Products                   |" << endl;
    cout << "|   3. Delete a Product                    |" << endl;
    cout << "|   4. View All Recently Deleted Data      |" << endl;
    cout << "|   5. View Last Deleted Data              |" << endl;
    cout << "|   6. Pop Recently Deleted Item           |" << endl;
    cout << "|   7. Go Back to Start                    |" << endl;
    cout << "|   8. Exit                                |" << endl;
    cout << "|                                          |" << endl;
    cout << "============================================" << endl;
    cout << "| Please enter your choice:                |" << endl;
    cout << "============================================" << endl;

    cin >> choice;

    switch (choice) {
        case 1:
        {
            char choices;
            do {
                productList.add_product();
                cout << "Do you want to add another product? (Y/N): ";
                cin >> choices;
            } while (choices == 'Y' || choices == 'y');
            productList.write_to_file();
            goto top;
        }
        break;
        case 2:
            productList.display_from_file();
            goto top;
            break;
        case 3:
            productList.delete_product();
            goto top;
        case 4:
            stack.getAll();
            goto top;
        case 5:
            stack.getTop();
            goto top;
        case 6:
		   stack.pop();
		   goto top;    
        case 7:
            startingFunction();
            break;
        case 8:
            exit(0);
        default:
            cout << "Invalid choice" << endl;
            getch();
            goto top;
            break;
    }
}

void startingFunction() {
top:
    system("cls");
    int choice;
    string secret_key;

        cout << "============================================" << endl;
    cout << "|                                          |" << endl;
    cout << "|              Main Menu                   |" << endl;
    cout << "|                                          |" << endl;
    cout << "============================================" << endl;
    cout << "|                                          |" << endl;
    cout << "|     1. Admin Section                     |" << endl;
    cout << "|     2. Customer Section                  |" << endl;
    cout << "|     3. End Program                       |" << endl;
    cout << "|                                          |" << endl;
    cout << "============================================" << endl;
    cout << "| Please enter your choice:                |" << endl;
    cout << "============================================" << endl;

    cin >> choice;

    switch (choice) {
        case 1:
            cout << "Enter Secret Key:" << endl;
            cin >> secret_key;
            if (secret_key == "123")
                admin_section();
            else {
                cout << "You entered wrong key. Press any key to continue" << endl;
                getch();
                goto top;
            }
            break;
        case 2:
             customer_section();
             goto top;
            
            break;
        case 3:
            exit(0);
        default:
            cout << "Invalid choice. Press any key to continue" << endl;
            getch();
            goto top;
            break;
    }
}

int main() {
    startingFunction();
    return 0;
}





