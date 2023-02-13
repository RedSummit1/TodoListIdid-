#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*
A Simple To do list!

Classes done Jonathan Shields
Shah Arfin did the menu member functions
Mohamed Mogali Main functions and some of the member functions in the classes such as add and insert such as the 
Sorting functions done by Prohab Patra
Christian Salvador did the print member function for the different objects

*/
class TaskNode{
	public:
		TaskNode(string task = "No task inputted", TaskNode* nextTaskNode = nullptr);
		TaskNode* nextTaskNode(){return nextTaskNodeLoc;}
		void PrintTask(bool isEndline = true);
		int NumChar() {return task.length();}
		TaskNode* InsertTask(TaskNode* taskNode = nullptr, bool isNull = true);
		string taskValue() {return task;}
		
	private:
		string task;
		TaskNode* nextTaskNodeLoc;
		
};

TaskNode::TaskNode(string task, TaskNode* nextTaskNode){
	this->task = task;
	this->nextTaskNodeLoc = nextTaskNode;
}

void TaskNode::PrintTask(bool isEndline){
	cout << task; 
	if(isEndline){
		cout << endl;
	}
}

TaskNode* TaskNode::InsertTask(TaskNode* taskNode, bool isNull){
	this->nextTaskNodeLoc = taskNode;
	if(isNull){
		taskNode->nextTaskNodeLoc = nullptr;
	}
	return taskNode;
}

class TaskGroupNode{
	public:
		TaskGroupNode(string title = "No title inputted", TaskGroupNode* nexttaskGroupNode = nullptr);
		TaskNode* AddTaskNode(string task,bool isappend  = true);
		void PrintTitle();
		TaskGroupNode* nextTaskGroupLoc(){return this->nextTaskGroupNode;}
		TaskGroupNode* AddTaskGroupNode(TaskGroupNode* tail, TaskGroupNode* head = nullptr);
		void SetTaskGroupNode(TaskGroupNode* mintedNode);
		void TaskGroupMenu();
		void PrintTasks();
		void Sort();
		void Reverse();
		void MaxandMin();
		void DeleteTaskNode();
		void CommonLetter(char commonLetter);
		
		
	private:
		string title;
		TaskNode* headTaskNode = nullptr; 
		TaskNode* currTaskNode = nullptr;
		TaskNode* tailTaskNode = nullptr;
		TaskGroupNode* nextTaskGroupNode = nullptr;
};
	
TaskGroupNode::TaskGroupNode(string title, TaskGroupNode* nexttaskGroupNode){
	this->title = title;
	this->nextTaskGroupNode = nextTaskGroupNode;
	// Make the taskGroupNode object in the main  
}

TaskNode* TaskGroupNode::AddTaskNode(string task, bool isappend){
	if(isappend){
	   if(headTaskNode == nullptr){
	   		headTaskNode = new TaskNode(task);
			tailTaskNode = headTaskNode;
			return headTaskNode;
	   }else{
			TaskNode* temp = new TaskNode(task);
			currTaskNode = headTaskNode;
			while(currTaskNode->nextTaskNode() != nullptr){
				currTaskNode = currTaskNode->nextTaskNode();
			}
			currTaskNode->InsertTask(temp);
			tailTaskNode = temp;
			return tailTaskNode;
	   }
	}
	else{
		TaskNode* temp = new TaskNode(task);
		char userOption = 'n';
		cout << "Where would you like to insert \""<< task << "\"?" << endl;
		do{
			currTaskNode = headTaskNode;
			while(currTaskNode != nullptr){
				currTaskNode->PrintTask(false);
				cout << " -> \"" + task + "\" -> ";
				cout << ((currTaskNode->nextTaskNode())?currTaskNode->nextTaskNode()->taskValue():"nullptr");
				cout << endl;
				cout << "(Y/N) : ";
				cin >> userOption;
				userOption = tolower(userOption);
				if(userOption == 'y'){
					break;
				}
				currTaskNode = currTaskNode->nextTaskNode();
				cout << endl;
			}
			cin.ignore();
		}while(userOption != 'y');
		if(currTaskNode->nextTaskNode() != nullptr){
			TaskNode* temp2 = currTaskNode->nextTaskNode();
			currTaskNode->InsertTask(temp,false);
			temp->InsertTask(temp2,false);
		}else{
			currTaskNode->InsertTask(temp);
			tailTaskNode = temp;	
		}
		
		this->PrintTasks();
	}
	return nullptr;
} 
		
TaskGroupNode* TaskGroupNode::AddTaskGroupNode(TaskGroupNode* tail, TaskGroupNode* head){
	if(head == nullptr){
		head = this;
		head->nextTaskGroupNode = nullptr;
		return head;
	}else{
		TaskGroupNode* curr = head;
		while(curr->nextTaskGroupNode != nullptr){
			curr = curr->nextTaskGroupNode;
		}
		curr->nextTaskGroupNode = this;
		tail = this;
		return tail;
   }	 
}

void TaskGroupNode::PrintTitle(){
	cout << title;
}

void TaskGroupNode::TaskGroupMenu(){
	cout<< endl << "What would you like to do with the list \"";
	this->PrintTitle();
	cout << "\"?" << endl << endl;
	cout << "1: Add a task to the list" << endl;
	cout << "2: Insert a task to the list" << endl;
	cout << "3: Print total tasks" << endl;
	cout << "4: Modify " << endl;
	cout << "5: Return longest and shortest tasks" << endl;
	cout << "6: Choose a task with the most common letter" << endl;
	cout << "7: Delete task" << endl;
	cout << "8: Exit " << endl;
	
}

void TaskGroupNode::PrintTasks(){
	if(headTaskNode){
		currTaskNode = headTaskNode;
		int count = 1;
		cout << endl;
		while(currTaskNode != nullptr && currTaskNode->taskValue() != "No task inputted"){
			cout << count << ": ";
			currTaskNode->PrintTask();
			currTaskNode = currTaskNode->nextTaskNode();
			++count;
		}
	}else{
		cout << "No task inputted" << endl;
	}
}

void TaskGroupNode::DeleteTaskNode(){
	char userOption = 'n';
	bool headCheck  = false;
		cout << "Which task would you like to delete?" << endl;
		do{
			headCheck = false;
			currTaskNode = headTaskNode;
			while(currTaskNode->nextTaskNode() != nullptr && userOption == 'n'){
				if(currTaskNode == headTaskNode && !headCheck){
					currTaskNode->PrintTask(false);
					cout << "<- ";
					cout << "(Y/N) : ";
					cin >> userOption;
					userOption = tolower(userOption);
					if(userOption == 'y'){
						break;
					}
					headCheck = true;
					continue;
				}else{
					currTaskNode->nextTaskNode()->PrintTask(false);
					cout << "<- ";
					cout << "(Y/N) : ";
					cin >> userOption;
					userOption = tolower(userOption);
					if(userOption == 'y'){
						break;
					}
				}
				currTaskNode = currTaskNode->nextTaskNode();
			}
			cin.ignore();
		}while(userOption != 'y');
		
		if(currTaskNode == headTaskNode & !headCheck){
			TaskNode* temp = currTaskNode;
			headTaskNode = headTaskNode->nextTaskNode();
			currTaskNode = nullptr;
			delete temp;
		}
		else if(currTaskNode->nextTaskNode() == tailTaskNode){
			tailTaskNode = new TaskNode();
			TaskNode* temp = currTaskNode->nextTaskNode();
			currTaskNode->InsertTask(tailTaskNode);
			tailTaskNode = currTaskNode;
			cout << "Hello World" << endl;
			  	
		}else{	
			TaskNode* temp = currTaskNode->nextTaskNode();
			currTaskNode->InsertTask(currTaskNode->nextTaskNode()->nextTaskNode(),false);
			delete temp;
		}
		
		
	
}

void TaskGroupNode::Sort(){
	vector<TaskNode*>vecTasks;
	int j;
	TaskNode* temp;
	currTaskNode = headTaskNode;
	cout << endl;
	
	while(currTaskNode != nullptr){
		vecTasks.push_back(currTaskNode);
		currTaskNode = currTaskNode->nextTaskNode();
	}
	
	for(int i = 1; i < vecTasks.size(); ++i){
		j = i;
		while( j > 0 && vecTasks.at(j)->NumChar() < vecTasks.at(j - 1)->NumChar()){
			temp = vecTasks.at(j - 1);
			vecTasks.at(j - 1) = vecTasks.at(j);
			vecTasks.at(j) = temp;
			--j;
		}	
	}
	headTaskNode = vecTasks.front();
	for(int i = 1; i < vecTasks.size(); ++i){
		vecTasks.at(i-1)->InsertTask(vecTasks.at(i));
	}
	tailTaskNode = vecTasks.back();
	
	this->PrintTasks();
	
}

void TaskGroupNode::Reverse(){
	
	vector<TaskNode*>vecTasks;
	TaskNode* temp;
	currTaskNode = headTaskNode;
	cout << endl;
	
	while(currTaskNode != nullptr){
		vecTasks.push_back(currTaskNode);
		currTaskNode = currTaskNode->nextTaskNode();
	}
	
	for(int i = 0; i < vecTasks.size()/2; ++i){
		temp = vecTasks.at(i);
		vecTasks.at(i) = vecTasks.at(vecTasks.size() - 1 - i);
		vecTasks.at(vecTasks.size() - 1 - i) = temp;
	}
	
	headTaskNode = vecTasks.front();
	for(int i = 1; i < vecTasks.size(); ++i){
		vecTasks.at(i-1)->InsertTask(vecTasks.at(i));
	}
	tailTaskNode = vecTasks.back();

	this->PrintTasks();
}

void TaskGroupNode::MaxandMin(){
	currTaskNode = headTaskNode->nextTaskNode();
	TaskNode*max = headTaskNode;
	TaskNode*min = headTaskNode;
	while(currTaskNode != nullptr){
	 	if(currTaskNode->NumChar() > max->NumChar()){
		 	max = currTaskNode;
		}
		else if(currTaskNode->NumChar() < min->NumChar()){
			min = currTaskNode;
		}
		currTaskNode = currTaskNode->nextTaskNode();
	}
	
	if (max == min){
		cout << "No min and max, all tasks are the same size" << endl;
	}else{
		cout << endl << "Minimum sized task: "; min->PrintTask();
		cout << "Maximum sized task: "; max->PrintTask();
	}
}

void TaskGroupNode::CommonLetter(char commonLetter){
	int count;
	int maxValue = 0;
	TaskNode* chosenTask = nullptr;
	currTaskNode = headTaskNode;
	while(currTaskNode != nullptr){
		count = 0;
		for(int i = 0; i < currTaskNode->taskValue().size(); ++i){
			if(tolower(commonLetter) == tolower(currTaskNode->taskValue().at(i))){
				count++;
			}
		}
		if(maxValue < count){
			maxValue = count;
			chosenTask = currTaskNode;
		}
		currTaskNode = currTaskNode->nextTaskNode();
	}
	if(chosenTask){
		cout << "\""; 
		cout << chosenTask->taskValue(); 
		cout << "\" task has the letter "; 
		cout << commonLetter; 
		cout << " the most amount of times ";
		cout << "(" << maxValue; 
		cout << ((maxValue > 1)? " times)": " time)");
		cout << " " << endl;
	}else{
		cout << "No task has that letter" << endl;
	}
}

void StartMenu(){
    cout << " *******************************************" << endl;
    cout << " *           \"Simple\" to do list         *" << endl;
    cout << " *******************************************" << endl << endl;
    cout << " Select a number: " << endl;
    cout << "    1: Make a new list " << endl;
    cout << "    2: Select a list" << endl;
    cout << "    3: Print total lists" << endl;
    cout << "    4: Quit " << endl;
    cout << endl;
}

void PrintTaskGroups(TaskGroupNode* head){
	TaskGroupNode* curr = head;
	int count = 1;
	cout << endl;
	while(curr != nullptr){
		cout << count << ": ";
		curr->PrintTitle();
		curr = curr->nextTaskGroupLoc();
		cout << endl;
		++count;
	}
}

int main(){
	
	int choiceMenu, userInput, modOption, i;
	char ans, choiceObj,again;
	string option, name , task;
	TaskGroupNode* mint = nullptr;
	TaskGroupNode* head = nullptr;
	TaskGroupNode* curr = nullptr;
	TaskGroupNode* tail = nullptr;
	bool stopLoop = false;
	bool didCase = false;
	bool didCase2 = false; 
	
	

	while(true){  
		StartMenu();
		cin >> choiceMenu;
		switch(choiceMenu){	
			case 1:
				didCase  = true;
				again = 'Y';
				while(toupper(again) == 'Y'){
					cin.ignore();
					cout << "What is the title of your list?" << endl;
					getline(cin, name);
					mint = new TaskGroupNode(name);
					if(head == nullptr){
						head = mint->AddTaskGroupNode(tail,head);
						tail = head;
					}else{
						tail = mint->AddTaskGroupNode(tail,head);
					}
					cout << "Add another list? (Y/N)" << endl;
					cin >> again;
				}
				break;	
			case 2:
				if(!didCase){
					cout << "Please do case 1 first before proceeding" << endl;
					break;
				}
				do{
					curr = head;
					while(curr != nullptr){
						curr->PrintTitle();
						cout << ": Is this your choice? (Y/N)" << endl;
						cin >> choiceObj;
						if(toupper(choiceObj) == 'Y'){
							break;
						}
						curr = curr->nextTaskGroupLoc();
					}
				}while(!curr);
				stopLoop = false;
				
				while(!stopLoop){
					curr->TaskGroupMenu();
					cin >> userInput;
					stopLoop = false;
					switch(userInput){
						case 1:
							didCase2 = true;
							do{
								cout << "What is the task you would like to add?" << endl;
								cin.ignore();
								getline(cin,task);
								curr->AddTaskNode(task);
								cin.clear();
								cout << "Add another task? (Y/N)" << endl;
								cin >> choiceObj;
							}while(toupper(choiceObj) == 'Y');
							break;
						case 2:
							if(!didCase2){
								cout << "Please do case 1 first before proceeding" << endl;
								break;
							}
							cout << "What is the task you would like to add?" << endl;
							cin.ignore();
							getline(cin,task); 
							curr->AddTaskNode(task, false);
							break;
						case 3:
							if(!didCase2){
								cout << "Please do case 1 first before proceeding" << endl;
								break;
							}
							curr->PrintTasks();
							break;
						case 4:
							if(!didCase2){
								cout << "Please do case 1 first before proceeding" << endl;
								break;
							}
							cout << endl << "What would you like to do with the list \""; 
							curr->PrintTitle();
							cout << "\"?" << endl << endl;
							cout <<"1: Sort" << endl;
							cout <<"2: Reverse" << endl;
							cout <<"3: Exit" << endl;
							cin >> modOption;
							switch(modOption){
								case 1:
									curr->Sort();
									break;
								case 2:
									curr->Reverse();
									break;
								case 3:
									break;
								default:
									cout << "Wrong option, back to menu" << endl;
									break;
							}					
							break;
						case 5:
							if(!didCase2){
								cout << "Please do case 1 first before proceeding" << endl;
								break;
							}
							curr->MaxandMin(); 
							break;
						case 6: 
							if(!didCase2){
								cout << "Please do case 1 first before proceeding" << endl;
								break;
							}
							cout << "Enter the value you would like to find: " << endl;
							cin >> ans;
							curr->CommonLetter(ans);
							break;
						case 7:
							if(!didCase2){
								cout << "Please do case 1 first before proceeding" << endl;
								break;
							}
							curr->DeleteTaskNode();
							break;
						case 8:
							cout << "Exiting \"";
							curr->PrintTitle(); 
							cout << "\" List" << endl;
							stopLoop = true;	
							break;
							
						default:
							cout << "Error" << endl;
							break;
					}
				}
				break;
			case 3:
				if(!didCase){
					cout << "Please do case 1 first before proceeding" << endl;
					break;
				}
				PrintTaskGroups(head);
				break;
			case 4:
				return 0;	
			default:
				cout << "Error" << endl;
				return -1;
			}
		cout << endl;
		cin.clear();
	}
}



