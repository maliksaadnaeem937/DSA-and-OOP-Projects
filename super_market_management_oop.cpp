#include <iostream>
#include <fstream> 
 #include <string>
 #include<conio.h>
 #include<windows.h>
using namespace std;
void main_menu();
void register_main_menu();
void login_main_menu();
//##########################################3333
class Abstract{
	public:
	virtual bool Register()=0;


};
//############################################################################################//
class User :public Abstract{
protected:
    string name;
    string cnic;
    int age;
    string address;
    string password;
    string filename;
    float balance;
public:
    bool already_exist() {
        string username, pass;
        ifstream file("User.txt");
        if (file.is_open()) {
            while (file >> username >> pass) {
                if (name == username || pass == password) {
                    file.close();
                    return true;
                }
            }
            file.close();
            return false;
        }
        return false;
    }

bool Register() {
        cout << "Enter User Name:";
        cin >> name;
        cout << "Enter CNIC:";
        cin >> cnic;
        cout << "Enter Address:";
        cin >> address;
        cout << "Enter Age:";
        cin >> age;
        cout << "Enter Password:";
        cin >> password;
        cout<<"Enter Balance:";
        cin>>balance;
        if (already_exist()) {
            cout << "User Name Or Password Already exists" << endl;
            
            getch();
            return false;
        } 
		else {
            ofstream file("User.txt", ios::app);
            if (file.is_open()) {
                file << name << "\t" << password << endl;

                
            }
            file.close();
            return true;
        }
    }

    bool authentication_successful() {
        string username, pass;
        ifstream file("User.txt");
        if (file.is_open()) {
            while (file >> username >> pass) {
                if (name == username && pass == password) {
                    file.close();
                    return true;
                }
            }
            file.close();
            return false;
        }
        return false;
    }

    bool Login() {
        cout << "Enter Name:";
        cin >> name;
        cout << "Enter Password:" << endl;
        cin >> password;
        if (authentication_successful()) {
            cout << "Login Successful..." << endl;
            getch();
            return true;
        } else {
            cout << "Wrong Username Or Password" << endl;
          getch();
            return false;
        }
    }
    string return_user(){
    	return name;
    	
	}
														// VIEW PROFILE 
 void profile(string request_user){
 	system("cls");
    fstream file;
     filename=request_user+".txt";
    file.open(filename.c_str(),ios::in);
    	
    file >> name >>  password   >> age  >> cnic  >> address>>balance;
    cout<<"Name: "<<name<<endl;
    cout<<"Password:"<<password<<endl;
    cout<<"Age: "<<age<<endl;
    cout<<"CNIC: "<<cnic<<endl;
    cout<<"Address:"<<address<<endl;
    cout<<"Balance:"<<balance<<endl;
    getch();
    file.close();
	}
	
																	//UPDATE PROFILE 	
void updateProfile(const std::string& request_user) {
    ifstream inputFile("User.txt");
    ofstream outputFile("TempUser.txt");

    if (!inputFile || !outputFile) {
        std::cerr << "Error opening files." << std::endl;
        getch();
        return;
    }

    bool userFound = false;

// Read data from the input file and write to the temporary file
    while (inputFile >> name >> password) {
        if (name == request_user) {
// Skip this user (do not write to the temporary file)
            userFound = true;
        } else {
// Write other users to the temporary file
            outputFile << name << " " << password << endl;
        }
    }

    inputFile.close();
    outputFile.close();

// Rename the temporary file to the original file
    if (userFound) {
        remove("User.txt");
        rename("TempUser.txt", "User.txt");
//        std::cout << "Profile for user '" << request_user << " removed." << std::endl;
    } else {
        std::cout << "User '" << request_user << "' not found." << std::endl;
        remove("TempUser.txt"); 
// Remove the temporary file if no changes were made
    }
    
    string userprofile=request_user+".txt";
    remove(userprofile.c_str());
    Register();
    adminCustomerWriteFile();
    cout<<"Updation successful..."<<endl;
    getch();
    
}
															//WRITE PROFILE AFTER REGISTERATION	
void adminCustomerWriteFile() {
        filename = name + ".txt";
        ofstream file;
        file.open(filename.c_str(), ios::app);
        if (file.is_open()) {
            file << name << " " << password << " " << age << " " << cnic << " " << address << " "<<balance<<endl;
            cout<<"Your Data has been saved and account is credited with Rs. "<<balance<<endl;
            getch();
        }
        file.close();
    }	
};
//##########################################################################################//
class Products {
protected:
    int id;
    string name;
    float price;
    int quantity;

public:
    void displayallproduct() {
		system("cls");
        fstream file;
        file.open("Products.txt", ios::in);

        if (file.is_open()) {
            file >> id >> name >> price>>quantity;
            while (!file.eof()) {
                cout << "\tID: " << id << "\tName: " << name << "\tPrice: " << price <<"\tQuantity:"<< quantity<<endl;
                file >> id >> name >> price>>quantity;
            }
            file.close();
        } else {
            cout << "Unable to open file for reading." << endl;
            getch();
        }
        cout<<"Press Enter to  hide view "<<endl;
        getch();
    }

    bool pro_already_exist() {
        int pro_id;
        string pro_name;
        float pro_price;
        int pro_qty;
        fstream file;
	   file.open("Products.txt", ios::in);
        if (file.is_open()) {
            file >> pro_id >> pro_name >> pro_price>>pro_qty;

            while (!file.eof()) {
                if (pro_id == id) {
                    return true;
                }
                file >> pro_id >> pro_name >> pro_price>>pro_qty;
            }
            return false;
        }
        else{
        	cout<<"File created successfully"<<endl;
        	getch();
        	fstream file;
        	file.open("Products.txt",ios::out);
        	file.close();
        	return false;
		}
    }

    bool pro_already_exist(int pr_id) {
        int pro_id;
        string pro_name;
        float pro_price;
        int pro_qty;
        fstream file;
        file.open("Products.txt", ios::in);

        if (file.is_open()) {
            file >> pro_id >> pro_name >> pro_price>>pro_qty;

            while (!file.eof()) {
                if (pro_id == pr_id) {
                    file.close();
                    return true;
                }
                file >> pro_id >> pro_name >> pro_price>>pro_qty;
            }
                    
            file.close();
            return false;
        }
    }

    void addproduct() {
    		
        m:
        	system("cls");
        cout << "Enter Product Id" << endl;
        cin >> id;
        cout << "Enter Name:" << endl;
        cin >> name;
        cout << "Enter Price" << endl;
        cin >> price;
        cout<<"Enter Product Quantity:"<<endl;
        cin>>quantity;

        if (pro_already_exist()) {
            cout << "Product Code Already Exists" << endl;
            getch();
            goto m;
        } else {
            fstream file;
            file.open("Products.txt", ios::app);
            file << id << "\t" << name << "\t" << price <<"\t"<<quantity<< endl;
            file.close();
            cout<<"Product added successfully"<<endl;
            getch();
        }
    }

    void deleteproduct() {
    	displayallproduct();
    	system("cls");
        int productId;
        cout << "Enter Product ID to delete: ";
        cin >> productId;

        fstream fileIn, fileOut;
        fileIn.open("Products.txt", ios::in);
        fileOut.open("temp.txt", ios::out);

        if (fileIn.is_open() && fileOut.is_open()) {
            fileIn >> id >> name >> price>>quantity;

            while (!fileIn.eof()) {
                if (id != productId) {
                    fileOut << id << "\t" << name << "\t" << price <<"\t"<<quantity<< endl;
                }
                fileIn >> id >> name >> price>>quantity;
            }

            fileIn.close();
            fileOut.close();

            // Remove the old file
            remove("Products.txt");

            // Rename the new file
            rename("temp.txt", "Products.txt");

            cout << "Product with ID " << productId << " deleted successfully." << endl;
            getch();
        }
    }

    void modifyproduct() {
    	displayallproduct();
    	system("cls");
        int productId;
        cout << "Enter Product ID to modify: ";
        cin >> productId;

        fstream fileIn, fileOut;
        fileIn.open("Products.txt", ios::in);
        fileOut.open("temp.txt", ios::out);

        if (fileIn.is_open() && fileOut.is_open()) {
            fileIn >> id >> name >> price>>quantity;

            while (!fileIn.eof()) {
                if (id == productId) {
                    cout << "Enter new Name: ";
                    cin >> name;
                    cout << "Enter new Price: ";
                    cin >> price;
                    cout<<"Enter New product Id:";
                    cin>>id;
                    cout<<"Enter  New quantity:";
                    cin>>quantity;
                }
                fileOut << id << "\t" << name << "\t" << price <<"\t"<<quantity<< endl;
                fileIn >> id >> name >> price>>quantity;
            }

            fileIn.close();
            fileOut.close();

            // Remove the old file
            remove("Products.txt");

            // Rename the new file
            rename("temp.txt", "Products.txt");

            cout << "Product with ID " << productId << " modified successfully." << endl;
            getch();
        }
    }

    float getProductPrice(int pr_id) {
        int pro_id;
        string pro_name;
        float pro_price;
        int pro_qty;
        fstream file;
        file.open("Products.txt", ios::in);

        if (file.is_open()) {
            file >> pro_id >> pro_name >> pro_price>>pro_qty;

            while (!file.eof()) {
                if (pro_id == pr_id) {
                    file.close();
                    return pro_price;
                }
                file >> pro_id >> pro_name >> pro_price>>pro_qty;
            }
        }
    }
    
   bool sufficient_product_quantity(int pro_id,int pro_qty){
    	
    	fstream file;
    	file.open("Products.txt",ios::in);
    	
    	file>>id>>name>>price>>quantity;
    	while(!file.eof()){
    		
    		if(pro_id==id){
    			if(pro_qty<=quantity){

    			  return true;
				}
				else{
					cout<<"Available quantity="<<quantity<<endl;
    				cout<<"Quantity You Want to buy="<<pro_qty<<endl;
				return false;
				}
			}
			file>>id>>name>>price>>quantity;
		}
    	
	}
    void update_inventory(int pro_id, int pro_qty){

    bool updation = false;

    
    fstream readfile, writefile;
    readfile.open("Products.txt", ios::in);
    writefile.open("temp.txt", ios::out);

    if (!readfile.is_open() || !writefile.is_open()) {
        cout << "Error opening files." << endl;
        return;
    }

    while (readfile >> id >> name >> price >> quantity) {
        if (id == pro_id) {
            updation = true;
            int updated_quantity = quantity - pro_qty;
            writefile << id << "\t" << name << "\t" << price << "\t" << (updated_quantity >= 0 ? updated_quantity : 0) << endl;
        } else {
            writefile << id << "\t" << name << "\t" << price << "\t" << quantity << endl;
        }
    }

    readfile.close();
    writefile.close();

    if (updation) {
        if (remove("Products.txt") != 0) {
            cout << "Error deleting file." << endl;
            return;
        }

        if (rename("temp.txt", "Products.txt") != 0) {
            cout<< "Error renaming file." << endl;
            return;
        }

        cout << "Inventory Updated Successfully........." << endl;
    }

    getch();

    	
	}
   
};
//.##############################################################################################.//
class Admin :  public User {
protected:
    string filename;
public:
   
       
    

    void AdminLogin() {
        if (User::Login()) {
        	
            // Admin-specific login actions

            // Create an object of the Products class
            Products products;

            int choice;
            do {
            	system("cls");
                cout << "1) Display all products\n2) Add a product\n3) Delete a product\n4) Modify a product\n5) Logout\nEnter your choice: ";
                cin >> choice;

                switch (choice) {
                case 1:
                    products.displayallproduct();
                    break;

                case 2:
                    products.addproduct();
                    break;

                case 3:
                    products.deleteproduct();
                    break;
                case 4:
                    products.modifyproduct();
                    break;
                case 5:
                    cout << "Logging out..." << endl;
                    break;

                default:
                    cout << "Invalid choice" << endl;
                }

            } while (choice != 5);
        }
          else{
        	cout<<"Enter TO Go Back"<<endl;
        	getch();
        	login_main_menu();
		}
    }
};
//-#############################################################################################-//
class Customer : public User {
	protected:
		string request_user;
public:
    void CustomerLogin() {
        if (User::Login()) {
            // Customer-specific login actions
           request_user=User::return_user();
            // Create an object of the Products class
            Products products;

            int choice;
            do {
            	system("cls");
            	cout<<"\t\t Welcome "<<request_user<<endl;
                cout << "1) Display all products\n2) Buy a product\n3) Profile\n4)UpdateProfile\n 5)Logout\nEnter your choice: ";
                cin >> choice;

                switch (choice) {
                case 1:
                    products.displayallproduct();
                    break;

                case 2:
                    buyProduct(products);
                    break;

				case 3:
                    profile(request_user);
                    break;
                    
                case 4:
                    updateProfile(request_user);
                    break;
                case 5:
                    cout << "Logging out..." << endl;
                    break;

                default:
                    cout << "Invalid choice" << endl;
                }

            } while (choice != 5);
        }
        else{
        	cout<<"Enter TO Go Back"<<endl;
        	getch();
        	login_main_menu();
		}
    }

    void buyProduct(Products &products) {
    	up:
        int productId, quantity;
        cout << "Enter Product ID to buy: ";
        cin >> productId;

        if (!products.pro_already_exist(productId)) {
            cout << "Product not found." << endl;
            getch();
            goto up;
        }

        cout << "Enter quantity to buy: ";
        cin >> quantity;
      if(products.sufficient_product_quantity(productId,quantity))
{  // Calculate the total cost based on the product price and quantity
        float totalCost = products.getProductPrice(productId) * quantity;

   if(sufficient_balance(totalCost)){	
   	// Display the bill
        cout << "Bill:\n";
        cout << "Product ID: " << productId << "\n";
        cout << "Quantity: " << quantity << "\n";
        cout << "Total Cost: " << totalCost << "\n";
        updateBalance(totalCost);
        products.update_inventory(productId,quantity);
        getch();
   }
   else{
   	cout<<"You Dont have sufficient balance to buy product"<<endl;
   	
   	getch();
   }
	
}
else{
	cout<<"Sorry! Entered Product Quantity is not available"<<endl;
	getch();
}
    }
	
	bool sufficient_balance(float totalCost){
	
		fstream file;
		string  filename=request_user+".txt";
		file.open(filename.c_str(), ios::in);
		if(file.is_open())
	{
	
	file>>name>>cnic>>age>>address>>password>>balance;
	
	if(balance>=totalCost){
		return true;
	}
	else{
		return false;
	}
		}						
	
	}  
	void updateBalance(float totalCost){
		
		fstream file;
		
		string  filename=request_user+".txt";
		file.open(filename.c_str(), ios::in);		
	if(file.is_open()){
	file>>name>>cnic>>age>>address>>password>>balance;
	balance=balance-totalCost;
	file.close();
	remove(filename.c_str());
	fstream newfile;
		  filename=request_user+".txt";
		newfile.open(filename.c_str(), ios::app);
		
		if(newfile.is_open()){
			newfile<<name<<"\t"<<cnic<<"\t"<<age<<"\t"<<address<<"\t"<<password<<"\t"<<balance<<"\t"<<endl;
			
			newfile.close();
			cout<<"Your Account Has been Debited by Rs."<<totalCost;
			cout<<"Your balance has been updated"<<endl;
			getch();
		}
		else{
			cout<<"Error opening file"<<endl;
			return ;
		}
	
		}
								
	}
};

void logo() {
 	cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t________________________________________________________________________________________________\n";
cout<<"\t\t\t\t\t|    _______________________________________________________________________________________    |\n";
cout<<"\t\t\t\t\t|   |                                           		                            |   |\n";
cout<<"\t\t\t\t\t|   |                                           		                            |   |\n";
cout<<"\t\t\t\t\t|   |                                           		                            |   |\n";
cout<<"\t\t\t\t\t|   |                                           		                            |   |\n";
cout<<"\t\t\t\t\t|   |                     ************************************************                  |   |\n";
cout<<"\t\t\t\t\t|   |                     * ******************************************** *                  |   |\n";
cout<<"\t\t\t\t\t|   |                     * *              WELCOME TO                  * *                  |   |\n";
cout<<"\t\t\t\t\t|   |                     * *                                          * *                  |   |\n";
cout<<"\t\t\t\t\t|   |                     * *       SUPERMARKET Managment System       * *                  |   |\n";
cout<<"\t\t\t\t\t|   |                     * ******************************************** *                  |   |\n";
cout<<"\t\t\t\t\t|   |                     ************************************************                  |   |\n";
cout<<"\t\t\t\t\t|   |                                                                                       |   |\n";
cout<<"\t\t\t\t\t|   |                                                                                       |   |\n";
cout<<"\t\t\t\t\t|   |                                                                                       |   |\n";
cout<<"\t\t\t\t\t|   |                                                                                       |   |\n";
cout<<"\t\t\t\t\t|   |_______________________________________________________________________________________|   |\n";
cout<<"\t\t\t\t\t|_______________________________________________________________________________________________|\n\n\n\n\t\t\t\t\t";
	
	getch();
	cout<<"SYSTEM LOADING.";
	for(int i=0; i<10; i++){
		Beep(900,300);
		cout<<".";
		Sleep(100);
	}
	
}
int main() {
	
//	logo();
main_menu();
    return 0;
}
void main_menu(){

	int choice;
	system("cls");
    cout<<"\n\n\t\t\t\t\t\t  MAIN MENU\n";
	cout<<"\n\n\n\n\t\t\t\t\t|--------------------------|"<<endl;
	Sleep(100);
	cout<<"\t\t\t\t\t|1)______Register__________|"<<endl;
	Sleep(100);
	cout<<"\t\t\t\t\t|2)________Login___________|"<<endl;
	Sleep(100);
	cout<<"\t\t\t\t\t|3)_________Exit___________|"<<endl;
	Sleep(100);
	cout<<"\t\t\t\t\t|--------------------------|"<<endl;
	cin>>choice;
	
	switch(choice){
		case 1:
			register_main_menu();
	    case 2:
		    login_main_menu();
		case 3:
		     exit(0);
	    default:
		    cout<<"Invalid Input...."<<endl;
			getch();
			main_menu();		 			
	}	
}
void register_main_menu(){
	top:
	int choice;
	system("cls");

            cout << "\n\n\n\n\t\t\t\t\t|-------------------------------|\n";
    		Sleep(100);
    		cout << "\t\t\t\t\t|1)______RegisterAsAdmin________|\n";
    		Sleep(100);
    		cout << "\t\t\t\t\t|2)________Customer_____________|\n";
    		Sleep(100);
    		cout << "\t\t\t\t\t|3)_________Exit________________|\n";
    		Sleep(10);
    		cout << "\t\t\t\t\t|4)_________GO BACK__________|\n";
    		Sleep(10);
    		cout << "\t\t\t\t\t|-------------------------------|\n";
            cin >> choice;
                
                switch (choice) {
                case 1: {
                	
                	string key;
                	cout<<"ENTER KEY:"<<endl;
                	cin>>key;
                	if(key=="12345"){
                	
                	Abstract *ptr;
                    User user;
                    ptr=&user;
                    
                    if(ptr->Register()){
                  
                    user.adminCustomerWriteFile();
                    cout<<"Regestration successful and data is saved"<<endl;
                    getch();
					}
              		}
              		else{
              			cout<<"Wrong key:"<<endl;
              			getch();
              			goto top;
					  }
                
                    break;
                }
                case 2: {
                    Abstract *ptr;
                    User user;
                    ptr=&user;
                    
                    if(ptr->Register()){
                    
                    user.adminCustomerWriteFile();
                    cout<<"Regestration successful and data is saved"<<endl;
                    getch();
					}
        
                    break;
                }
                case 3:
                	exit(0);
                    break;
                case 4:
                	main_menu();

                default:
                    cout << "Invalid choice...." << endl;
                    getch();
                    register_main_menu();
                    
                }
}
void login_main_menu(){
	top:
	system("cls");
	int choice;
	   cout <<  "1) Login as admin\n"
	    		"2) Login as customer\n"
				"3) Go back\n"
	    		"Enter your choice: ";
                cin >> choice;

                switch (choice) {
                case 1: {
                    string key;
                    Admin admin;
                    cout<<"Enter Key:"<<endl;
                    cin>>key;
                    if(key=="12345"){
                    admin.AdminLogin();
					}
                   
                    else{
                    	cout<<"Wrong key:"<<endl;
              			getch();
                    	goto top;
                    	
					}
                    break;
                }
                case 2: {
                     Customer customer;
                    customer.CustomerLogin();
                    break;
                }
                case 3:
                	main_menu();
                    break;

                default:
                    cout << "Invalid choice....." << endl;
                    getch();
                    login_main_menu();
                }
}
