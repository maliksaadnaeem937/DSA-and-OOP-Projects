#include <iostream>
#include <string>
using namespace std;

class NodeStack {
public:
    NodeStack* next;
    string data;
    
    NodeStack(string d) {
        this->data = d;
        this->next = NULL;
    }
};

class Stack {
    NodeStack* top;
    int numberOfWords;
    
public:
    Stack() {
        this->top = NULL;
        numberOfWords = 0;
    }
    
    void push(string word) {
        NodeStack* newNode = new NodeStack(word);
        if (top == NULL) {
            top = newNode;
        } else {
            newNode->next = top;
            top = newNode;
        }
        numberOfWords++;
    }
    
    void pop() {
        while (top != NULL) {
            cout << top->data << " ";
            top = top->next;
        }cout<<endl;
    }
    
    void printTotalWords() {
        cout << "Total number of words  = " << numberOfWords << endl;
    }
    bool contains(const string word){
    	if(top==NULL) return 0;
    	else {
    		NodeStack* temp=top;
    		while(temp!=NULL){
    			if(temp->data==word){
    				return 1;
				}
				temp=temp->next;
    			
			}
			return 0;
		}
    	
    	
	}
    void counterFunction(const string word,Stack &uniqueWordsStack){
    
    	NodeStack *temp=top;
    	int count=0;
    	while(temp!=NULL){
    		
    		if(temp->data==word){
    			count++;
    			
    			
			}
			temp=temp->next;
		}
	
    
    	if(!uniqueWordsStack.contains(word)){
    		uniqueWordsStack.push(word);
    		cout<<word<<" : is repeated "<<count<<" times"<<endl;
		}
    	
	}
    
    
    void frequencyOfEachWord(Stack &uniqueWordsStack){
    	NodeStack *temp=top;
    
     
    	while(temp!=NULL){
    		counterFunction(temp->data,uniqueWordsStack);
    		temp=temp->next;
    		
		}
    	
    	
    	
    	
	}
    
   
};

class NodeQueue {
public:
    NodeQueue* next;
    char data;
    
    NodeQueue(char d) {
        this->data = d;
        this->next = NULL;
    }
};

class Queue {
    NodeQueue* front;
    NodeQueue* rear;
    
public:
    Queue() {
        this->front = NULL;
        this->rear = NULL;
    }
    
    void enqueue(char i) {
        NodeQueue* newNode = new NodeQueue(i);
        if (front == NULL && rear == NULL) {
            front = newNode;
            rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }
    
    void print() {

        NodeQueue* temp = front;
        while (temp != NULL) {
            cout << temp->data;
            temp = temp->next;
        }
        cout << endl;
    }
    
  void dequeue() {
    Stack stack;
    Stack uniqueWordsStack;
    string word = "";

    while (front != NULL) {
        if (front->data == ' ' || front->data == '.' || front->data == ',') {
            if (!word.empty()) { // Only push non-empty words
                stack.push(word);
                word = "";
            }
        } else {
            word += front->data;
        }
        front = front->next;
    }

    if (!word.empty()) { // Push the last word if it's non-empty
        stack.push(word);
    }

    stack.printTotalWords();
    stack.frequencyOfEachWord(uniqueWordsStack);
    cout<<"Printing the original input in reverse order:"<<endl;
    stack.pop();
  cout<<"Printing the unique words without any repetition"<<endl;
    uniqueWordsStack.pop();
}

};

int main() {
    Queue queue;
    string input;
    cout << "Enter a line of text: ";
    getline(cin, input);
    
    
    for (int i = 0; input[i] != '\0'; i++) {
        queue.enqueue(input[i]);
    }
    
    queue.print();
    queue.dequeue();
    
    return 0;
}

