#include <iostream>
#include <vector>
using namespace std;

// class activity yang berisi detail detail tentang aktivitas 
class activity{
    public:
    int indexAct;
    string activityName;
    string description;
    bool actMark = 0;

};

// fungsi help untuk menampilkan command comman yang digunakan pada aplikasi 
void help(){
    cout<<"    view        => to view Activities list"<<endl;
    cout<<"touch [index]   => to view more about the activity"<<endl;
    cout<<"    add         => to add activity in list"<<endl;
    cout<<"mark [index] -c  => to mark activity as completed"<<endl;
    cout<<"mark [index] -p  => to mark activity as pending"<<endl;
    cout<<"  rmv [index]   => to remove activity from list"<<endl<<endl;
}

// fungsi untuk mengupdate status mark pada suatu aktivitas
void updateMark(string status, int index, vector <activity> &actList){
        // jika status "c" maka status akan bervalue 1 (completed)
        // check if Index are match or not 
    if ((index > actList.size()) || (index == 0)){
        cout<<"There is no such Activity"<<endl;
    }else{     
        if ((status == "c")){
            actList[index - 1].actMark = 1;
            cout<<"Status updated successfully"<<endl;
        }else{
            // jika status "p" maka status akan bervalue 0 (pending)
            actList[index - 1].actMark = 0;
            cout<<"Status updated successfully "<<endl;   
        }
    }
}

// fungsi untuk menghapus aktivitas pada vektor 
void remove(int index, vector <activity> &actList){
    actList.erase(actList.begin() + index - 1);
    cout<<"Activity Removed successfully"<<endl;
}

// fungsi untuk melihat lebih detail tentang aktivitas yang ada pada vector actList
void touchAct(int index, vector <activity> &actList){
    string mark;
    // check if Index are match or not 
    if ((index > actList.size()) || (index == 0)){
        cout<<"There's No Such Activity "<<endl;
    }else{
        // to convert value of indexMark into pending or complete 
            if (actList[index - 1].actMark == 0){
                mark = "Pending";
            }else{
                mark = "Completed";
            }

        // to show detail information of activity 
        cout<<"\n"<<"----------Activity Info----------"<<endl<<endl;
        cout<<"Activity Name    : "<<actList[index - 1].activityName<<endl;
        cout<<"Description      : "<<actList[index - 1].description<<endl;
        cout<<"Status           : "<<mark<<endl;
    }
    
}

void listActivity(vector <activity> actList){
    // UI for null activity List 
    if (actList.size() == 0){
        cout<<"------------- TO DO LIST -----------------"<<endl;
        cout<<endl<<endl<<endl;
        cout<<"No Activities Right Now !"<<endl;
        cout<<"Type 'help' to view command list"<<endl<<endl;
    }else{
        // to show the list of activity 
        cout<<"------------- TO DO LIST -----------------"<<endl<<endl;
        cout<<"Index |  Activity Name   | Status";
        string mark;
        cout<<endl<<endl;
        for (int i = 0; i < actList.size(); i++){
            if (actList[i].actMark == 0){
                mark = "Pending";
            }else{
                mark = "Completed";
            }
            
            cout<<i+1<<". |     "<<actList[i].activityName<<"    | "<<mark<<endl;
        }
        cout<<endl<<endl;
    }
}

void addActivity(vector <activity> &actList){
        activity newAct;  //create new variable from class
        string name;
        string desc;

        cout<<"Activity Name : ";
        getline(cin>>ws,name);
        cout<<endl;
        cout<<"Description   : ";
        getline(cin,desc);
        
        newAct.activityName = name;
        newAct.description = desc;
        newAct.indexAct = actList.size();
        actList.push_back(newAct); //push the variabel into activity vector 
}


int main(){
    vector <activity> actList;
    listActivity(actList);

    // create infinite command line input 
    while (true){
        string inputUser;
        cout<<"==> ";
        getline(cin>>ws,inputUser);
        cout<<endl;
        string inputSplit = inputUser.substr(0, inputUser.find(" "));  // to get first word from inputUser 

        if (inputUser == "help"){
            help();
        }else if (inputUser == "view"){
            listActivity(actList);
        }else if (inputUser == "add"){
            addActivity(actList);
        }else if(inputSplit == "touch"){
            // to get the index where its in the second word 
            string getIndex = inputUser.substr(6, inputUser.find(" "));
            bool checkIndex = 1;
            for (auto x : getIndex){
                // to check if the second word are integer or not 
                if (isdigit(x) == 0){
                    checkIndex = 0;
                    break;   
                }
            }

            if (checkIndex){
                // to convert string Index into int 
                int catchIndex = stoi(getIndex);
                touchAct(catchIndex, actList);
            }else{
                cout<<"There's No Such Activity "<<endl;
            }
        }else if(inputSplit == "mark"){
            // to get second and third word from input User 
            string getMark = inputUser.substr(inputUser.find("-")+1,inputUser.find(" "));
            string getIndex = inputUser.substr(5,inputUser.find("-")-6);
            
            bool checkIndex = 1;
            for (auto x : getIndex){
                // to check if the second word (index) is integer or not 
                if (isdigit(x) == 0){
                    checkIndex = 0;
                    break;   
                }
            }

            if ((checkIndex) && ((getMark == "c") || (getMark == "p"))){
                // convert string index into int 
                int catchIndex = stoi(getIndex);
                updateMark(getMark,catchIndex, actList);
            }else{
                cout<<"There's No Such Activity "<<endl;
            }
        }else if(inputSplit == "rmv"){
            string getIndex = inputUser.substr(4, inputUser.find(" "));
            bool checkIndex = 1;
            for (auto x : getIndex){
                if (isdigit(x) == 0){
                    checkIndex = 0;
                    break;   
                }
            }

            if (checkIndex){
                int catchIndex = stoi(getIndex);
                remove(catchIndex, actList);
            }else{
                cout<<"There's No Such Activity "<<endl;
            }
        }else{
            cout<<"Command not Found"<<endl;
        }
    }
}